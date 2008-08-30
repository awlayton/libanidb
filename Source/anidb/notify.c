/*
 *  notify.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: notify.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#include <anidb.h>
#include <unistd.h>

#define NOTIFICATION_POLL_INTERVAL  (20*60)

static ani_notify_file_callback file_notify_callback = NULL;
static ani_notify_msg_callback msg_notify_callback = NULL;
static ani_notify_buddy_callback buddy_notify_callback = NULL;
static ani_notify_shutdown_callback shutdown_notify_callback = NULL;

static ani_notifyget_msg_callback notifyget_msg_callback = NULL;
static ani_notifyget_notification_callback notifyget_notification_callback =
    NULL;

static ani_thread_t *notifyer_thread = (ani_thread_t *)NULL;
static const char notifyer_lock_name[] = "NOTIFYER_LOCK";
static ani_sem_t *notifyer_lock = (ani_sem_t *)NULL;

static void get_all_notifications(ani_notifylist_t *list);

static void *notifyer(void *ptr);
static int create_notifyer_semaphores(void);
static int destroy_notifyer_semaphores(void);
static int create_notifyer_thread(void);
static int destroy_notifyer_thread(void);

ani_response_t *ani_start_notification_service(int files_added, int msg_added,
    int buddy_event)
{
    ani_response_t *response = NULL;

    assert(files_added == 1 || files_added == 0);
    assert(msg_added == 1 || msg_added == 0);
    assert(buddy_event == 1 || buddy_event == 0);
    response = ani_send_cmd(ANIDB_CMD_PUSH, files_added, msg_added, buddy_event);
    (void)create_notifyer_thread();
    if (ANI_STATUS_NOTIFICATION_ENABLED == response->status_code)
    {
        INFO("Notification service enabled\n", NULL);
        ANI_ENABLE_STATUS(STATUS_NOTIFY_ENABLED);
    }
    return response;
}

ani_response_t *ani_stop_notification_service(void)
{
    ani_response_t *response = NULL;

    response = ani_send_cmd(ANIDB_CMD_PUSH, 0, 0, 0);
    (void)destroy_notifyer_thread();
    INFO("Notification service disabled\n", NULL);
    ANI_DISABLE_STATUS(STATUS_NOTIFY_ENABLED);
    return response;
}

ani_response_t *ani_notify(int buddies)
{
    assert(0 == buddies || 1 == buddies);
    return ani_send_cmd(ANIDB_CMD_NOTIFY, buddies);
}

ani_response_t *ani_notify_list(void)
{
    return ani_send_cmd(ANIDB_CMD_NOTIFYLIST);
}

ani_response_t *ani_notify_get(char type, int id)
{
    assert(type == 'M' || type == 'N');
    assert(id > 0);
    return ani_send_cmd(ANIDB_CMD_NOTIFYGET, type, id);
}

ani_response_t *ani_notify_ack(char type, int id)
{
    assert(type == 'M' || type == 'N');
    assert(id > 0);
    return ani_send_cmd(ANIDB_CMD_NOTIFYACK, type, id);
}

ani_response_t *ani_push_ack(int id)
{
    assert(id > 0);
    return ani_send_cmd(ANIDB_CMD_PUSHACK, id);
}

void ani_file_notify(ani_push_file_notify_t *notification)
{
    assert(NULL != notification);
    if (NULL != file_notify_callback)
    {
        file_notify_callback(notification);
    }
}

void ani_msg_notify(ani_push_msg_notify_t *notification)
{
    assert(NULL != notification);
    if (NULL != msg_notify_callback)
    {
        msg_notify_callback(notification);
    }
}

void ani_buddy_notify(ani_push_buddy_notify_t *notification)
{
    assert(NULL != notification);
    if (NULL != buddy_notify_callback)
    {
        buddy_notify_callback(notification);
    }
}

void ani_shutdown_notify(ani_push_shutdown_notify_t *notification)
{
    assert(NULL != notification);
    if (NULL != shutdown_notify_callback)
    {
        shutdown_notify_callback(notification);
    }
}

void ani_msg_notifyget(ani_notifyget_msg_t *notification)
{
    assert(NULL != notification);
    if (NULL != notifyget_msg_callback)
    {
        notifyget_msg_callback(notification);
    }
}

void ani_notification_notifyget(ani_notifyget_notification_t *notification)
{
    assert(NULL != notification);
    if (NULL != notifyget_notification_callback)
    {
        notifyget_notification_callback(notification);
    }
}

void ani_register_file_notify_callback(ani_notify_file_callback func)
{
    file_notify_callback = func;
}

void ani_register_msg_notify_callback(ani_notify_msg_callback func)
{
    msg_notify_callback = func;
}

void ani_register_buddy_notify_callback(ani_notify_buddy_callback func)
{
    buddy_notify_callback = func;
}

void ani_register_shutdown_notify_callback(ani_notify_shutdown_callback func)
{
    shutdown_notify_callback = func;
}

void ani_register_msg_notifyget_callback(ani_notifyget_msg_callback func)
{
    notifyget_msg_callback = func;
}

void ani_register_notification_notifyget_callback(
    ani_notifyget_notification_callback func)
{
    notifyget_notification_callback = func;
}

/*
 *  Possible FIXME: we could use the dispatcher to execute the callback
 */
