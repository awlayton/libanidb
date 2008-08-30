/*
 *  test_utils.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 09.02.07.
 *  Copyright 2007 Andreas Meingast. All rights reserved.
 *
 *  $Id: test_utils.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#include <stdio.h>

#include "test.h"

void test_utils_split(void)
{
    char **split_str = NULL;

    split_str = split("Hello;&#\nWorld\t\nBye\nWorld\n", '\n');
    if (count_splits(split_str) != 5) TEST_ERROR();
    free_split(split_str);
    split_str = split("\n\n\n", '\n');
    if (count_splits(split_str) != 4) TEST_ERROR();
    free_split(split_str);
    split_str = split("", '\n');
    if (count_splits(split_str) != 0) TEST_ERROR();
    free_split(split_str);
    split_str = split("Hello World", '\n');
    if (count_splits(split_str) != 1) TEST_ERROR();
    free_split(split_str);
}
