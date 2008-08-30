/*
 *  misc.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: misc.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#include <anidb.h>

ani_response_t *ani_ping(void)
{
    return ani_send_cmd(ANIDB_CMD_PING);
}

ani_response_t *ani_encoding(const char *encoding_name)
{
    assert(NULL != encoding_name);
    return ani_send_cmd(ANIDB_CMD_ENCODING, encoding_name);
}

ani_response_t *ani_sendmsg(const char *username, const char *title,
    const char *body)
{
    assert(NULL != username);
    assert(NULL != title);
    assert(NULL != body);
    return ani_send_cmd(ANIDB_CMD_SENDMSG, username, title, body);
}

ani_response_t *ani_user(const char *username)
{
    assert(NULL != username);
    return ani_send_cmd(ANIDB_CMD_USER, username);
}

ani_response_t *ani_uptime(void)
{
    return ani_send_cmd(ANIDB_CMD_UPTIME);
}

ani_response_t *ani_version(void)
{
    return ani_send_cmd(ANIDB_CMD_VERSION);
}

ani_response_t *ani_stats(void)
{
    return ani_send_cmd(ANIDB_CMD_STATS);
}

ani_response_t *ani_top(void)
{
    return ani_send_cmd(ANIDB_CMD_TOP);
}

ani_response_t *ani_vote_by_anime_id(short type, int anime_id, int vote_value,
    int episode_number)
{
    assert(type > 0);
    assert(anime_id > 0);
    assert(vote_value > 99);
    assert(vote_value < 1001);
    assert(episode_number > 0);
    return ani_send_cmd(ANIDB_CMD_VOTE_BY_AID, type, anime_id, vote_value,
        episode_number);
}

ani_response_t *ani_vote_by_aname(short type, const char *aname, int vote_value,
    int episode_number)
{
    assert(type > 0);
    assert(NULL != aname);
    assert(vote_value > 99);
    assert(vote_value < 1001);
    assert(episode_number > 0);
    return ani_send_cmd(ANIDB_CMD_VOTE_BY_ANAME, type, aname, vote_value,
        episode_number);
}

ani_response_t *ani_get_random_anime(int type)
{
    assert(type >= 0);
    return ani_send_cmd(ANIDB_CMD_GET_RANDOM_ANIME, type);
}
