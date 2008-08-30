/*
 *  response.h
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: response.h 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#ifndef ANIDB_RESPONSE_H
#define ANIDB_RESPONSE_H

#include <anidb/net.h>
#include <anidb/utils.h>

ANI_BEGIN_C_DECLS

#define TAG_BANNED              "BAN"
#define TAG_UNKNOWN             "UNK"
#define TAG_SERVER              "SRV"

typedef struct _ani_response_t
{
    int status_code;
    int notify_code;
    int truncated;
    char data[RAW_LEN];
    char msg[RAW_LEN];
    char tag[TAG_LEN];
}   ani_response_t;

ani_response_t *ani_create_response(const char *raw);
void ani_free_response(ani_response_t *);

ANI_END_C_DECLS

#endif /* ANIDB_RESPONSE_H */
