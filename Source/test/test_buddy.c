/*
 *  test_buddy.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 09.02.07.
 *  Copyright 2007 Andreas Meingast. All rights reserved.
 *
 *  $Id: test_buddy.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#include <anidb.h>

#include "test.h"

int test_buddy_setup(void)
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
        ani_free_response(ani_buddydel(TEST_USER_ID));
        return 0;
    }
    else
    {
        TEST_ERROR();
        return 1;
    }
}

void test_buddy_teardown(void)
{
    ani_response_t *response = NULL;
    
    ani_free_response(ani_buddydel(TEST_USER_ID));
    response = ani_logout();
    if (ANI_STATUS_LOGGED_OUT != response->status_code) TEST_ERROR();
    ani_free_response(response);
    if (0 != ani_close_connection()) TEST_ERROR();
}

void test_buddy_buddyadd_by_id_and_buddydel(void)
{
    ani_response_t *response = NULL;
    
    response = ani_buddyadd_by_id(TEST_USER_ID);
    if (ANI_STATUS_BUDDY_ADDED != response->status_code) TEST_ERROR();
    ani_free_response(response);
    response = ani_buddyadd_by_id(999999999);
    if (ANI_STATUS_NO_SUCH_USER != response->status_code) TEST_ERROR();
    ani_free_response(response);
    response = ani_buddydel(TEST_USER_ID);
    if (ANI_STATUS_BUDDY_DELETED != response->status_code) TEST_ERROR();
    ani_free_response(response);
}

void test_buddy_buddyadd_by_name_and_buddydel(void)
{
    ani_response_t *response = NULL;
    
    response = ani_buddyadd_by_name(TEST_USER);
    if (ANI_STATUS_BUDDY_ADDED != response->status_code) TEST_ERROR();
    ani_free_response(response);
    response = ani_buddyadd_by_name("f23ursdfkj");
    if (ANI_STATUS_NO_SUCH_USER != response->status_code) TEST_ERROR();
    ani_free_response(response);
    response = ani_buddydel(TEST_USER_ID);
    if (ANI_STATUS_BUDDY_DELETED != response->status_code) TEST_ERROR();
    ani_free_response(response);
}

void test_buddy_buddyaccept(void)
{
    /*  TODO */
}

void test_buddy_buddydeny(void)
{
    /*  TODO */
}

void test_buddy_buddylist(void)
{
    ani_response_t *response = NULL;
    
    response = ani_buddylist(0);
    if (ANI_STATUS_BUDDY_LIST != response->status_code) TEST_ERROR();
    ani_free_response(response);
}

void test_buddy_buddystate(void)
{
    ani_response_t *response = NULL;
    
    response = ani_buddystate(0);
    if (ANI_STATUS_BUDDY_STATE != response->status_code) TEST_ERROR();
    ani_free_response(response);
}
