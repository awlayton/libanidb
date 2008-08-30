/*
 *  types.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: types.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#include <anidb.h>

#define DATA_SEPERATOR   '|'

ani_anime_t *ani_create_anime(ani_response_t *response)
{
    ani_anime_t *anime = (ani_anime_t *)xmalloc(sizeof(ani_anime_t));
    char **split_str = NULL;

    assert(NULL != response);
    split_str = split(response->data, DATA_SEPERATOR);
    assert(count_splits(split_str) == 19);
    anime->anime_id = atoi(split_str[0]);
    anime->total_episode_count = atoi(split_str[1]);
    anime->normal_episode_count = atoi(split_str[2]);
    anime->special_episode_count = atoi(split_str[3]);
    anime->rating = atoi(split_str[4]);
    anime->vote_count = atoi(split_str[5]);
    anime->tmp_rating = atoi(split_str[6]);
    anime->tmp_vote_count = atoi(split_str[7]);
    anime->average_review_rating = atoi(split_str[8]);
    anime->review_count = atoi(split_str[9]);
    (void)xstrncpy(anime->year, split_str[10], RAW_LEN - 1);
    (void)xstrncpy(anime->type, split_str[11], RAW_LEN - 1);
    (void)xstrncpy(anime->romaji_name, split_str[12], RAW_LEN - 1);
    (void)xstrncpy(anime->kanji_name, split_str[13], RAW_LEN - 1);
    (void)xstrncpy(anime->english_name, split_str[14], RAW_LEN - 1);
    (void)xstrncpy(anime->other_name, split_str[15], RAW_LEN - 1);
    (void)xstrncpy(anime->short_name_list, split_str[16], RAW_LEN - 1);
    (void)xstrncpy(anime->synonym_list, split_str[17], RAW_LEN - 1);
    (void)xstrncpy(anime->category_list, split_str[18], RAW_LEN - 1);
    free_split(split_str);
	return anime;
}

ani_episode_t *ani_create_episode(ani_response_t *response)
{
	ani_episode_t *episode = (ani_episode_t *)xmalloc(sizeof(ani_response_t));
	char **split_str = NULL;
	
	assert(NULL != response);
	split_str = split(response->data, DATA_SEPERATOR);
	assert(count_splits(split_str) == 9);
	episode->episode_id = atoi(split_str[0]);
    episode->anime_id = atoi(split_str[1]);
    episode->length = atoi(split_str[2]);
    episode->rating = atoi(split_str[3]);
    episode->vote_count = atoi(split_str[4]);
    (void)xstrncpy(episode->episode_number, split_str[5], RAW_LEN - 1);
    (void)xstrncpy(episode->english_name, split_str[6], RAW_LEN - 1);
    (void)xstrncpy(episode->romaji_name, split_str[7], RAW_LEN - 1);
    (void)xstrncpy(episode->kanji_name, split_str[8], RAW_LEN - 1);
	free_split(split_str);
	return episode;
}

ani_file_t *ani_create_file(ani_response_t *response)
{
    ani_file_t *file = (ani_file_t *)xmalloc(sizeof(ani_file_t));
    char **split_str = NULL;

    assert(NULL != response);
	split_str = split(response->data, DATA_SEPERATOR);
	assert(count_splits(split_str) == 8);
    file->file_id = atoi(split_str[0]);
    file->anime_id = atoi(split_str[1]);
    file->episode_id = atoi(split_str[2]);
    file->group_id = atoi(split_str[3]);
    file->state = (short)atoi(split_str[4]);
    file->size = atoi(split_str[5]);
    strncpy(file->ed2k, split_str[6], RAW_LEN - 1);
    strncpy(file->anidb_filename, split_str[7], RAW_LEN - 1);
    free_split(split_str);
	return file;
}

ani_group_t *ani_create_group(ani_response_t *response)
{
    ani_group_t *group = (ani_group_t *)xmalloc(sizeof(ani_group_t));
    char **split_str = NULL;

    assert(NULL != response);
	split_str = split(response->data, DATA_SEPERATOR);
	assert(count_splits(split_str) == 10);
	group->group_id = atoi(split_str[0]);
    group->rating = atoi(split_str[1]);
    group->vote_count = atoi(split_str[2]);
    group->anime_count = atoi(split_str[3]);
    group->file_count = atoi(split_str[4]);
    strncpy(group->name, split_str[5], RAW_LEN - 1);
    strncpy(group->short_name, split_str[6], RAW_LEN - 1);
    strncpy(group->irc_channel, split_str[7], RAW_LEN - 1);
    strncpy(group->irc_server, split_str[8], RAW_LEN - 1);
    strncpy(group->url, split_str[9], RAW_LEN - 1);
    free_split(split_str);
	return group;
}

ani_producer_t *ani_create_producer(ani_response_t *response)
{
    ani_producer_t *producer =
        (ani_producer_t *)xmalloc(sizeof(ani_producer_t));
    char **split_str = NULL;

    assert(NULL != response);
	split_str = split(response->data, DATA_SEPERATOR);
	assert(count_splits(split_str) == 7);
	producer->producer_id = atoi(split_str[0]);
    strncpy(producer->name, split_str[1], RAW_LEN - 1);
    strncpy(producer->short_name, split_str[2], RAW_LEN - 1);
    strncpy(producer->other_name, split_str[3], RAW_LEN - 1);
    strncpy(producer->type, split_str[4], RAW_LEN - 1);
    strncpy(producer->picture_name, split_str[5], RAW_LEN - 1);
    strncpy(producer->url, split_str[6], RAW_LEN - 1);
    free_split(split_str);
	return producer;
}

ani_mylist_t *ani_create_mylist(ani_response_t *response)
{
    ani_mylist_t *list = (ani_mylist_t *)xmalloc(sizeof(ani_mylist_t));
    char **split_str = NULL;

    assert(NULL != response);
	split_str = split(response->data, DATA_SEPERATOR);
    switch(response->status_code)
    {
        case ANI_STATUS_MYLIST:
            assert(count_splits(split_str) == 11);
            list->list_id = atoi(split_str[0]);
            list->file_id = atoi(split_str[1]);
            list->episode_id = atoi(split_str[2]);
            list->anime_id = atoi(split_str[3]);
            list->group_id = atoi(split_str[4]);
            list->date = atoi(split_str[5]);
            list->state = atoi(split_str[6]);
            list->viewdate = atoi(split_str[7]);
            strncpy(list->storage, split_str[8], RAW_LEN - 1);
            strncpy(list->source, split_str[9], RAW_LEN - 1);
            strncpy(list->other, split_str[10], RAW_LEN - 1);
            break;
        case ANI_STATUS_MULTIPLE_MYLIST_ENTRIES:    /* TODO: implement */
            assert(0);
            break;
        default:
            assert(0);
            break;
    }
    free_split(split_str);
	return list;
}

