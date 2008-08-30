/*
 *  buddy.h
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: buddy.h 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#ifndef ANIDB_BUDDY_H
#define ANIDB_BUDDY_H

#include <anidb/response.h>
#include <anidb/utils.h>

ANI_BEGIN_C_DECLS

ani_response_t *ani_buddyadd_by_id(int buddy_uid);
ani_response_t *ani_buddyadd_by_name(const char *buddyname);
ani_response_t *ani_buddydel(int buddy_uid);
ani_response_t *ani_buddyaccept(int buddy_uid);
ani_response_t *ani_buddydeny(int buddy_uid);
ani_response_t *ani_buddylist(int start_at);
ani_response_t *ani_buddystate(int start_at);

ANI_END_C_DECLS

#endif /* ANIDB_BUDDY_H */