static void get_all_notifications(ani_notifylist_t *list)
{
    int i = 0;
    ani_response_t *response = NULL;
    ani_response_t *ack_response = NULL;
    ani_notifyget_msg_t *msg = NULL;
    ani_notifyget_notification_t *notification = NULL;

    DEBUG("Getting all pending notifications (%d)\n", list->notify_count);
    for (i = 0; i < list->notify_count; ++i)
    {
        DEBUG("Getting pending notification: (%c::%d)\n", list->types[i],
            list->ids[i]);
        response = ani_notify_get(list->types[i], list->ids[i]);
        switch (response->status_code)
        {
            case ANI_STATUS_NOTIFYGET_NOTIFY:
            case ANI_STATUS_NOTIFYGET_MESSAGE:
                DEBUG("Got notification (%d)... ACKing\n", list->ids[i]);
                ack_response = ani_notify_ack(list->types[i], list->ids[i]);
                switch(ack_response->status_code)
                {
                    case ANI_STATUS_NOTIFYACK_SUCCESSFUL_M:
                        DEBUG("Acked notification (%d)\n", list->ids[i]);
                        msg = ani_create_notifyget_msg(response);
                        DEBUG("Executing callback for notification (%d)\n",
                            list->ids[i]);
                        // TODO: Call the dispatcher
                        ani_msg_notifyget(msg);
                        DEBUG("Executed callback for notification (%d)\n",
                            list->ids[i]);
                        xfree(ani_notifyget_msg_t, msg);
                        break;
                    case ANI_STATUS_NOTIFYACK_SUCCESSFUL_N:
                        DEBUG("Acked notification (%d)\n", list->ids[i]);
                        notification =
                            ani_create_notifyget_notification(response);
                        DEBUG("Executing callback for notification (%d)\n",
                            list->ids[i]);
                        // TODO: Call the dispatcher
                        ani_notification_notifyget(notification);
                        DEBUG("Executed callback for notification (%d)\n",
                            list->ids[i]);
                        xfree(ani_notifyget_notification_t, notification);
                        break;
                    case ANI_STATUS_NO_SUCH_ENTRY_M:
                    case ANI_STATUS_NO_SUCH_ENTRY_N:
                        ERROR("No such entry in notifylist: %d\n",
                            list->ids[i]);
                        break;
                    default:
                        assert(0);
                        break;
                }
                break;
            case ANI_STATUS_NO_SUCH_NOTIFY:
            case ANI_STATUS_NO_SUCH_MESSAGE:
                ERROR("No such notify pending: %d\n", list->ids[i]);
                break;
            default:
                ERROR("Cannot handle answer: %s\n", ack_response->msg);
                break;
        }
        DEBUG("Got all pending notifications\n", NULL);
        xfree(ani_response_t, ack_response);
        xfree(ani_response_t, response);
    }
}

static void *notifyer(void *ptr)
{
    ani_response_t *response = NULL;
    ani_response_t *response_list = NULL;
    ani_notify_t *notify = NULL;
    ani_notifylist_t *notifylist = NULL;

    assert(NULL == ptr);
    for (;;)
    {
        if (-1 == ani_sem_wait(notifyer_lock))
        {
            break;
        }
        DEBUG("Polling for new notifications\n", NULL);
        response = ani_notify(1);
        DEBUG("Got notification packet\n", NULL);
        if (ANI_STATUS_NOTIFICATION == response->status_code)
        {
            notify = ani_create_notify(response);
            if (notify->pending_notifies > 0 || notify->pending_msgs > 0)
            {
                    response_list = ani_notify_list();
                    notifylist = ani_create_notifylist(response_list);

                    if (ANI_STATUS_NOTIFYLIST == response_list->status_code)
                    {
                        get_all_notifications(notifylist);
                    }
                    else
                    {
                    ERROR("Unable to handle response (not a notifylist: %s)",
                        response->msg);
                }
                xfree(ani_notifylist_t, notifylist);
                xfree(ani_response_t, response_list);
            }
            xfree(ani_notify_t, notify);
        }
        xfree(ani_response_t, response);
        if (-1 == ani_sem_post(notifyer_lock))
        {
            break;
        }
        if (0 != sleep(NOTIFICATION_POLL_INTERVAL))
        {
            WARN("Sleep interrupted\n", NULL)
            continue;
        }
    }
    return NULL;
}

static int create_notifyer_semaphores(void)
{
    assert(NULL == notifyer_lock);
    ANI_KILL_SEM(notifyer_lock_name);
    if (NULL == (notifyer_lock = ani_sem_open(notifyer_lock_name, 1)))
    {
        return 1;
    }
    return 0;
}

static int destroy_notifyer_semaphores(void)
{
    assert(NULL != notifyer_lock);
    if (0 != ani_sem_cleanup(notifyer_lock_name, notifyer_lock))
    {
        return 1;
    }
    notifyer_lock = NULL;
    return 0;
}

static int create_notifyer_thread(void)
{
    assert(NULL == notifyer_thread);
    if (0 != create_notifyer_semaphores())
    {
        return 1;
    }
    notifyer_thread = (ani_thread_t *)xmalloc(sizeof(ani_thread_t));
    if (0 != ani_create_thread(notifyer_thread, notifyer, NULL))
    {
        ERROR("Could not create notifyer thread: %s\n", xstrerror());
        return 1;
    }
    DEBUG("Started notifyer thread\n", NULL);
    return 0;
}

static int destroy_notifyer_thread(void)
{
    assert(NULL != notifyer_thread);
    (void)ani_sem_wait(notifyer_lock);
    if (0 != destroy_notifyer_semaphores())
    {
        return 1;
    }
    if (0 != ani_thread_cancel(notifyer_thread))
    {
        ERROR("Could not cancel notifyer thread: %s\n", xstrerror());
        return 1;
    }
    xfree(ani_thread_t, notifyer_thread);
    DEBUG("Destroyed notifyer thread\n", NULL);
    return 0;
}
