/*
 *  mylist.h
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: mylist.h 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#ifndef ANIDB_MYLIST_H
#define ANIDB_MYLIST_H

#include <anidb/response.h>
#include <anidb/utils.h>

ANI_BEGIN_C_DECLS

ani_response_t *ani_mylist_by_list_id(int list_id);
ani_response_t *ani_mylist_by_file_id(int file_id);
ani_response_t *ani_mylist_by_size_and_md4(int size, const char *md4);
ani_response_t *ani_mylist_by_aname_and_gname(const char *aname,
    const char *gname, int episode_number);
ani_response_t *ani_mylist_by_aname_and_group_id(const char *aname,
    int group_id, int episode_number);
ani_response_t *ani_mylist_by_anime_id_and_gname(int anime_id,
    const char *gname, int episode_number);
ani_response_t *ani_mylist_by_by_aid_and_gid(int anime_id, int group_id,
    int episode_number);

ani_response_t *ani_edit_mylist_by_list_id(int list_id, short state,
    short viewed, const char *source, const char *storage, const char *other);

ani_response_t *ani_add_mylist_by_file_id(int file_id, short state,
    short viewed, const char *source, const char *storage, const char *other);
ani_response_t *ani_add_mylist_by_size_and_md4(int size, const char *md4,
    short state, short viewed,const char *source, const char *storage,
    const char *other);
ani_response_t *ani_add_mylist_by_aname(const char *aname, short state,
    short viewed, const char *source, const char *storage, const char *other);
ani_response_t *ani_add_mylist_by_aname_and_gname(const char *aname,
    const char *gname, int episode_number, short state, short viewed,
    const char *source, const char *storage, const char *other);
ani_response_t *ani_add_mylist_by_aname_and_gid(const char *aname,
    int group_id, int episode_number, short state, short viewed,
    const char *source, const char *storage, const char *other);
ani_response_t *ani_add_mylist_by_aid_and_gname(int anime_id,
    const char *gname, int episode_number, short state, short viewed,
    const char *source, const char *storage, const char *other);
ani_response_t *ani_add_mylist_by_aid_and_gid(int anime_id, int group_id,
    short state, int episode_number, short viewed, const char *source,
    const char *storage, const char *other);

ani_response_t *ani_del_mylist_by_list_id(int list_id);
ani_response_t *ani_del_mylist_by_file_id(int file_id);
ani_response_t *ani_del_mylist_by_aname(const char *anime_name);
ani_response_t *ani_del_mylist_by_aname_and_gname(const char *anime_name,
    const char *group_name, int episode_number);
ani_response_t *ani_del_mylist_by_aname_and_gid(const char *anime_name,
    int group_id, int episode_number);
ani_response_t *ani_del_mylist_by_aid_and_gid(int anime_id, int group_id,
    int episode_number);

ani_response_t *ani_myliststats(void);

ANI_END_C_DECLS

#endif /* ANIDB_MYLIST_H */
