/*
 *  test_request.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 09.02.07.
 *  Copyright 2007 Andreas Meingast. All rights reserved.
 *
 *  $Id: test_request.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */
        
#include <anidb.h>

#include "test.h"

void test_request_has_tag(void)
{
    ani_request_t *request = NULL;
    char tag1[TAG_LEN] = { '\0' };
    char tag2[TAG_LEN] = { '\0' };
    
    request = ani_create_request("UPTIME");
    (void)strncpy(tag1, request->tag, TAG_LEN - 1);
    ani_free_request(request);
    request = ani_create_request("UPTIME");
    (void)strncpy(tag2, request->tag, TAG_LEN - 1);
    ani_free_request(request);
    if (0 == strcmp("", tag1)) TEST_ERROR();
    if (0 == strcmp("", tag2)) TEST_ERROR();
    if (0 == strcmp(tag1, tag2)) TEST_ERROR();
}

void test_request_has_session(void)
{
    ani_request_t *request = NULL;
    char session[SESSION_LEN] = { '\0' };
    
    (void)xstrncpy(session, ani_session(), SESSION_LEN - 1);
    ani_set_session("");
    request = ani_create_request("UPTIME");
    if (0 != strcmp("", request->session)) TEST_ERROR();
    ani_free_request(request);
    ani_set_session("FOO");
    request = ani_create_request("UPTIME");
    if (0 != strcmp("FOO", request->session)) TEST_ERROR();
    ani_free_request(request);
    ani_set_session(session);
}
