/*
 *  mylist.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: mylist.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#include <anidb.h>

ani_response_t *ani_mylist_by_list_id(int list_id)
{
    assert(list_id > 0);
    return ani_send_cmd(ANIDB_CMD_MYLIST_BY_LID, list_id);
}

ani_response_t *ani_mylist_by_file_id(int file_id)
{
	assert(file_id > 0);
    return ani_send_cmd(ANIDB_CMD_MYLIST_BY_FID, file_id);
}

ani_response_t *ani_mylist_by_size_and_md4(int size, const char *md4)
{
	assert(size > 0);
    assert(NULL != md4);
    return ani_send_cmd(ANIDB_CMD_MYLIST_BY_MD4, size, md4);
}

ani_response_t *ani_mylist_by_aname_and_gname(const char *aname,
    const char *gname, int episode_number)
{
	assert(NULL != aname);
    assert(NULL != gname);
    assert(episode_number > 0);
    return ani_send_cmd(ANIDB_CMD_MYLIST_BY_ANAME_AND_GNAME, aname, gname,
        episode_number);
}

ani_response_t *ani_mylist_by_aname_and_group_id(const char *aname,
    int group_id, int episode_number)
{
	assert(NULL != aname);
    assert(group_id > 0);
    assert(episode_number > 0);
    return ani_send_cmd(ANIDB_CMD_MYLIST_BY_ANAME_AND_GID, aname, group_id,
        episode_number);
}

ani_response_t *ani_mylist_by_anime_id_and_gname(int anime_id,
    const char *gname, int episode_number)
{
	assert(anime_id > 0);
    assert(NULL != gname);
    assert(episode_number > 0);
    return ani_send_cmd(ANIDB_CMD_MYLIST_BY_AID_AND_GNAME, anime_id, gname,
        episode_number);
}

ani_response_t *ani_mylist_by_by_aid_and_gid(int anime_id, int group_id,
    int episode_number)
{
	assert(anime_id > 0);
    assert(group_id > 0);
    assert(episode_number > 0);
    return ani_send_cmd(ANIDB_CMD_MYLIST_BY_AID_AND_GID, anime_id, group_id,
        episode_number);
}

ani_response_t *ani_edit_mylist_by_list_id(int list_id, short state,
    short viewed, const char *source, const char *storage, const char *other)
{
	assert(list_id > 0);
    assert(state >= 0);
    assert(viewed >= 0);
    assert(NULL != source);
    assert(NULL != storage);
    assert(NULL != other);
    return ani_send_cmd(ANIDB_CMD_MYLISTADD_BY_LID, list_id, state, viewed,
        source, storage, other);
}

ani_response_t *ani_add_mylist_by_file_id(int file_id, short state,
    short viewed, const char *source, const char *storage, const char *other)
{
	assert(file_id > 0);
    assert(state >= 0);
    assert(viewed >= 0);
    assert(NULL != source);
    assert(NULL != storage);
    assert(NULL != other);
    return ani_send_cmd(ANIDB_CMD_MYLISTADD_BY_FID, file_id, state, viewed,
        source, storage, other);
}

ani_response_t *ani_add_mylist_by_size_and_md4(int size, const char *md4,
    short state, short viewed,const char *source, const char *storage,
    const char *other)
{
	assert(size > 0);
    assert(NULL != md4);
    assert(state >= 0);
    assert(viewed >= 0);
    assert(NULL != source);
    assert(NULL != storage);
    assert(NULL != other);
    return ani_send_cmd(ANIDB_CMD_MYLISTADD_BY_MD4, size, md4, state, viewed,
        source, storage, other);
}

ani_response_t *ani_add_mylist_by_aname(const char *aname, short state,
    short viewed, const char *source, const char *storage, const char *other)
{
	assert(NULL != aname);
    assert(state >= 0);
    assert(viewed >= 0);
    assert(NULL != source);
    assert(NULL != storage);
    assert(NULL != other);
    return ani_send_cmd(ANIDB_CMD_MYLISTADD_BY_ANAME, aname, state, viewed,
        source, storage, other);
}

ani_response_t *ani_add_mylist_by_aname_and_gname(const char *aname,
    const char *gname, int episode_number, short state, short viewed,
    const char *source, const char *storage, const char *other)
{
	assert(NULL != aname);
    assert(NULL != gname);
    assert(episode_number > 0);
    assert(state >= 0);
    assert(viewed >= 0);
    assert(NULL != source);
    assert(NULL != storage);
    assert(NULL != other);
    return ani_send_cmd(ANIDB_CMD_MYLISTADD_BY_ANAME_AND_GNAME, aname, gname,
        episode_number, state, viewed, source, storage, other);
}

ani_response_t *ani_add_mylist_by_aname_and_gid(const char *aname,
    int group_id, int episode_number, short state, short viewed,
    const char *source, const char *storage, const char *other)
{
	assert(NULL != aname);
    assert(group_id > 0);
    assert(episode_number > 0);
    assert(state >= 0);
    assert(viewed >= 0);
    assert(NULL != source);
    assert(NULL != storage);
    assert(NULL != other);
    return ani_send_cmd(ANIDB_CMD_MYLISTADD_BY_ANAME_AND_GID, aname, group_id,
        episode_number, state, viewed, source, storage, other);
}

ani_response_t *ani_add_mylist_by_aid_and_gname(int anime_id,
    const char *gname, int episode_number, short state, short viewed,
    const char *source, const char *storage, const char *other)
{
    assert(anime_id > 0);
    assert(NULL != gname);
    assert(episode_number > 0);
    assert(state >= 0);
    assert(viewed >= 0);
    assert(NULL != source);
    assert(NULL != storage);
    assert(NULL != other);
    return ani_send_cmd(ANIDB_CMD_MYLISTADD_BY_AID_AND_GNAME, anime_id, gname,
        episode_number, state, viewed, source, storage, other);
}

ani_response_t *ani_add_mylist_by_aid_and_gid(int anime_id, int group_id,
    short state, int episode_number, short viewed, const char *source,
    const char *storage, const char *other)
{
    assert(anime_id > 0);
    assert(group_id > 0);
    assert(episode_number > 0);
    assert(state >= 0);
    assert(viewed >= 0);
    assert(NULL != source);
    assert(NULL != storage);
    assert(NULL != other);
    return ani_send_cmd(ANIDB_CMD_MYLISTADD_BY_AID_AND_GID, anime_id, group_id,
        episode_number, state, viewed, source, storage, other);
}

ani_response_t *ani_del_mylist_by_list_id(int list_id)
{
    assert(list_id > 0);
    return ani_send_cmd(ANIDB_CMD_MYLISTDEL_BY_LID, list_id);
}

ani_response_t *ani_del_mylist_by_file_id(int file_id)
{
	assert(file_id > 0);
    return ani_send_cmd(ANIDB_CMD_MYLISTDEL_BY_FID, file_id);
}

ani_response_t *ani_del_mylist_by_aname(const char *anime_name)
{
	assert(NULL != anime_name);
    return ani_send_cmd(ANIDB_CMD_MYLISTDEL_BY_ANAME, anime_name);
}

ani_response_t *ani_del_mylist_by_aname_and_gname(const char *anime_name,
    const char *group_name, int episode_number)
{
    assert(NULL != anime_name);
    assert(NULL != group_name);
    assert(episode_number > 0);
    return ani_send_cmd(ANIDB_CMD_MYLISTDEL_BY_ANAME_AND_GNAME, anime_name,
        group_name, episode_number);
}

ani_response_t *ani_del_mylist_by_aname_and_gid(const char *anime_name,
    int group_id, int episode_number)
{
	assert(NULL != anime_name);
    assert(group_id > 0);
    assert(episode_number > 0);
    return ani_send_cmd(ANIDB_CMD_MYLISTDEL_BY_ANAME_AND_GID, anime_name,
        group_id, episode_number);
}

ani_response_t *ani_del_mylist_by_aid_and_gid(int anime_id, int group_id,
    int episode_number)
{
	assert(anime_id > 0);
    assert(group_id > 0);
    assert(episode_number > 0);
    return ani_send_cmd(ANIDB_CMD_MYLISTDEL_BY_AID_AND_GID, anime_id,
        group_id, episode_number);
}

ani_response_t *ani_myliststats(void)
{
    return ani_send_cmd(ANIDB_CMD_MYLISTSTATS);
}