ani_myliststats_t *ani_create_myliststats(ani_response_t *response)
{
    ani_myliststats_t *stats =
        (ani_myliststats_t *)xmalloc(sizeof(ani_myliststats_t));
    char **split_str = NULL;

    assert(NULL != response);
	split_str = split(response->data, DATA_SEPERATOR);
	assert(count_splits(split_str) == 16);
    stats->total_anime_count = atoi(split_str[0]);
    stats->total_episodes_count = atoi(split_str[1]);
    stats->total_files_count = atoi(split_str[2]);
    stats->size_of_files = atoi(split_str[3]);
    stats->added_animes_count = atoi(split_str[4]);
    stats->added_episodes_count = atoi(split_str[5]);
    stats->added_files_count = atoi(split_str[6]);
    stats->added_groups_count = atoi(split_str[7]);
    stats->leech_ratio = atoi(split_str[8]);
    stats->lame_ratio = atoi(split_str[9]);
    stats->viewed_of_db_ratio = atoi(split_str[10]);
    stats->mylist_of_db_ratio = atoi(split_str[11]);
    stats->viewed_of_mylist_ratio = atoi(split_str[12]);
    stats->viewed_episodes_count = atoi(split_str[13]);
    stats->votes_count = atoi(split_str[14]);
    stats->reviews_count = atoi(split_str[15]);
    free_split(split_str);
	return stats;
}

ani_push_file_notify_t *ani_create_push_file_notify(ani_response_t *response)
{
    ani_push_file_notify_t *notification =
        (ani_push_file_notify_t *)xmalloc(sizeof(ani_push_file_notify_t));
    char **split_str = NULL;

    assert(NULL != response);
    split_str = split(response->data, DATA_SEPERATOR);
    assert(count_splits(split_str) == 4);
    notification->anime_id = atoi(split_str[0]);
    notification->date = atoi(split_str[1]);
    notification->count = atoi(split_str[2]);
    (void)xstrncpy(notification->anime_title, split_str[3], RAW_LEN - 1);
    free_split(split_str);
	return notification;
}

