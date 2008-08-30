/*
 *  response.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: response.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#include <anidb.h>

/*
 * TODO: crashes on unformatted input. introduce sanity checks
 */

static const char *parse_raw_response(const char *raw,
    ani_response_t *response);
static const char *parse_tag_response(const char *raw,
    ani_response_t *response);
static const char *parse_login_response(const char *raw,
    ani_response_t *response);
static const char *parse_msg_and_data(const char *raw,
    ani_response_t *response);
static const char *parse_notification_response(const char *raw,
    ani_response_t *response);

ani_response_t *ani_create_response(const char *raw)
{
    ani_response_t *response =
        (ani_response_t *)xmalloc(sizeof(ani_response_t));

    assert(NULL != raw);
    if (strlen(raw) > RAW_LEN)
    {
        WARN("Incoming message too long\n", strlen(raw));
        response->status_code = ANI_STATUS_MALFORMED_RESPONSE;
        (void)xstrncpy(response->msg, "Received message is too long (%d)\n",
            strlen(raw));
        (void)xstrncpy(response->tag, TAG_SERVER, TAG_LEN - 1);
    }
    else
    {
        /*  deliberately ignore the return value; no further parsing after
            parse_raw_response  */
        (void)parse_raw_response(raw, response);
    }
    return response;
}

void ani_free_response(ani_response_t *response)
{
    xfree(ani_response_t, response);
}

static const char *parse_raw_response(const char *raw, ani_response_t *response)
{
    const char *ptr = raw;

    assert(NULL != raw);
    assert(NULL != response);
    /*  we already have an authenticated connection established...
        this is a reply to some request */
    if (0 == atoi(raw)) // FIXME: replace with atoi
    {
        ptr = parse_tag_response(raw, response);
    }
    while ('\0' != *ptr && ' ' == *ptr) *ptr++;
    if (0 == atoi(ptr))
    {
        ERROR("Malformed message detected... no status code present\n", NULL);
        response->status_code = ANI_STATUS_MALFORMED_RESPONSE;
        (void)xstrncpy(response->msg, "No status code present in msg",
            TAG_LEN - 1);
        (void)xstrncpy(response->tag, TAG_SERVER, TAG_LEN - 1);
        return NULL;
    }
    /*  get the status code (also tagged messages have those!) */
    response->status_code = atoi(ptr);
    DEBUG("Parsed status_code: %d\n", response->status_code);
    /*  hop to the next word */
    while (' ' != *ptr) *ptr++;
    switch (response->status_code)
    {
        /*  if we got timed out... make sure that our system knows about it */
        case ANI_STATUS_LOGIN_FIRST:
            if (ANI_STATUS_ENABLED(STATUS_LOGGED_IN))
            {
                /*  FIXME: return an appropriate error! */
                ANI_DISABLE_STATUS(STATUS_LOGGED_IN);
            }
            break;
        /*  notifications are treated in a special fashion, since they
            have to be prepped to not enter the response_q */
        case ANI_STATUS_NOTIFICATION_NOTIFY:
        case ANI_STATUS_NOTIFICATION_MESSAGE:
        case ANI_STATUS_NOTIFICATION_BUDDY:
        case ANI_STATUS_NOTIFICATION_SHUTDOWN:
            ptr = parse_notification_response(ptr, response);
            break;
        /*  also different from standard responses, because we get the
            session key */
        case ANI_STATUS_LOGIN_ACCEPTED:
        case ANI_STATUS_LOGIN_ACCEPTED_NEW_VERSION:
            ptr = parse_login_response(ptr, response);
            break;
        /*  the  problem with following status codes is, that the request is
            ignored by the server and we get some kind of error returned
            (additionally we have no tag on the responses, so we have to handle
            them in a special way)
            since only correctly tagged responses enter the response_q, there
            are three additional tags to handle the following messages:
                * TAG_BANNED
                * TAG_UNKNOWN
                * TAG_SERVER

            whenever we store one of the following messages in the response_q,
            they will be delivered ASAP to the first ani_get_response call to
            the response_q.
            in the end, the library-user has to deal with those messages,
            because there isn't really much we can do from here on */
        case ANI_STATUS_BANNED:
            xstrncpy(response->tag, TAG_BANNED, TAG_LEN - 1);
            break;
        case ANI_STATUS_UNKNOWN_COMMAND:
            xstrncpy(response->tag, TAG_UNKNOWN, TAG_LEN - 1);
            break;
        case ANI_STATUS_ILLEGAL_INPUT_OR_ACCESS_DENIED:
        case ANI_STATUS_INTERNAL_SERVER_ERROR:
        case ANI_STATUS_OUT_OF_SERVICE:
        case ANI_STATUS_SERVER_BUSY:
            xstrncpy(response->tag, TAG_SERVER, TAG_LEN - 1);
            break;
        default:
            break;
    }
    /*  finally get the message- and data-information */
    return parse_msg_and_data(ptr, response);
}

static const char *parse_tag_response(const char *raw, ani_response_t *response)
{
    int i = 0;

    assert(NULL != raw);
    assert(NULL != response);
    while ('\0' != *raw && ' ' != *raw && i < TAG_LEN)
    {
        response->tag[i++] = *raw++;
    }
    response->tag[i] = '\0';
    *raw++;
    DEBUG("Parsed tag: %s\n", response->tag);
    return raw;
}

static const char *parse_login_response(const char *raw,
    ani_response_t *response)
{
    int i = 0;
    char session_key[SESSION_LEN] = { '\0' };

    assert(NULL != raw);
    assert(NULL != response);
    while ('\0' != *raw && ' ' == *raw) *raw++;
    while ('\0' != *raw && ' ' != *raw && i < SESSION_LEN)
    {
        session_key[i++] = *raw++;
    }
    *raw++;
    DEBUG("Parsed session key: %s\n", session_key);
    ani_set_session(session_key);
    return raw;
}

static const char *parse_msg_and_data(const char *raw, ani_response_t *response)
{
    int i = 0;

    assert(NULL != raw);
    assert(NULL != response);
    while ('\0' != *raw && ' ' == *raw) *raw++;
    while ('\0' != *raw && '\n' != *raw && i < RAW_LEN)
    {
        response->msg[i++] = *raw++;
    }
    response->msg[i] = '\0';
    *raw++;
    DEBUG("Parsed msg: %s\n", response->msg);
    xstrncpy(response->data, raw, RAW_LEN - 1);
    /*  kill the last character (a linefeed), because it's useless */
    if (response->data[strlen(response->data) - 1] == '\n')
    {
        response->data[strlen(response->data) - 1] = '\0';
    }
    DEBUG("Parsed data: %s\n", response->data);
    /*  end of message */
    return NULL;
}

static const char *parse_notification_response(const char *raw,
    ani_response_t *response)
{
    assert(NULL != raw);
    assert('\0' != *raw);
    assert(NULL != response);
    while ('\0' != *raw && ' ' == *raw) raw++;
    response->notify_code = atoi(raw);
    while ('\0' != *raw && ' ' != *raw) raw++;
    while ('\0' != *raw && ' ' == *raw) raw++;
    DEBUG("Parsed notify_code: %d\n", response->notify_code);
    return raw;
}
