/*
 *  data.h
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: data.h 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#ifndef ANIDB_DATA_H
#define ANIDB_DATA_H

#include <anidb/response.h>
#include <anidb/types.h>
#include <anidb/utils.h>

ANI_BEGIN_C_DECLS

ani_response_t *ani_get_anime_by_anime_id(int anime_id);
ani_response_t *ani_get_anime_by_anime_id_and_acode(int anime_id, int acode);
ani_response_t *ani_get_anime_by_name(const char *anime_name);
ani_response_t *ani_get_anime_by_name_and_acode(const char *anime_name,
    int acode);

ani_response_t *ani_get_episode_by_id(int episode_id);
ani_response_t *ani_get_episode_by_anime_name(const char *anime_name,
    int episode_number);
ani_response_t *ani_get_episode_by_anime_id(int anime_id, int episode_number);

ani_response_t *ani_get_file_by_id(int file_id);
ani_response_t *ani_get_file_by_id_and_fcode(int file_id, int fcode, int acode);
ani_response_t *ani_get_file_by_md4(int file_size, const char *md4_digest);
ani_response_t *ani_get_file_by_md4_and_fcode(int file_size,
    const char *md4_digest, int fcode, int acode);

ani_response_t *ani_get_group_by_id(int group_id);
ani_response_t *ani_get_group_by_name(const char *group_name);

ani_response_t *ani_get_producer_by_id(int producer_id);
ani_response_t *ani_get_producer_by_name(const char *producer_name);

ANI_END_C_DECLS

#endif /* ANIDB_DATA_H */
