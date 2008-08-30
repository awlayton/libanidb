/*
 *  misc.h
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: misc.h 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#ifndef ANIDB_MISC_H
#define ANIDB_MISC_H

#include <anidb/response.h>
#include <anidb/utils.h>

ANI_BEGIN_C_DECLS

ani_response_t *ani_ping(void);
ani_response_t *ani_encoding(const char *encoding_name);
ani_response_t *ani_sendmsg(const char *username, const char *title,
    const char *body);
ani_response_t *ani_user(const char *username);
ani_response_t *ani_uptime(void);
ani_response_t *ani_version(void);
ani_response_t *ani_stats(void);
ani_response_t *ani_top(void);

ani_response_t *ani_vote_by_anime_id(short type, int anime_id, int vote_value,
    int episode_number);
ani_response_t *ani_vote_by_aname(short type, const char *aname, int vote_value,
    int episode_number);
ani_response_t *ani_get_random_anime(int type);

ANI_END_C_DECLS

#endif /* ANIDB_MISC_H */
