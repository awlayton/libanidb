/*
 *  test_net.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 09.02.07.
 *  Copyright 2007 Andreas Meingast. All rights reserved.
 *
 *  $Id: test_net.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#include <anidb.h>

#include "test.h"

void test_net_status(void)
{
    ANI_ENABLE_STATUS(STATUS_CONNECTED);
    if (!ANI_STATUS_ENABLED(STATUS_CONNECTED)) TEST_ERROR();
    ANI_ENABLE_STATUS(STATUS_LOGGED_IN);
    if (!ANI_STATUS_ENABLED(STATUS_CONNECTED) ||
        !ANI_STATUS_ENABLED(STATUS_LOGGED_IN)) TEST_ERROR();
    ANI_ENABLE_STATUS(STATUS_NOTIFY_ENABLED);
    if (!ANI_STATUS_ENABLED(STATUS_CONNECTED) ||
        !ANI_STATUS_ENABLED(STATUS_LOGGED_IN) ||
        !ANI_STATUS_ENABLED(STATUS_NOTIFY_ENABLED)) TEST_ERROR();
    ANI_DISABLE_STATUS(STATUS_CONNECTED);
    if (ANI_STATUS_ENABLED(STATUS_CONNECTED) ||
        !ANI_STATUS_ENABLED(STATUS_LOGGED_IN) ||
        !ANI_STATUS_ENABLED(STATUS_NOTIFY_ENABLED)) TEST_ERROR();
    ANI_DISABLE_STATUS(STATUS_LOGGED_IN);
    if (ANI_STATUS_ENABLED(STATUS_CONNECTED) ||
        ANI_STATUS_ENABLED(STATUS_LOGGED_IN) ||
        !ANI_STATUS_ENABLED(STATUS_NOTIFY_ENABLED)) TEST_ERROR();
    ANI_DISABLE_STATUS(STATUS_NOTIFY_ENABLED);
    if (ANI_STATUS_ENABLED(STATUS_CONNECTED) ||
        ANI_STATUS_ENABLED(STATUS_LOGGED_IN) ||
        ANI_STATUS_ENABLED(STATUS_NOTIFY_ENABLED)) TEST_ERROR();
    /*  return with a cleaned STATUS state... 
        it's very important for other tests to work correctly */
}

void test_net_open_close_connection(void)
{
    if (0 != ani_open_connection(NULL, 0)) TEST_ERROR();
    if (0 != ani_close_connection()) TEST_ERROR();
}

void test_net_send(void)
{
    char raw[RAW_LEN] = { '\0' };
    
    if (0 == ani_open_connection(NULL, 0))
    {
        (void)strncat(raw, "UPTIME", RAW_LEN);
        if (0 >= ani_send(raw, RAW_LEN)) TEST_ERROR();
        if (0 != ani_close_connection()) TEST_ERROR();
    }
}
