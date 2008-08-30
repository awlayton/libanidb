/*
 *  test_auth.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 09.02.07.
 *  Copyright 2007 Andreas Meingast. All rights reserved.
 *
 *  $Id: test_auth.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#include <anidb.h>
#include <string.h>

#include "test.h"

void test_auth_username(void)
{
    ani_set_username(TEST_USER);
    if (0 != strcmp(TEST_USER, ani_username())) TEST_ERROR();
    ani_set_username("foo");
    if (0 != strcmp("foo", ani_username())) TEST_ERROR();
    ani_set_username("");
    if (0 != strcmp("", ani_username())) TEST_ERROR();
}

void test_auth_password(void)
{
    ani_set_password(TEST_PASSWD);
    if (0 != strcmp(TEST_PASSWD, ani_password())) TEST_ERROR();
    ani_set_password("");
    if (0 != strcmp("", ani_password())) TEST_ERROR();
}

void test_auth_session(void)
{
    ani_set_session("fooo");
    if (0 != strcmp("fooo", ani_session())) TEST_ERROR();
    ani_set_session("");
    if (0 != strcmp("", ani_session())) TEST_ERROR();
}

void test_auth_login_logout(void)
{
    ani_response_t *response = NULL;
    
    if (0 == ani_open_connection(NULL, 0))
    {
        ani_set_username(TEST_USER);
        ani_set_password(TEST_PASSWD);
        response = ani_login();
        if (ANI_STATUS_LOGIN_ACCEPTED != response->status_code &&
            ANI_STATUS_LOGIN_ACCEPTED_NEW_VERSION != response->status_code)
            TEST_ERROR();
        ani_free_response(response);
        response = ani_logout();
        if (ANI_STATUS_LOGGED_OUT != response->status_code) TEST_ERROR();
        ani_free_response(response);
        if (0 != ani_close_connection()) TEST_ERROR();
    }
}

void test_auth_relogin(void)
{
    ani_response_t *response = NULL;
    
    /*  not connected to server... therefore this one should be NULL */
    if (NULL != ani_relogin()) TEST_ERROR();
    if (0 == ani_open_connection(NULL, 0))
    {
        ani_set_username(TEST_USER);
        ani_set_password(TEST_PASSWD);
        response = ani_relogin();
        if (ANI_STATUS_LOGIN_ACCEPTED != response->status_code &&
            ANI_STATUS_LOGIN_ACCEPTED_NEW_VERSION != response->status_code)
            TEST_ERROR();
        ani_free_response(response);
        response = ani_relogin();
        if (ANI_STATUS_LOGIN_ACCEPTED != response->status_code &&
            ANI_STATUS_LOGIN_ACCEPTED_NEW_VERSION != response->status_code)
            TEST_ERROR();
        if (0 != ani_close_connection()) TEST_ERROR();
    }
}
