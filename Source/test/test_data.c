/*
 *  test_data.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 09.02.07.
 *  Copyright 2007 Andreas Meingast. All rights reserved.
 *
 *  $Id: test_data.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#include "test.h"

int test_data_setup(void)
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

void test_data_teardown(void)
{
    ani_response_t *response = NULL;
    
    response = ani_logout();
    if (ANI_STATUS_LOGGED_OUT != response->status_code) TEST_ERROR();
    ani_free_response(response);
    if (0 != ani_close_connection()) TEST_ERROR();
}

void test_data_get_anime_by_anime_id(void)
{
    ani_response_t *response = NULL;
    
    response = ani_get_anime_by_anime_id(TEST_ANIME_ID);
    if (ANI_STATUS_ANIME != response->status_code) TEST_ERROR();
    ani_free_response(response);
}

void test_data_get_anime_by_anime_id_and_acode(void)
{
    /*  TODO */
}

void test_data_get_anime_by_name(void)
{
    ani_response_t *response = NULL;
    
    response = ani_get_anime_by_name(TEST_ANIME);
    if (ANI_STATUS_ANIME != response->status_code) TEST_ERROR();
    ani_free_response(response);
}

void test_data_get_anime_by_name_and_acode(void)
{
    /*  TODO */
}


void test_data_get_episode_by_id(void)
{
    ani_response_t *response = NULL;
    
    response = ani_get_episode_by_id(TEST_EPISODE_1_ID);
    if (ANI_STATUS_EPISODE != response->status_code) TEST_ERROR();
    ani_free_response(response);
    response = ani_get_episode_by_id(TEST_EPISODE_2_ID);
    if (ANI_STATUS_EPISODE != response->status_code) TEST_ERROR();
    ani_free_response(response);
}

void test_data_get_episode_by_anime_name(void)
{
    ani_response_t *response = NULL;
    
    response = ani_get_episode_by_anime_name(TEST_ANIME, 1);
    if (ANI_STATUS_EPISODE != response->status_code) TEST_ERROR();
    ani_free_response(response);
}

void test_data_get_episode_by_anime_id(void)
{
    ani_response_t *response = NULL;
    
    response = ani_get_episode_by_anime_id(TEST_ANIME_ID, 1);
    if (ANI_STATUS_EPISODE != response->status_code) TEST_ERROR();
    ani_free_response(response);
}

void test_data_get_file_by_id(void)
{
    /*  TODO */
}

void test_data_get_file_by_id_and_fcode(void)
{
    /*  TODO */
}

void test_data_get_file_by_md4(void)
{
    /*  TODO */    
}

void test_data_get_file_by_md4_and_fcode(void)
{
    /*  TODO */   
}

void test_data_get_group_by_id(void)
{
    ani_response_t *response = NULL;
    
    response = ani_get_group_by_id(TEST_GROUP_ID);
    if (ANI_STATUS_GROUP != response->status_code) TEST_ERROR();
    ani_free_response(response);
}

void test_data_get_group_by_name(void)
{
    ani_response_t *response = NULL;
    
    response = ani_get_group_by_name(TEST_GROUP_NAME);
    if (ANI_STATUS_GROUP != response->status_code) TEST_ERROR();
    ani_free_response(response);
}

void test_data_get_producer_by_id(void)
{
    ani_response_t *response = NULL;
    
    response = ani_get_producer_by_id(TEST_PRODUCER_ID);
    if (ANI_STATUS_PRODUCER != response->status_code) TEST_ERROR();
    ani_free_response(response);
}

void test_data_get_producer_by_name(void)
{
    ani_response_t *response = NULL;
    
    response = ani_get_producer_by_name(TEST_PRODUCER_NAME);
    if (ANI_STATUS_PRODUCER != response->status_code) TEST_ERROR();
    ani_free_response(response);
}
