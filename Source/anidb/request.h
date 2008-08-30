/*
 *  request.h
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: request.h 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#ifndef ANIDB_REQUEST_H
#define ANIDB_REQUEST_H

#include <anidb/net.h>
#include <anidb/response.h>
#include <anidb/utils.h>

ANI_BEGIN_C_DECLS

typedef struct _ani_request_t
{
    char msg[RAW_LEN];
    char tag[TAG_LEN];
    char session[SESSION_LEN];
}   ani_request_t;

ani_request_t *ani_create_request(const char *raw_request);
ani_response_t *ani_send_request(const ani_request_t *request);

ani_response_t *ani_send_retry_request(const ani_request_t *request,
    int retries);

void ani_free_request(ani_request_t *request);

ANI_END_C_DECLS

#endif /* ANIDB_REQUEST_H */
