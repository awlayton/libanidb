/*
 *  utils.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: utils.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#include <anidb/utils.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

void xassert(const char *expr, const char *file, int line)
{
    if (NULL != expr && NULL != file && line > 0)
    {
        fprintf(stderr, "Assertion failed: %s:%d: \"%s\"\n", file, line, expr);
        abort();
    }
}

int print_msg(char *priority, const char *filename, const char *function,
    int line, const char *fmt, ...)
{
    va_list arg;
    time_t t = time(NULL);
    struct tm *ts = localtime(&t);
    int r = 0;

    assert(NULL != priority);
    assert(NULL != filename);
    assert(NULL != function);
    assert(line > 0);
    assert(NULL != fmt);
    assert(NULL != ts);
    fprintf(stdout, "%.2i:%.2i:%.2i %s :: %s:%d :::: ", ts->tm_hour, ts->tm_min,
        ts->tm_sec, priority, function, line);
    va_start(arg, fmt);
    r = vfprintf(stdout, fmt, arg);
    va_end(arg);
    return r;
}

const char *xstrerror(void)
{
    static char buf[1024] = { '\0' };

    if (0 == snprintf(buf, 1024, "(%d) %s", errno, strerror(errno)))
    {
        (void)snprintf(buf, 1024, "(%d) Unknown", errno);
    }
    return buf;
}

char *xstrncpy(char *dst, const char *src, size_t len)
{
    char *ptr = dst;
    
    assert(NULL != dst);
    assert(NULL != src);
    assert(len > 0);
    while (--len != 0 && *src != '\0')
    {
        *dst++ = *src++;
    }
    *dst = '\0';
    return ptr;
}

char *xstrdup(const char *src)
{
    void *ptr = NULL;
    size_t size = xstrlen(src) + 1;

    assert(NULL != src);
    ptr = memcpy(xmalloc(size), src, size);
    return ptr;
}

char *xstrndup(const char *src, size_t len)
{
    void *ptr = NULL;
    size_t size = xstrlen(src) + 1;

    assert(NULL != src);
    assert(len > 0);
    if (size > len)
    {
        size = len;
    }
    ptr = xstrncpy(xmalloc(size), src, size);
    return ptr;
}

void xto_lower(char *str)
{
    char *ptr = str;

    assert(NULL != str);
    while (*ptr != '\0')
    {
        if (isalpha((unsigned char) *ptr))
        {
            *ptr = tolower((unsigned char) *ptr);
        }
        ptr++;
    }
}

void *xmalloc(size_t size)
{
    return xcalloc(1, size);
}

void *xcalloc(size_t count, size_t size)
{
    void *ptr = NULL;

    assert(count > 0);
    assert(size > 0);
    if (NULL == (ptr = calloc(count, size)))
    {
        ABORT("Could not allocate memory: %s\n", xstrerror());
    }
    return ptr;
}

void *xrealloc(void *ptr, size_t size)
{
    void *new_ptr = NULL;

    assert(size > 0);
    if (NULL == ptr)
    {
        new_ptr = xmalloc(size);
    }
    else
    {
        if (NULL == (new_ptr = realloc(ptr, size)))
        {
            ABORT("Could not allocate memory: %s\n", xstrerror());
        }
    }
    return new_ptr;
}

char **split(const char *src, char seperator)
{
    char **str_array = NULL;
    char *work = xstrdup(src);
    char *ptr = NULL;
    unsigned int i = 0;
    int count = 0;

    assert(NULL != src);
    for (i = 0; i < xstrlen(work); i++)
    {
        if (seperator == work[i])
        {
            count++;
        }
    }
    str_array = (char **)xcalloc(count + 2, sizeof(char *));
    for (ptr = work, i = 0; NULL != (ptr = strchr(work, seperator));
        work = ++ptr)
    {
        *ptr = '\0';
        str_array[i++] = xstrdup(work);
    }
    str_array[i] = xstrdup(work);
    return str_array;
}

int count_splits(char **str)
{
    int i = 0;
    char **ptr = str;

    while(NULL != *ptr++) i++;
    if (i == 1 && **str == '\0')
    {
        return 0;
    }
    return i;
}

void free_split(char **strptr)
{
    char **work = strptr;

    assert(NULL != strptr);
    while (NULL != *work)
    {
        free(*work);
        *work++ = NULL;
    }
    free(strptr);
    strptr = NULL;
}
