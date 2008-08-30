/*
 *  request.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: request.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#include <anidb.h>
#include <stdlib.h>
#include <string.h>

#define ANI_DEFAULT_RETRIES 3

static void add_space(ani_request_t *request);
static void add_tag(ani_request_t *request);
static void add_session(ani_request_t *request);

ani_request_t *ani_create_request(const char *raw_request)
{
    ani_request_t *request = (ani_request_t *)xmalloc(sizeof(ani_request_t));

    assert(NULL != raw_request);
    (void)xstrncpy(request->msg, raw_request, RAW_LEN);
    add_space(request);
    add_tag(request);
    add_session(request);
    return request;
}

ani_response_t *ani_send_request(const ani_request_t *request)
{
    ani_response_t *response = NULL;
    ssize_t length = strlen(request->msg) * sizeof(char);
    ssize_t s_length = -1;

    assert(NULL != request);
    if (length != (s_length = ani_send((const void *)request->msg, length)))
    {
        response = (ani_response_t *)xmalloc(sizeof(ani_response_t));
        response->status_code = ANI_STATUS_SEND_FAILED;
        (void)xstrncpy(response->msg, xstrerror(), RAW_LEN - 1);
        return response;
    }
    if (NULL == (response = ani_get_response(request)))
    {
        response = (ani_response_t *)xmalloc(sizeof(ani_response_t));
        response->status_code = ANI_STATUS_SEND_FAILED;
        (void)xstrncpy(response->msg, "Communication process timed out",
            RAW_LEN - 1);
    }
    return response;
}

ani_response_t *ani_send_retry_request(const ani_request_t *request,
    int retries)
{
    int i = 0;
    ssize_t length = strlen(request->msg) * sizeof(char);
    ani_response_t *response = NULL;

    assert(NULL != request);
    retries = retries <= 0 ? ANI_DEFAULT_RETRIES : retries;
    for (i = 0; i < retries; ++i)
    {
        if (-1 == ani_send((const void *)request->msg, length) ||
            NULL == (response = ani_get_response(request)))
        {
            WARN("communication failed, retrying (iteration=%d)\n", i);
            continue;
        }
        return response;
    }
    WARN("ani_send failed, not retrying anymore\n", NULL);
    response = (ani_response_t *)xmalloc(sizeof(ani_response_t));
    response->status_code = ANI_STATUS_SEND_FAILED;
    (void)xstrncpy(response->msg, "Communication process timed out",
        RAW_LEN - 1);
    return response;
}

void ani_free_request(ani_request_t *request)
{
    xfree(ani_request_t, request);
}

static void add_space(ani_request_t *request)
{
    int i = 0;

    for (i = 0; i < RAW_LEN; i++)
    {
        if (request->msg[i] == ' ')
        {
            return;
        }
    }
    request->msg[strlen(request->msg)] = ' ';
}

static void add_tag(ani_request_t *request)
{
    static int counter = 0;

    assert(NULL != request);
    (void)snprintf(request->tag, TAG_LEN, "tag%d", counter++);
    (void)strncat(request->msg, "&tag=", RAW_LEN - xstrlen(request->msg));
    (void)strncat(request->msg, request->tag, RAW_LEN - xstrlen(request->msg));
}

static void add_session(ani_request_t *request)
{
    const char *session = ani_session();

    assert(NULL != request);
    if (NULL != session && '\0' != *session)
    {
        (void)xstrncpy(request->session, session, SESSION_LEN);
        (void)strncat(request->msg, "&s=",
            RAW_LEN - xstrlen(request->msg));
        (void)strncat(request->msg, request->session,
            RAW_LEN - xstrlen(request->msg));
    }
}
