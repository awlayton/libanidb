/*
 *  notify.h
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: notify.h 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#ifndef ANIDB_NOTIFY_H
#define ANIDB_NOTIFY_H

#include <anidb/response.h>
#include <anidb/utils.h>

ANI_BEGIN_C_DECLS

typedef void (*ani_notify_file_callback)(ani_push_file_notify_t *notification);
typedef void (*ani_notify_msg_callback)(ani_push_msg_notify_t *notification);
typedef void (*ani_notify_buddy_callback)(
    ani_push_buddy_notify_t *notification);
typedef void (*ani_notify_shutdown_callback)(
    ani_push_shutdown_notify_t *notification);

typedef void (*ani_notifyget_msg_callback)(ani_notifyget_msg_t *msg);
typedef void (*ani_notifyget_notification_callback)(
    ani_notifyget_notification_t *notification);

ani_response_t *ani_start_notification_service(int files_added, int msg_added,
    int buddy_event);
ani_response_t *ani_stop_notification_service(void);
ani_response_t *ani_notify(int buddies);
ani_response_t *ani_notify_list(void);
ani_response_t *ani_notify_get(char type, int id);
ani_response_t *ani_notify_ack(char type, int id);
ani_response_t *ani_push_ack(int id);

void ani_file_notify(ani_push_file_notify_t *notification);
void ani_msg_notify(ani_push_msg_notify_t *notification);
void ani_buddy_notify(ani_push_buddy_notify_t *notification);
void ani_shutdown_notify(ani_push_shutdown_notify_t *notification);

void ani_msg_notifyget(ani_notifyget_msg_t *notification);
void ani_notification_notifyget(ani_notifyget_notification_t *notification);

void ani_register_file_notify_callback(ani_notify_file_callback func);
void ani_register_msg_notify_callback(ani_notify_msg_callback func);
void ani_register_buddy_notify_callback(ani_notify_buddy_callback func);
void ani_register_shutdown_notify_callback(ani_notify_shutdown_callback func);

void ani_register_msg_notifyget_callback(ani_notifyget_msg_callback func);
void ani_register_notification_notifyget_callback(
    ani_notifyget_notification_callback func);

ANI_END_C_DECLS

#endif /* ANIDB_NOTIFY_H */
