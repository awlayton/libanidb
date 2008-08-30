/*
 *  test_misc.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 09.02.07.
 *  Copyright 2007 Andreas Meingast. All rights reserved.
 *
 *  $Id: test_misc.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#include <anidb.h>

#include "test.h"

int test_misc_setup(void)
{
    ani_response_t *response = NULL;
    
    ani_set_username(TEST_USER);
    ani_set_password(TEST_PASSWD);
    if (0 == ani_open_connection(NULL, 0)) 
    {
        response = ani_login();
        if (ANI_STATUS_LOGIN_ACCEPTED != response->status_code &&
            ANI_STATUS_LOGIN_ACCEPTED_NEW_VERSION != response->status_code)
        {
            if (0 != ani_close_connection()) TEST_ERROR();
            ani_free_response(response);
            TEST_ERROR();
            return 1;
        }
        ani_free_response(response);
        return 0;
    }
    else
    {
        TEST_ERROR();
        return 1;
    }
}

void test_misc_teardown(void)
{
    ani_response_t *response = NULL;
    
    response = ani_logout();
    if (ANI_STATUS_LOGGED_OUT != response->status_code) TEST_ERROR();
    ani_free_response(response);
    if (0 != ani_close_connection()) TEST_ERROR();
}

void test_misc_ping(void)
{
    ani_response_t *response = NULL;
    
    response = ani_ping();
    if (ANI_STATUS_PONG != response->status_code) TEST_ERROR();
    ani_free_response(response);
}

void test_misc_encoding(void)
{
    ani_response_t *response = NULL;

    response = ani_encoding("utf-8");
    if (ANI_STATUS_ENCODING_CHANGED != response->status_code) TEST_ERROR();
    ani_free_response(response);
    response = ani_encoding("foobar");
    if (ANI_STATUS_ENCODING_NOT_SUPPORTED != response->status_code) 
    {
        TEST_ERROR();
    }
    /*  necessary, because we get logged out with a bad encoding */
    else 
    {
        ani_relogin();
    }
    ani_free_response(response);
}

void test_misc_sendmsg(void)
{
    ani_response_t *response = NULL;

    response = ani_sendmsg(TEST_USER, "testmsg", "testbody");
    if (ANI_STATUS_SENDMSG_SUCCESSFUL != response->status_code) TEST_ERROR();
    ani_free_response(response);
}

void test_misc_user(void)
{
    ani_response_t *response = NULL;
    
    response = ani_user(TEST_USER);
    if (ANI_STATUS_USER != response->status_code) TEST_ERROR();
    ani_free_response(response);
}

void test_misc_uptime(void)
{
    ani_response_t *response = NULL;
    
    response = ani_uptime();
    if (ANI_STATUS_UPTIME != response->status_code) TEST_ERROR();
    ani_free_response(response);
}

void test_misc_version(void)
{
    ani_response_t *response = NULL;
    
    response = ani_version();
    if (ANI_STATUS_VERSION != response->status_code) TEST_ERROR();
    ani_free_response(response);
}

void test_misc_stats(void)
{
    /*  disabled on serverside */
}

void test_misc_top(void)
{
    /* disabled on serverside */
}

void test_misc_vote_by_anime_id(void)
{
    ani_response_t *response = NULL;

    response = ani_vote_by_anime_id(1, TEST_ANIME_ID, 100, 1);
    if (ANI_STATUS_VOTED != response->status_code &&
        ANI_STATUS_VOTE_UPDATED != response->status_code) TEST_ERROR();
    ani_free_response(response);
}

void test_misc_vote_by_aname(void)
{
    ani_response_t *response = NULL;
    
    response = ani_vote_by_aname(1, TEST_ANIME, 100, 1);
    if (ANI_STATUS_VOTED != response->status_code &&
        ANI_STATUS_VOTE_UPDATED != response->status_code) TEST_ERROR();
    ani_free_response(response);
}

void test_misc_get_random_anime(void)
{
    ani_response_t *response = NULL;
    
    response = ani_get_random_anime(0);
    if (ANI_STATUS_ANIME != response->status_code) TEST_ERROR();
    ani_free_response(response);
}
