/*
 *  receiver.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: receiver.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#include <anidb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define QUEUE_SIZE  100
#define RETRIES     6

static int receiver_started = 0;

static ani_response_t **response_queue = (ani_response_t **)NULL;
static int response_queue_size = QUEUE_SIZE;
static const char lock_name[] = "RESPONSE_Q_LOCK";
static ani_sem_t *queue_lock = (ani_sem_t *)NULL;
static ani_thread_t *receiver_thread = (ani_thread_t *)NULL;

static void *receiver(void *ptr);
static void store_response(ani_response_t *response);
static void create_response_queue(void);
static void destroy_response_queue(void);
static int create_semaphores(void);
static int destroy_receiver_semaphores(void);
static int create_receiver_thread(void);
static int destroy_receiver_thread(void);

int ani_start_receiver(void)
{
    if (0 != receiver_started)
    {
        ERROR("Receiver already started\n", NULL);
        return 1;
    }
    create_response_queue();
    if (0 != create_semaphores())
    {
        return 1;
    }
    if (0 != create_receiver_thread())
    {
        return 1;
    }
    receiver_started = 1;
    DEBUG("Receiver started\n", NULL);
    return 0;
}

int ani_stop_receiver(void)
{
    if (0 == receiver_started)
    {
        ERROR("Receiver not running\n", NULL);
        return 1;
    }
    if (0 != destroy_receiver_thread())
    {
        return 1;
    }
    if (0 != destroy_receiver_semaphores())
    {
        return 1;
    }
    destroy_response_queue();
    receiver_started = 0;
    DEBUG("Receiver stopped\n", NULL);
    return 0;
}

ani_response_t *ani_get_response(const ani_request_t *request)
{
    #define CMP_TAG(x)                                                      \
        (0 == strncmp(response_queue[i]->tag, x, TAG_LEN) ||                \
         0 == strncmp(response_queue[i]->tag, TAG_BANNED, TAG_LEN) ||       \
         0 == strncmp(response_queue[i]->tag, TAG_UNKNOWN, TAG_LEN) ||      \
         0 == strncmp(response_queue[i]->tag, TAG_SERVER, TAG_LEN))

    ani_response_t *response = NULL;
    int i = 0;
    int j = 0;

    assert(NULL != request);
    assert(NULL != response_queue);
    assert(NULL != queue_lock);
    DEBUG("Waiting for response_q\n", NULL);
    for (j = 1; j <= RETRIES; j++)
    {
        DEBUG("Looking for request in response_q (tag=%s, iteration=%i)\n",
            request->tag, j);
        ani_sem_wait(queue_lock);
        for (i = 0; i < response_queue_size; i++)
        {
            if (NULL != response_queue[i] && CMP_TAG(request->tag))
            {
                DEBUG("Found request in response_q (tag=%s)\n", request->tag);
                response = response_queue[i];
                response_queue[i] = NULL;
                ani_sem_post(queue_lock);
                return response;
            }
        }
        ani_sem_post(queue_lock);
        (void)sleep(j + 2);
    }
    DEBUG("No such request in response_q (tag=%s)\n", request->tag);
    return response;
}

ani_response_t *ani_get_notification(void)
{
    ani_request_t request = { { '\0' }, { '\0' }, { '\0' } };

    return ani_get_response(&request);
}

static void *receiver(void *ptr)
{
    char recv_buf[RAW_LEN] = { '\0' };
    ssize_t recv_len = 0;

    assert(NULL == ptr);
    for (;;)
    {
        recv_len = ani_recv(recv_buf, RAW_LEN);
        switch(recv_len) {
            case -3:        /* ECONNREFUSED */
                break;
            case -2:        /* EAGAIN || EWOULDBLOCK */
                break;
            case -1:        /* ERROR */
                return NULL;
            case 0:         /* socket closed */
                return NULL;
            default:        /* data */
                store_response(ani_create_response(recv_buf));
                break;
        }
    }
    return NULL;
}

static void store_response(ani_response_t *response)
{
    int i = 0;
    int stored = 0;

    assert(NULL != response);
    assert(NULL != response_queue);
    assert(NULL != queue_lock);
    ani_sem_wait(queue_lock);
    DEBUG("Storing response (tag=%s)\n", response->tag);
    for (i = 0; i < response_queue_size; i++)
    {
        if (NULL == response_queue[i])
        {
            response_queue[i] = response;
            stored = 1;
            break;
        }
    }
    if (0 == stored)
    {
        response_queue_size += QUEUE_SIZE;
        response_queue = xrealloc(response_queue, response_queue_size);
        response_queue[++i] = response;
    }
    ani_sem_post(queue_lock);
    DEBUG("Stored response (tag=%s)\n", response->tag);
    if (*response->tag == '\0')
    {
        DEBUG("Notifying dispatcher\n", NULL);
        ani_pump();
    }
}

static void create_response_queue(void)
{
    assert(NULL == response_queue);
    response_queue = (ani_response_t **)xcalloc(response_queue_size,
        sizeof(ani_response_t));
}

static void destroy_response_queue(void)
{
    int i = 0;

    assert(NULL != response_queue);
    for (i = 0; i < response_queue_size; i++)
    {
        if (NULL != response_queue[i])
        {
            free(response_queue[i]);
            response_queue[i] = NULL;
        }
    }
    free(response_queue);
    response_queue = NULL;
    DEBUG("Cleaned up response queue\n", NULL);
}

static int create_semaphores(void)
{
    assert(NULL == queue_lock);
    ANI_KILL_SEM(lock_name);
    if (NULL == (queue_lock = ani_sem_open(lock_name, 1)))
    {
        return 1;
    }
    return 0;
}

static int destroy_receiver_semaphores(void)
{
    assert(NULL != queue_lock);
    if (0 != ani_sem_cleanup(lock_name, queue_lock))
    {
        return 1;
    }
    queue_lock = NULL;
    return 0;
}

static int create_receiver_thread(void)
{
    assert(NULL == receiver_thread);
    receiver_thread = (ani_thread_t *)xmalloc(sizeof(ani_thread_t));
    if (0 != ani_create_thread(receiver_thread, receiver, NULL))
    {
        ERROR("Could not create receiver thread: %s\n", xstrerror());
        return 1;
    }
    DEBUG("Started receiver thread\n", NULL);
    return 0;
}

static int destroy_receiver_thread(void)
{
    assert(NULL != receiver_thread);
    if (0 != ani_thread_cancel(receiver_thread))
    {
        ERROR("Could not cancel receiver thread: %s\n", xstrerror());
        return 1;
    }
    xfree(ani_thread_t, receiver_thread);
    DEBUG("Destroyed receiver thread\n", NULL);
    return 0;
}
