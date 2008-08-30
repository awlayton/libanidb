/*
 *  test.h
 *  libanidb
 *
 *  Created by Andreas Meingast on 18.03.07.
 *  Copyright 2007 Andreas Meingast. All rights reserved.
 *
 *  $Id: test.h 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#ifndef ANIDB_TEST_H
#define ANIDB_TEST_H

#include <anidb.h>
#include <string.h>

extern int errors;
extern char error_names[1024][128];

#define TEST_USER           "libanidbcl"
#define TEST_USER_ID        209280
#define TEST_PASSWD         "1234567890"

#define TEST_ANIME          "Test Anime"
#define TEST_ANIME_ID       357

#define TEST_EPISODE_1_ID   51566
#define TEST_EPISODE_1_NAME "AJAX/XML test ep - DO NOT REMOVE"
#define TEST_EPISODE_2_ID   52524
#define TEST_EPISODE_2_NAME "Episode 8"

#define TEST_GROUP_ID       1
#define TEST_GROUP_NAME     "Animehaven"

#define TEST_PRODUCER_ID    34
#define TEST_PRODUCER_NAME  "GONZO"

#ifndef TEST_ONLINE
  #define TEST_ONLINE         0
#endif /* TEST_ONLINE */

/*  all available tests */
#if TEST_ONLINE == 1
  #define TEST_AUTH_C         1
  #define TEST_BUDDDY_C       1
  #define TEST_DATA_C         1
  #define TEST_MISC_C         1
  #define TEST_MYLIST_C       1
  #define TEST_NET_C          1
  #define TEST_NOTIFY_C       1
  #define TEST_REQUEST_C      1
  #define TEST_RESPONSE_C     1
  #define TEST_TYPES_C        1
  #define TEST_UTILS_C        1
#else /*  offline testing */
  #define TEST_AUTH_C         0
  #define TEST_BUDDDY_C       0
  #define TEST_DATA_C         0
  #define TEST_MISC_C         0
  #define TEST_MYLIST_C       0
  #define TEST_NET_C          0
  #define TEST_NOTIFY_C       0
  #define TEST_REQUEST_C      1
  #define TEST_RESPONSE_C     1
  #define TEST_TYPES_C        1
  #define TEST_UTILS_C        1
#endif /* TEST_ONLINE == ! */

#define TEST_ERROR()                                                        \
{                                                                           \
    (void)snprintf(error_names[errors++], 128, "%s:%d",                     \
        __PRETTY_FUNCTION__, __LINE__);                                     \
    ERROR("=== FAILED TEST ===\n", NULL);                                   \
}

#endif /* ANIDB_TEST_H */
