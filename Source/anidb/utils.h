/*
 *  utils.h
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: utils.h 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#ifndef ANIDB_UTILS_H
#define ANIDB_UTILS_H

#include <stdlib.h>
#include <string.h>

#include <errno.h>

#if defined(__cplusplus)
 #define ANI_BEGIN_C_DECLS      extern "C" {
 #define ANI_END_C_DECLS        }
#else /* !__cplusplus */
 #define ANI_BEGIN_C_DECLS       /* nothing */
 #define ANI_END_C_DECLS         /* nothing */
#endif /* __cplusplus */

ANI_BEGIN_C_DECLS

#if defined(assert)
 #undef assert
#endif /* assert */

#if defined(NODEBUG)
 #define assert(x)   ((void)0)
#else /* !NODEBUG */
 #define assert(x)   ((x) ? ((void)0) : xassert(# x, __FILE__, __LINE__))
#endif /* NODEBUG */

#if defined(ANIDBUG)
 #define DEBUG(x, ...)                                                      \
 {                                                                          \
     print_msg("Debug", __FILE__, __PRETTY_FUNCTION__, __LINE__, x,          \
         ## __VA_ARGS__);                                                   \
 }
#else /* !ANIDBUG */
 #define DEBUG(x, ...)   ((void)0)
#endif /* ANIDBUG */

#define INFO(x, ...)                                                        \
{                                                                           \
    print_msg("Info", __FILE__, __PRETTY_FUNCTION__, __LINE__, x,           \
        ## __VA_ARGS__);                                                    \
}

#define WARN(x, ...)                                                        \
{                                                                           \
    print_msg("Warning", __FILE__, __PRETTY_FUNCTION__, __LINE__, x,        \
        ## __VA_ARGS__);                                                    \
}

#define ERROR(x, ...)                                                       \
{                                                                           \
    print_msg("Error", __FILE__, __PRETTY_FUNCTION__, __LINE__, x,          \
        ## __VA_ARGS__);                                                    \
}

#define ABORT(x, ...)                                                       \
{                                                                           \
    print_msg("Critical Error", __FILE__, __PRETTY_FUNCTION__,              \
    __LINE__, x, ## __VA_ARGS__);                                           \
    abort();                                                                \
}

int print_msg(char *priority, const char *filename, const char *function,
    int line, const char *fmt, ...);

void xassert(const char *expr, const char *file, int line);

const char *xstrerror(void);

#define xstrlen(x)  (((x) != NULL && *(x) != '\0') ? strlen(x) : 0)

char *xstrncpy(char *dst, const char *src, size_t len);
char *xstrdup(const char *src);
char *xstrndup(const char *src, size_t len);

void xto_lower(char *str);

void *xmalloc(size_t size);
void *xcalloc(size_t count, size_t size);
void *xrealloc(void *ptr, size_t size);

#define xfree(type, ptr)                                                    \
{                                                                           \
    memset((ptr), 0xfc, sizeof(type));                                      \
    free(ptr);                                                              \
    ptr = NULL;                                                             \
}

#define xnfree(type, ptr)                                                   \
{                                                                           \
    memset((ptr), 0xfc, sizeof(type) * (size));                             \
    free(ptr);                                                              \
    ptr = NULL;                                                             \
}

char **split(const char *src, char seperator);
int count_splits(char **str);
void free_split(char **str);

ANI_END_C_DECLS

#endif /* ANIDB_UTILS_H */
