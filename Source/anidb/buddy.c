/*
 *  buddy.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: buddy.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#include <anidb.h>

ani_response_t *ani_buddyadd_by_id(int buddy_uid)
{
    assert(buddy_uid > 0);
    return ani_send_cmd(ANIDB_CMD_BUDDYADD_BY_UID, buddy_uid);
}

ani_response_t *ani_buddyadd_by_name(const char *buddyname)
{
    assert(NULL != buddyname);
    return ani_send_cmd(ANIDB_CMD_BUDDYADD_BY_NAME, buddyname);
}

ani_response_t *ani_buddydel(int buddy_uid)
{
    assert(buddy_uid > 0);
    return ani_send_cmd(ANIDB_CMD_BUDDYDEL, buddy_uid);
}

ani_response_t *ani_buddyaccept(int buddy_uid)
{
    assert(buddy_uid > 0);
    return ani_send_cmd(ANIDB_CMD_BUDDYACCEPT, buddy_uid);
}

ani_response_t *ani_buddydeny(int buddy_uid)
{
    assert(buddy_uid > 0);
    return ani_send_cmd(ANIDB_CMD_BUDDYDENY, buddy_uid);
}

ani_response_t *ani_buddylist(int start_at)
{
    return ani_send_cmd(ANIDB_CMD_BUDDYLIST, start_at);
}

ani_response_t *ani_buddystate(int start_at)
{
    return ani_send_cmd(ANIDB_CMD_BUDDYSTATE, start_at);
}
