/*
 *  test_mylist.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 09.02.07.
 *  Copyright 2007 Andreas Meingast. All rights reserved.
 *
 *  $Id: test_mylist.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#include "test.h"

int test_mylist_setup(void)
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

void test_mylist_teardown(void)
{
    ani_response_t *response = NULL;
    
    response = ani_logout();
    if (ANI_STATUS_LOGGED_OUT != response->status_code) TEST_ERROR();
    ani_free_response(response);
    if (0 != ani_close_connection()) TEST_ERROR();
}

void test_mylist_mylist_by_list_id(void)
{

}

void test_mylist_mylist_by_file_id(void)
{

}

void test_mylist_mylist_by_size_and_md4(void)
{

}

void test_mylist_mylist_by_aname_and_gname(void)
{

}

void test_mylist_mylist_by_aname_and_group_id(void)
{

}

void test_mylist_mylist_by_anime_id_and_gname(void)
{

}

void test_mylist_mylist_by_by_aid_and_gid(void)
{

}

void test_mylist_edit_mylist_by_list_id(void)
{

}

void test_mylist_add_mylist_by_file_id(void)
{

}

void test_mylist_add_mylist_by_size_and_md4(void)
{

}

void test_mylist_add_mylist_by_aname(void)
{

}

void test_mylist_add_mylist_by_aname_and_gname(void)
{

}

void test_mylist_add_mylist_by_aname_and_gid(void)
{

}

void test_mylist_add_mylist_by_aid_and_gname(void)
{

}

void test_mylist_add_mylist_by_aid_and_gid(void)
{

}

void test_mylist_del_mylist_by_list_id(void)
{

}

void test_mylist_del_mylist_by_file_id(void)
{

}

void test_mylist_del_mylist_by_aname(void)
{

}

void test_mylist_del_mylist_by_aname_and_gname(void)
{

}

void test_mylist_del_mylist_by_aname_and_gid(void)
{

}

void test_mylist_del_mylist_by_aid_and_gid(void)
{

}

void test_mylist_myliststats(void)
{

}