ani_push_msg_notify_t *ani_create_push_msg_notify(ani_response_t *response)
{
    ani_push_msg_notify_t *notification =
        (ani_push_msg_notify_t *)xmalloc(sizeof(ani_push_msg_notify_t));
    char **split_str = NULL;

    assert(NULL != response);
    split_str = split(response->data, DATA_SEPERATOR);
    assert(count_splits(split_str) == 5);
    notification->type = atoi(split_str[0]);
    notification->date = atoi(split_str[1]);
    notification->sender_uid = atoi(split_str[2]);
    (void)xstrncpy(notification->sender_name, split_str[3], RAW_LEN - 1);
    (void)xstrncpy(notification->subject, split_str[4], RAW_LEN - 1);
    free_split(split_str);
	return notification;
}

ani_push_buddy_notify_t *ani_create_push_buddy_notify(ani_response_t *response)
{
	ani_push_buddy_notify_t *notification =
	    (ani_push_buddy_notify_t *)xmalloc(sizeof(ani_push_buddy_notify_t));
	char **split_str = NULL;
	
	assert(NULL != response);
	split_str = split(response->data, DATA_SEPERATOR);
	assert(count_splits(split_str) == 2);
	notification->buddy_uid = atoi(split_str[0]);
	notification->event_type = atoi(split_str[1]);
	free_split(split_str);
	return notification;
}

ani_push_shutdown_notify_t *ani_create_push_shutdown_notify(
    ani_response_t *response)
{
	ani_push_shutdown_notify_t *notification = (ani_push_shutdown_notify_t *)
	    xmalloc(sizeof(ani_push_shutdown_notify_t));
	char **split_str = NULL;
	
	assert(NULL != response);
	split_str = split(response->data, DATA_SEPERATOR);
	assert(count_splits(split_str) == 2);
	notification->offline_time = atoi(split_str[0]);
	(void)xstrncpy(notification->comment, split_str[1], RAW_LEN - 1);
	free_split(split_str);
	return notification;
}

ani_notify_t *ani_create_notify(ani_response_t *response)
{
	ani_notify_t *notification =
	    (ani_notify_t *)xmalloc(sizeof(ani_notify_t));
	char **split_str = NULL;
	
	assert(NULL != response);
	split_str = split(response->data, DATA_SEPERATOR);
	assert(count_splits(split_str) == 3);
	notification->pending_notifies = atoi(split_str[0]);
	notification->pending_msgs = atoi(split_str[1]);
	notification->online_buddy_count = atoi(split_str[2]);
	free_split(split_str);
	return notification;
}

ani_notifylist_t *ani_create_notifylist(ani_response_t *response)
{
	ani_notifylist_t *notifylist =
	    (ani_notifylist_t *)xmalloc(sizeof(ani_notifylist_t));
	char **split_str = NULL, **split_line = NULL;
	int i = 0;
	
	assert(NULL != response);
	split_str = split(response->data, '\n');
	assert(count_splits(split_str) < RAW_LEN);
	notifylist->notify_count = count_splits(split_str);
	for (i = 0; i < notifylist->notify_count; i++)
	{
	    split_line = split(split_str[i], DATA_SEPERATOR);
	    assert(count_splits(split_line) == 2);
	    notifylist->types[i] = *(split_line[0]);
	    notifylist->ids[i] = atoi(split_line[1]);
	    free_split(split_line);
	}
	free_split(split_str);
	return notifylist;
}

ani_notifyget_msg_t *ani_create_notifyget_msg(ani_response_t *response)
{
	ani_notifyget_msg_t *notification =
	    (ani_notifyget_msg_t *)xmalloc(sizeof(ani_notifyget_msg_t));
	char **split_str = NULL;
	
	assert(NULL != response);
	split_str = split(response->data, DATA_SEPERATOR);
	assert(count_splits(split_str) == 7);
    notification->notification_id = atoi(split_str[0]);
    notification->from_user_id = atoi(split_str[1]);
    (void)xstrncpy(notification->from_user_name, split_str[2], RAW_LEN - 1);
    notification->date = atoi(split_str[3]);
    notification->type = atoi(split_str[4]);
    (void)xstrncpy(notification->title, split_str[5], RAW_LEN - 1);
    (void)xstrncpy(notification->body, split_str[6], RAW_LEN - 1);
	free_split(split_str);
	return notification;
}

ani_notifyget_notification_t *ani_create_notifyget_notification(
    ani_response_t *response)
{
	ani_notifyget_notification_t *notification =
	    (ani_notifyget_notification_t *)
	    xmalloc(sizeof(ani_notifyget_notification_t));
	char **split_str = NULL;
	
	assert(NULL != response);
	split_str = split(response->data, DATA_SEPERATOR);
	assert(count_splits(split_str) == 5);
    notification->anime_id = atoi(split_str[0]);
    notification->type = atoi(split_str[1]);
    notification->count = atoi(split_str[2]);
    notification->date = atoi(split_str[3]);
    (void)xstrncpy(notification->anime_name, split_str[4], RAW_LEN - 1);
	free_split(split_str);
	return notification;
}

