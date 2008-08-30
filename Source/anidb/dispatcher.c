/*
 *  dispatcher.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: dispatcher.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#include <anidb.h>
#include <stdlib.h>
#include <unistd.h>

static int dispatcher_started = 0;

static ani_thread_t *dispatcher_thread = (ani_thread_t *)NULL;
static const char dispatcher_counter_name[] = "DISPATCHER_COUNTER";
static ani_sem_t *dispatcher_counter = (ani_sem_t *)NULL;

static void *dispatcher(void *ptr);
static int create_semaphores(void);
static int destroy_dispatcher_semaphores(void);
static int create_dispatcher_thread(void);
static int destroy_dispatcher_thread(void);

int ani_start_dispatcher(void)
{
    if (0 != dispatcher_started)
    {
        ERROR("Dispatcher already started\n", NULL);
        return 1;
    }
    DEBUG("Starting dispatcher\n", NULL);
    if (0 != create_semaphores())
    {
        return 1;
    }
    if (0 != create_dispatcher_thread())
    {
        return 1;
    }
    dispatcher_started = 1;
    DEBUG("Dispatcher started\n", NULL);
    return 0;
}

int ani_stop_dispatcher(void)
{
    if (0 == dispatcher_started)
    {
        ERROR("Dispatcher not running\n", NULL);
        return 1;
    }
    DEBUG("Stopping dispatcher\n", NULL);
    if (0 != destroy_dispatcher_semaphores())
    {
        return 1;
    }
    if (0 != destroy_dispatcher_thread())
    {
        return 1;
    }
    dispatcher_started = 0;
    DEBUG("Dispatcher stopped\n", NULL);
    return 0;
}

int ani_pump(void)
{
    return ani_sem_post(dispatcher_counter);
}

static void *dispatcher(void *ptr)
{
    ani_response_t *response = NULL;
    ani_response_t *push_response = NULL;
    ani_push_file_notify_t *file_notification = NULL;
    ani_push_msg_notify_t *msg_notification = NULL;
    ani_push_buddy_notify_t *buddy_notification = NULL;
    ani_push_shutdown_notify_t *shutdown_notification = NULL;

    assert(NULL == ptr);
    for (;;)
    {
        /*  check for NULL values is needed, as destroy_dispatcher_semaphores
            destroys the sem and then NULLs out the variable */
        if (NULL == dispatcher_counter ||
            -1 == ani_sem_wait(dispatcher_counter))
        {
            break;
        }
        response = ani_get_notification();
        DEBUG("Received notification (notify_code %d)\n",
            response->notify_code);
        push_response = ani_push_ack(response->notify_code);
        if (ANI_STATUS_PUSHACK_CONFIRMED != push_response->status_code)
        {
            WARN("Did not receive pushack confirmation (notify_code %d)... "
                " not launching callback\n", response->notify_code);
            xfree(ani_response_t, push_response);
            xfree(ani_response_t, response);
            continue;
        }
        DEBUG("Received pushack confirmation (notify_code %d)\n",
            response->notify_code);
        switch(response->status_code)
        {
            case ANI_STATUS_NOTIFICATION_NOTIFY:
                file_notification = ani_create_push_file_notify(response);
                ani_file_notify(file_notification);
                xfree(ani_push_file_notify_t, file_notification);
                break;
            case ANI_STATUS_NOTIFICATION_MESSAGE:
                msg_notification = ani_create_push_msg_notify(response);
                ani_msg_notify(msg_notification);
                xfree(ani_push_msg_notify_t, msg_notification);
                break;
            case ANI_STATUS_NOTIFICATION_BUDDY:
                buddy_notification = ani_create_push_buddy_notify(response);
                ani_buddy_notify(buddy_notification);
                xfree(ani_push_buddy_notify_t, buddy_notification);
                break;
            case ANI_STATUS_NOTIFICATION_SHUTDOWN:
                shutdown_notification =
                    ani_create_push_shutdown_notify(response);
                ani_shutdown_notify(shutdown_notification);
                xfree(ani_push_shutdown_notify_t, shutdown_notification);
                break;
            default:
                ERROR("Unknown notification arrived (status_code=%d)\n",
                    response->status_code);
                break;
        }
        xfree(ani_response_t, push_response);
        xfree(ani_response_t, response);
    }
    return NULL;
}

static int create_semaphores(void)
{
    assert(NULL == dispatcher_counter);
    ANI_KILL_SEM(dispatcher_counter_name);
    if (NULL == (dispatcher_counter = ani_sem_open(dispatcher_counter_name, 0)))
    {
        return 1;
    }
    return 0;
}

static int destroy_dispatcher_semaphores(void)
{
    assert(NULL != dispatcher_counter);
    if (0 != ani_sem_cleanup(dispatcher_counter_name, dispatcher_counter))
    {
        return 1;
    }
    dispatcher_counter = NULL;
    return 0;
}

static int create_dispatcher_thread(void)
{
    assert(NULL == dispatcher_thread);
    dispatcher_thread = (ani_thread_t *)xmalloc(sizeof(ani_thread_t));
    if (0 != ani_create_thread(dispatcher_thread, dispatcher, NULL))
    {
        ERROR("Could not create dispatcher thread: %s\n", xstrerror());
        return 1;
    }
    return 0;
}

static int destroy_dispatcher_thread(void)
{
    assert(NULL != dispatcher_thread);
    if (0 != ani_thread_cancel(dispatcher_thread))
    {
        ERROR("Could not cancel dispatcher thread: %s\n", xstrerror());
        return 1;
    }
    free(dispatcher_thread);
    dispatcher_thread = NULL;
    return 0;
}
