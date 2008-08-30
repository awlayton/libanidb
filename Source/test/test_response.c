/*
 *  test_response.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 09.02.07.
 *  Copyright 2007 Andreas Meingast. All rights reserved.
 *
 *  $Id: test_response.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#include <anidb.h>

#include "test.h"

void test_normal_packet(void)
{
    int i = 0;
    ani_response_t *response = NULL;
    char *responses[] = {
        "230 ANIME\n161|52|50|0|715|57|777|35|816|1|2002-2003|TV|Tokyo Mew Mew|"
        "東京ミュウミュウ||||TMM'mew|Cat Girls\n",
        "230 ANIME\n161|52|50|0|715|57|777|35|816|1|2002-2003|TV|Tokyo Mew Mew|"
        "東京ミュウミュウ||||TMM'mew|Cat Girls161|52|50|0|715|57|777|35|816|1|"
        "2002-2003|TV|Tokyo Mew Mew|東京ミュウミュウ||||TMM'mew|Cat Girls161|52|50"
        "|0|715|57|777|35|816|1|2002-2003|TV|Tokyo Mew Mew|東京ミュウミュウ||||TMM"
        "'mew|Cat Girls161|52|50|0|715|57|777|35|816|1|2002-2003|TV|"
        "Tokyo Mew Mew|東京ミュウミュウ||||TMM'mew|Cat Girls161|52|50|0|715|57|777"
        "|35|816|1|2002-2003|TV|Tokyo Mew Mew|東京ミュウミュウ||||T"
        "MM'mew|Cat Girls161|52|50|0|715|57|777|35|816|1|2002-2003|TV|"
        "Tokyo Mew Mew|東京ミュウミュウ||||TMM'mew|Cat Girls161|52|50|0|715|57"
        "|777|35|816|1|2002-2003|TV|Tokyo Mew Mew|東京ミュウミュウ||||TMM'mew|"
        "Cat Girls161|52|50|0|715|57|777|35|816|1|2002-2003|TV|Tokyo Mew Mew|"
        "東京ミュウミュウ||||TMM'mew|Cat Girls161|52|50|0|715|57|777|35|816|1|"
        "2002-2003|TV|Tokyo Mew Mew|東京ミュウミュウ||||TMM'mew|Cat Girls161|52|50"
        "|0|715|57|777|35|816|1|2002-2003|TV|Tokyo Mew Mew|東京ミュウミュウ||||"
        "TMM'mew|Cat Girls161|52|50|0|715|57|777|35|816|1|2002-2003|TV|"
        "Tokyo Mew Mew|東京ミュウミュウ||||TMM'mew|Cat Girls\n"
    };
    
    for (i = 0; i < sizeof(responses)/sizeof(*responses); i++)
    {
        response = ani_create_response(responses[i]);
        if (ANI_STATUS_MALFORMED_RESPONSE == response->status_code) 
            TEST_ERROR();
        ani_free_response(response);
    }
}

void test_response_overflow(void)
{
    ani_response_t *response = NULL;
    char data[RAW_LEN * 2];
    int i = 0;

    for (i = 0; i < RAW_LEN * 2; ++i)
    {
        data[i] = 'a';
    }
    data[RAW_LEN * 2 - 1] = '\0';
    response = ani_create_response(data);
    if (response->status_code != ANI_STATUS_MALFORMED_RESPONSE) TEST_ERROR();
    ani_free_response(response);
}

void test_response_nonterminated(void)
{
    ani_response_t *response = NULL;
    char data[RAW_LEN + 1];
    int i = 0;

    for (i = 0; i < RAW_LEN + 1; ++i)
    {
        data[i] = 'a';
    }
    (void)strcpy(data, "tag1 210 Some Message\nSome Data\n");
    data[strlen(data)] = ' ';
    response = ani_create_response(data);
    if (response->status_code != ANI_STATUS_MALFORMED_RESPONSE) TEST_ERROR();
    ani_free_response(response);
}

void test_response_blob(void)
{
    unsigned char data[RAW_LEN];
    int i = 0;
    ani_response_t *response = NULL;

    for (i = 0; i < RAW_LEN; i++)
    {
        srand(time(NULL));
        data[i] = rand() % 9;
    }
    data[i] = '\0';
    response = ani_create_response((char *)data);
    if (response->status_code != ANI_STATUS_MALFORMED_RESPONSE) TEST_ERROR();
    ani_free_response(response);
}