ani_buddylist_t *ani_create_buddylist(ani_response_t *response)
{
    ani_buddylist_t *list =
        (ani_buddylist_t *)xmalloc(sizeof(ani_buddylist_t));
    char **split_str = NULL, **split_line = NULL;
    int i = 0;

    assert(NULL != response);
	split_str = split(response->data, '\n');
	list->total = count_splits(split_str);
	assert(list->total < RAW_LEN);
	for (i = 0; i < list->total; i++)
	{
	    split_line = split(split_str[i], DATA_SEPERATOR);
	    list->user_ids[i] = atoi(split_line[0]);
	    list->user_names[i] = xstrdup(split_line[1]);
	    list->states[i] = atoi(split_line[2]);
	    free_split(split_line);
	}
    free_split(split_str);
    return list;
}

ani_buddystates_t *ani_create_buddystates(ani_response_t *response)
{
    ani_buddystates_t *states =
        (ani_buddystates_t *)xmalloc(sizeof(ani_buddystates_t));
    char **split_str = NULL, **split_line = NULL;
    int i = 0;

    assert(NULL != response);
	split_str = split(response->data, '\n');
	states->total = count_splits(split_str);
	assert(states->total < RAW_LEN);
	for (i = 0; i < states->total; i++)
	{
	    split_line = split(split_str[i], DATA_SEPERATOR);
	    assert(count_splits(split_line) == 2);
	    states->user_ids[i] = atoi(split_line[0]);
	    states->states[i] = atoi(split_line[1]);
	    free_split(split_line);
	}
    free_split(split_str);
    return states;
}

ani_stats_t *ani_create_stats(ani_response_t *response)
{
    ani_stats_t *stats = (ani_stats_t *)xmalloc(sizeof(ani_stats_t));
    char **split_str = NULL;

    assert(NULL != response);
    split_str = split(response->data, DATA_SEPERATOR);
    assert(count_splits(split_str) == 7);
    stats->anime_count = atoi(split_str[0]);
    stats->episode_count = atoi(split_str[1]);
    stats->file_count = atoi(split_str[2]);
    stats->group_count = atoi(split_str[3]);
    stats->user_count = atoi(split_str[4]);
    stats->total_file_size = atol(split_str[5]);
	stats->open_creqs = atoi(split_str[6]);
	free_split(split_str);
	return stats;
}

ani_top_t *ani_create_top(ani_response_t *response)
{
	ani_top_t *top = (ani_top_t *)xmalloc(sizeof(ani_top_t));
    char **split_str = NULL;

    assert(NULL != response);
    split_str = split(response->data, DATA_SEPERATOR);
    assert(count_splits(split_str) == 22);
    top->longest_mylist_count = atoi(split_str[0]);
    (void)xstrncpy(top->longest_mylist_user, split_str[1], RAW_LEN - 1);
    top->largest_mylist_count = atoi(split_str[2]);
    (void)xstrncpy(top->largest_mylist_user, split_str[3], RAW_LEN - 1);
    top->most_lame_files_count = atoi(split_str[4]);
    (void)xstrncpy(top->most_lame_files_user, split_str[5], RAW_LEN - 1);
    top->most_indep_user_count = atoi(split_str[6]);
    (void)xstrncpy(top->most_indep_user_name, split_str[7], RAW_LEN - 1);
    top->biggest_leecher_count = atoi(split_str[8]);
    (void)xstrncpy(top->biggest_leecher_name, split_str[9], RAW_LEN - 1);
    top->most_anime_added_count = atoi(split_str[10]);
    (void)xstrncpy(top->most_anime_added_user, split_str[11], RAW_LEN - 1);
    top->most_eps_added_count = atoi(split_str[12]);
    (void)xstrncpy(top->most_eps_added_user, split_str[13], RAW_LEN - 1);
    top->most_files_added_count = atoi(split_str[14]);
    (void)xstrncpy(top->most_files_added_user, split_str[15], RAW_LEN - 1);
    top->most_groups_added_count = atoi(split_str[16]);
    (void)xstrncpy(top->most_groups_added_user, split_str[17], RAW_LEN - 1);
    top->most_votes_count = atoi(split_str[18]);
    (void)xstrncpy(top->most_votes_user, split_str[19], RAW_LEN - 1);
    top->most_reviews_count = atoi(split_str[20]);
    (void)xstrncpy(top->most_reviews_user, split_str[21], RAW_LEN - 1);
    free_split(split_str);
    return top;
}
