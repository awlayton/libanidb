/*
 *  commands.h
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: commands.h 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#ifndef ANIDB_COMMANDS_H
#define ANIDB_COMMANDS_H

#include <anidb/request.h>
#include <anidb/response.h>
#include <stdio.h>
#include <stdarg.h>

/**
 *  @param fmt  The format string, that is used to form the raw-command string
 *  @parm ...   Varargs that will be printed into the format string
 *  @return     The response from the server; even if no answer received, there
 *              is never the chance of returning a NULL value. If errors
 *              appear, an error code will be set in the response data.
 *  @see        ani_send_retry_request()
 */
static inline ani_response_t *ani_send_cmd(const char *fmt, ...)
{
    char raw[RAW_LEN] = { '\0' };
    va_list ap;

    assert(NULL != fmt);
    va_start(ap, fmt);
    (void)vsnprintf(raw, RAW_LEN, fmt, ap);
    va_end(ap);
    return ani_send_retry_request(ani_create_request(raw), 0);
}

#define ANIDB_CMD_AUTH                          "AUTH user=%s&pass=%s&protover=%i&client=libanidb&clientver=%d"
#define ANIDB_CMD_AUTH_NAT                      "AUTH user=%s&pass=%s&protover=%i&client=libanidb&clientver=%d&nat=1"
#define ANIDB_CMD_LOGOUT                        "LOGOUT"

#define ANIDB_CMD_PUSH                          "PUSH notify=%d&msg=%d&buddy=%d"
#define ANIDB_CMD_PUSHACK                       "PUSHACK nid=%d"
#define ANIDB_CMD_NOTIFY                        "NOTIFY buddy=%d"
#define ANIDB_CMD_NOTIFYLIST                    "NOTIFYLIST"
#define ANIDB_CMD_NOTIFYGET                     "NOTIFYGET type=%c&id=%d"
#define ANIDB_CMD_NOTIFYACK                     "NOTIFYACK type=%c&id=%d"

#define ANIDB_CMD_BUDDYADD_BY_UID               "BUDDYADD uid=%d"
#define ANIDB_CMD_BUDDYADD_BY_NAME              "BUDDYADD uname=%s"
#define ANIDB_CMD_BUDDYDEL                      "BUDDYDEL uid=%d"
#define ANIDB_CMD_BUDDYACCEPT                   "BUDDYACCEPT uid=%d"
#define ANIDB_CMD_BUDDYDENY                     "BUDDYDENY uid=%d"
#define ANIDB_CMD_BUDDYLIST                     "BUDDYLIST startat=%d"
#define ANIDB_CMD_BUDDYSTATE                    "BUDDYSTATE startat=%d"

#define ANIDB_CMD_ANIME_BY_AID                  "ANIME aid=%d"
#define ANIDB_CMD_ANIME_BY_AID_AND_ACODE        "ANIME aid=%d&acode=%d"
#define ANIDB_CMD_ANIME_BY_NAME                 "ANIME aname=%s"
#define ANIDB_CMD_ANIME_BY_NAME_AND_ACODE       "ANIME aname=%s&acode=%d"
#define ANIDB_CMD_EPISODE_BY_EID                "EPISODE eid=%d"
#define ANIDB_CMD_EPISODE_BY_ANAME_AND_EPNO     "EPISODE aname=%s&epno=%d"
#define ANIDB_CMD_EPISODE_BY_AID_AND_EPNO       "EPISODE aid=%d&epno=%d"
#define ANIDB_CMD_FILE_BY_FID                   "FILE fid=%d"
#define ANIDB_CMD_FILE_BY_FID_AND_FCODE         "FILE fid=%d&fcode=%d&acode=%d"
#define ANIDB_CMD_FILE_BY_MD4                   "FILE size=%d&ed2k=%s"
#define ANIDB_CMD_FILE_BY_MD4_AND_FCODE         "FILE size=%d&ed2k=%s&fcode=%d&acode=%d"
#define ANIDB_CMD_GROUP_BY_GID                  "GROUP gid=%d"
#define ANIDB_CMD_GROUP_BY_GNAME                "GROUP gname=%s"
#define ANIDB_CMD_PRODUCER_BY_PID               "PRODUCER pid=%d"
#define ANIDB_CMD_PRODUCER_BY_PNAME             "PRODUCER pname=%s"

