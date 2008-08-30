/*
 *  main.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 11.01.07.
 *  Copyright 2007 Andreas Meingast. All rights reserved.
 *
 *  $Id: main.c 9 2007-03-10 16:03:07Z ameingast
 */
 
/*
 *  A CLI interface to the ANIDB server which is mainly used to debug the
 *  libanidb components.
 *
 *  it features support for notifications (via default callbacks) and basically
 *  any other anidb-command (as commands are sent in raw).
 */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#include "anidb.h"

#define PROMPT      "[ANISHELL] > "

static void sighandler(int signal);
static void usage(const char **argv);

static void file_callback(ani_push_file_notify_t *notification);
static void msg_callback(ani_push_msg_notify_t *notification);
static void buddy_callback(ani_push_buddy_notify_t *notification);
static void shutdown_callback(ani_push_shutdown_notify_t *notification);

/*
 *  main entry point which will launch (given the correct arguments)
 *  a connection to the anidb-server and provide a very basic shell
 *  interface
 */
int main(int argc, char **argv)
{
    char buf[RAW_LEN] = { '\0' };
    ani_response_t *response = NULL;
    /*	exactly two arguments are required: username and p/w */
    if (argc != 3)
    {
        usage((const char **)argv);
        return EXIT_FAILURE;
    }
    /*	hookup a cleanup mechanism */
    signal(SIGINT, sighandler);
    /*  hookup callbacks */
    ani_register_file_notify_callback(file_callback);
    ani_register_msg_notify_callback(msg_callback);
    ani_register_buddy_notify_callback(buddy_callback);
    ani_register_shutdown_notify_callback(shutdown_callback);
    /*	open low level connection */
    if (0 != ani_open_connection(NULL, 0))
    {
        ERROR("Could not open connection to anidb-server\n", NULL);
        return EXIT_FAILURE;
    }
    /*	register credentials */
    ani_set_username(argv[1]);
    ani_set_password(argv[2]);
    /*	login call to authorize against the anidb server */
    response = ani_login();
    /*	we are all good */
    if (ANI_STATUS_LOGIN_ACCEPTED == response->status_code ||
        ANI_STATUS_LOGIN_ACCEPTED_NEW_VERSION == response->status_code)
    {
        free(response);
        free(ani_start_notification_service(1,1,1));
        /*	anidb shell */
        for (;;)
        {
            (void)printf(PROMPT);
            /*	get the command from the CLI */
            if (NULL == fgets(buf, sizeof(char) * RAW_LEN, stdin))
            {
                break;
            }
            /*	truncate the \n character */
            buf[strlen(buf) - 1] = '\0';
            /*	send the command to the server */
            response = ani_send_retry_request(ani_create_request(buf), 2);
            /*	show the answer (even if it contains errors) */
            (void)fprintf(stdout, "%s :: %s\n", response->msg, response->data);
            /*	finally cleanup for next iteration */
            xfree(ani_response_t, response);
            (void)memset(buf, 0xfc, RAW_LEN);
        }
    }
    /*	probably bad p/w or user */
    else
    {
        (void)fprintf(stderr, "Could not login: %s\n", response->msg);
    }
    return ani_close_connection();
}

/*
 *  the registered sighandler that will take care of ^C inputs
 */
static void sighandler(int signal)
{
    (void)printf("\nCaught signal. Shutting down...\n");
    exit(ani_close_connection());
}

/*
 *  some basic infos on howto use this shell interface
 */
static void usage(const char **argv)
{
    ERROR("USAGE:\n%s <username> <password>\n", *argv);
}

static void file_callback(ani_push_file_notify_t *notification)
{
    (void)printf("\n>> { (ID = %d), (Date = %d), (Count = %d), (Name = %s) }\n",
        notification->anime_id, notification->date, notification->count,
        notification->anime_title);
}

static void msg_callback(ani_push_msg_notify_t *notification)
{
    (void)printf("\n>> { (Type = %d), (Date = %d), (Sender UID = %d), "
        " (Sender Name = %s), (Subject = %s) }\n", notification->type,
        notification->date, notification->sender_uid,
        notification->sender_name, notification->subject);
}

static void buddy_callback(ani_push_buddy_notify_t *notification)
{
    (void)printf("\n>> { (Buddy UID = %d), (Event Type = %d) }\n",
        notification->buddy_uid, notification->event_type);
}

static void shutdown_callback(ani_push_shutdown_notify_t *notification)
{
    (void)printf("\n>> { (Offline time = %d), (Comment = %s) }\n",
        notification->offline_time, notification->comment);
}

