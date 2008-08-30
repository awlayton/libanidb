/*
 *  types.h
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: types.h 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#ifndef ANIDB_TYPES_H
#define ANIDB_TYPES_H

#include <anidb/response.h>

ANI_BEGIN_C_DECLS

typedef struct _ani_anime_t
{
    int anime_id;
    int total_episode_count;
    int normal_episode_count;
    int special_episode_count;
    int rating;
    int vote_count;
    int tmp_rating;
    int tmp_vote_count;
    int average_review_rating;
    int review_count;
    int air_date;
    int end_date;
    int animeplanet_id;
    int animenewsnetwork_id;
    int allcinema_id;
    int animenfo_id;
    char url[RAW_LEN];
    char picname[RAW_LEN];
    char year[RAW_LEN];
    char type[RAW_LEN];
    char romaji_name[RAW_LEN];
    char kanji_name[RAW_LEN];
    char english_name[RAW_LEN];
    char other_name[RAW_LEN];
    char short_name_list[RAW_LEN];
    char synonym_list[RAW_LEN];
    char category_list[RAW_LEN];
    char related_aid_list[RAW_LEN];
    char producer_name_list[RAW_LEN];
    char producer_id_list[RAW_LEN];
    char award_list[RAW_LEN];
}	ani_anime_t;

ani_anime_t *ani_create_anime(ani_response_t *response);

typedef struct _ani_episode_t
{
    int episode_id;
    int anime_id;
    int length;
    int rating;
    int vote_count;
    char episode_number[RAW_LEN];
    char english_name[RAW_LEN];
    char romaji_name[RAW_LEN];
    char kanji_name[RAW_LEN];
}	ani_episode_t;

ani_episode_t *ani_create_episode(ani_response_t *response);

typedef struct _ani_file_t
{
    int file_id;
    int anime_id;
    int episode_id;
    int group_id;
    int mylist_id;
    short state;
    int size;
    char ed2k[RAW_LEN];
    char md5[RAW_LEN];
    char sha1[RAW_LEN];
    char crc32[RAW_LEN];
    char dub_language[RAW_LEN];
    char sub_language[RAW_LEN];
    char quality[RAW_LEN];
    char source[RAW_LEN];
    char audio_codec[RAW_LEN];
    int audio_bitrate;
    char video_codec[RAW_LEN];
    int video_bitrate;
    char video_resolution[RAW_LEN];
    char file_type[RAW_LEN];
    int length;
    char description[RAW_LEN];
    char anidb_filename[RAW_LEN];
}	ani_file_t;

ani_file_t *ani_create_file(ani_response_t *response);

typedef struct _ani_group_t
{
    int group_id;
    int rating;
    int vote_count;
    int anime_count;
    int file_count;
    char name[RAW_LEN];
    char short_name[RAW_LEN];
    char irc_channel[RAW_LEN];
    char irc_server[RAW_LEN];
    char url[RAW_LEN];
}	ani_group_t;

ani_group_t *ani_create_group(ani_response_t *response);

typedef struct _ani_producer_t
{
    int producer_id;
    char name[RAW_LEN];
    char short_name[RAW_LEN];
    char other_name[RAW_LEN];
    char type[RAW_LEN];
    char picture_name[RAW_LEN];
    char url[RAW_LEN];
}	ani_producer_t;
ani_producer_t *ani_create_producer(ani_response_t *response);

typedef struct _ani_mylist_t
{
    int list_id;
    int file_id;
    int episode_id;
    int anime_id;
    int group_id;
    int date;
    short state;
    int viewdate;
    char storage[RAW_LEN];
    char source[RAW_LEN];
    char other[RAW_LEN];
}	ani_mylist_t;

ani_mylist_t *ani_create_mylist(ani_response_t *response);

typedef struct _ani_myliststats_t
{
    int total_anime_count;
    int total_episodes_count;
    int total_files_count;
    int size_of_files;
    int added_animes_count;
    int added_episodes_count;
    int added_files_count;
    int added_groups_count;
    int leech_ratio;
    int lame_ratio;
    int viewed_of_db_ratio;
    int mylist_of_db_ratio;
    int viewed_of_mylist_ratio;
    int viewed_episodes_count;
    int votes_count;
    int reviews_count;
}	ani_myliststats_t;

ani_myliststats_t *ani_create_myliststats(ani_response_t *response);

typedef struct _ani_push_file_notify_t
{
    int anime_id;
    int date;
    int count;
    char anime_title[RAW_LEN];
}	ani_push_file_notify_t;

ani_push_file_notify_t *ani_create_push_file_notify(ani_response_t *response);

typedef struct _ani_push_msg_notify_t
{
    short type;
    int date;
    int sender_uid;
    char sender_name[RAW_LEN];
    char subject[RAW_LEN];
}	ani_push_msg_notify_t;

ani_push_msg_notify_t *ani_create_push_msg_notify(ani_response_t *response);

typedef struct _ani_push_buddy_notify_t
{
    int buddy_uid;
    short event_type;
}	ani_push_buddy_notify_t;

ani_push_buddy_notify_t *ani_create_push_buddy_notify(ani_response_t *response);

typedef struct _ani_push_shutdown_notify_t
{
    int offline_time;
    char comment[RAW_LEN];
}	ani_push_shutdown_notify_t;

ani_push_shutdown_notify_t *ani_create_push_shutdown_notify(
    ani_response_t *response);

typedef struct _ani_notify_t
{
    int pending_notifies;
    int pending_msgs;
    int online_buddy_count;
}	ani_notify_t;

ani_notify_t *ani_create_notify(ani_response_t *response);

typedef struct _ani_notifylist_t
{
    int notify_count;
    char types[RAW_LEN];
    int ids[RAW_LEN];
}	ani_notifylist_t;

ani_notifylist_t *ani_create_notifylist(ani_response_t *response);

typedef struct _ani_notifyget_msg_t
{
    int notification_id;
    int from_user_id;
    char from_user_name[RAW_LEN];
    int date;
    int type;
    char title[RAW_LEN];
    char body[RAW_LEN];
}	ani_notifyget_msg_t;

ani_notifyget_msg_t *ani_create_notifyget_msg(ani_response_t *response);

typedef struct _ani_notifyget_notification_t
{
    int anime_id;
    int type;
    short count;
    int date;
    char anime_name[RAW_LEN];
}	ani_notifyget_notification_t;

ani_notifyget_notification_t *ani_create_notifyget_notification(
    ani_response_t *response);

typedef struct _ani_buddylist_t
{
    short total;
    int user_ids[RAW_LEN];
    char *user_names[RAW_LEN];
    int states[RAW_LEN];
}	ani_buddylist_t;

ani_buddylist_t *ani_create_buddylist(ani_response_t *response);

typedef struct _ani_buddystates_t
{
    short total;
    int user_ids[RAW_LEN];
    int states[RAW_LEN];
}	ani_buddystates_t;

ani_buddystates_t *ani_create_buddystates(ani_response_t *response);

typedef struct _ani_stats_t
{
    int anime_count;
    int episode_count;
    int file_count;
    int group_count;
    int user_count;
    long total_file_size;
    int open_creqs;
}	ani_stats_t;

ani_stats_t *ani_create_stats(ani_response_t *response);

typedef struct _ani_top_t
{
    int longest_mylist_count;
    char longest_mylist_user[RAW_LEN];
    int largest_mylist_count;
    char largest_mylist_user[RAW_LEN];
    int most_lame_files_count;
    char most_lame_files_user[RAW_LEN];
    int most_indep_user_count;
    char most_indep_user_name[RAW_LEN];
    int biggest_leecher_count;
    char biggest_leecher_name[RAW_LEN];
    int most_anime_added_count;
    char most_anime_added_user[RAW_LEN];
    int most_eps_added_count;
    char most_eps_added_user[RAW_LEN];
    int most_files_added_count;
    char most_files_added_user[RAW_LEN];
    int most_groups_added_count;
    char most_groups_added_user[RAW_LEN];
    int most_votes_count;
    char most_votes_user[RAW_LEN];
    int most_reviews_count;
    char most_reviews_user[RAW_LEN];
}	ani_top_t;

ani_top_t *ani_create_top(ani_response_t *response);

ANI_END_C_DECLS

#endif /* ANIDB_TYPES_H */