#define ANIDB_CMD_MYLIST_BY_LID                 "MYLIST lid=%d"
#define ANIDB_CMD_MYLIST_BY_FID                 "MYLIST fid=%d"
#define ANIDB_CMD_MYLIST_BY_MD4                 "MYLIST size=%d&ed2k=%s"
#define ANIDB_CMD_MYLIST_BY_ANAME_AND_GNAME     "MYLIST aname=%s&gname=%s&epno=%d"
#define ANIDB_CMD_MYLIST_BY_ANAME_AND_GID       "MYLIST aname=%s&gid=%d&epno=%d"
#define ANIDB_CMD_MYLIST_BY_AID_AND_GNAME       "MYLIST aid=%d&gname=%s&epno=%d"
#define ANIDB_CMD_MYLIST_BY_AID_AND_GID         "MYLIST aid=%d&gid=%d&epno=%d"
#define ANIDB_CMD_MYLISTADD_BY_LID              "MYLISTADD lid=%d&edit=1&state=%d&viewed=%d&source=%s&storage=%s&other=%s"
#define ANIDB_CMD_MYLISTADD_BY_FID              "MYLISTADD fid=%d&edit=1&state=%d&viewed=%d&source=%s&storage=%s&other=%s"
#define ANIDB_CMD_MYLISTADD_BY_MD4              "MYLISTADD size=%d&ed2k=%s&edit=1&state=%d&viewed=%d&source=%s&storage=%s&other=%s"
#define ANIDB_CMD_MYLISTADD_BY_ANAME            "MYLISTADD aname=%s&edit=1&state=%d&viewed=%d&source=%s&storage=%s&other=%s"
#define ANIDB_CMD_MYLISTADD_BY_ANAME_AND_GNAME  "MYLISTADD aname=%s&gname=%s&epno=%d&edit=1&state=%d&viewed=%d&source=%s&storage=%s&other=%s"
#define ANIDB_CMD_MYLISTADD_BY_ANAME_AND_GID    "MYLISTADD aname=%s&gid=%d&epno=%d&edit=1&state=%d&viewed=%d&source=%s&storage=%s&other=%s"
#define ANIDB_CMD_MYLISTADD_BY_AID_AND_GNAME    "MYLISTADD aid=%d&gname=%s&epno=%d&edit=1&state=%d&viewed=%d&source=%s&storage=%s&other=%s"
#define ANIDB_CMD_MYLISTADD_BY_AID_AND_GID      "MYLISTADD aid=%d&gid=%d&epno=%d&edit=1&state=%d&viewed=%d&source=%s&storage=%s&other=%s"
#define ANIDB_CMD_MYLISTDEL_BY_LID              "MYLISTDEL lid=%d"
#define ANIDB_CMD_MYLISTDEL_BY_FID              "MYLISTDEL fid=%d"
#define ANIDB_CMD_MYLISTDEL_BY_ANAME            "MYLISTDEL aname=%s"
#define ANIDB_CMD_MYLISTDEL_BY_ANAME_AND_GNAME  "MYLISTDEL aname=%s&gname=%s&epno=%d"
#define ANIDB_CMD_MYLISTDEL_BY_ANAME_AND_GID    "MYLISTDEL aname=%s&gid=%d&epno=%d"
#define ANIDB_CMD_MYLISTDEL_BY_AID_AND_GID      "MYLISTDEL aid=%d&gid=%d&epno=%d"
#define ANIDB_CMD_MYLISTSTATS                   "MYLISTSTATS"

#define ANIDB_CMD_PING                          "PING"
#define ANIDB_CMD_ENCRYPT                       "ENCRYPT user=%s&type=%d"
#define ANIDB_CMD_ENCODING                      "ENCODING name=%s"
#define ANIDB_CMD_SENDMSG                       "SENDMSG to=%s&title=%s&body=%s"
#define ANIDB_CMD_USER                          "USER user=%s"
#define ANIDB_CMD_UPTIME                        "UPTIME"
#define ANIDB_CMD_VERSION                       "VERSION"
#define ANIDB_CMD_STATS                         "STATS"
#define ANIDB_CMD_TOP                           "TOP"

#define ANIDB_CMD_VOTE_BY_AID                   "VOTE type=%d&id=%d&value=%d&epno=%d"
#define ANIDB_CMD_VOTE_BY_ANAME                 "VOTE type=%d&name=%s&value=%d&epno=%d"
#define ANIDB_CMD_GET_RANDOM_ANIME              "RANDOMANIME type=%d"

#endif /* ANIDB_COMMANDS_H */
