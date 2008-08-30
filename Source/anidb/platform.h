/*
 *  platform.h
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: platform.h 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#ifndef ANIDB_PLATFORM_H
#define ANIDB_PLATFORM_H

#include <anidb/utils.h>

ANI_BEGIN_C_DECLS

#if defined(_Windows) || defined(__WINDOWS__) || defined(__WIN32__) || \
    defined(WIN32) || defined(__WINNT__) || defined(__NT__)
  #ifndef WINDOWS
    #define WINDOWS
  #endif /* WINDOWS */
#endif /* ... */

#if defined(linux) || defined(__linux) || defined(__linux__)
  #ifndef LINUX 
    #define LINUX
  #endif /* LINUX */
#endif /* ... */

#if defined(__APPLE__) || defined(MACINTOSH) || defined(MAC)
  #ifndef MACOS
    #define MACOS
  #endif /* MACOS */
#endif /* ... */

#ifdef SYS_BEOS
  #include <kernel/OS.h>
  typedef thread_id ani_thread_t;
  typedef sem_id ani_sem_t;
#elif defined(WINDOWS)
  #error "Unimplemented"
#else
  #ifdef HAVE_PTHREAD
    #include <pthread.h>
    typedef pthread_t ani_thread_t;
  #else
    #error "Pthreads not available"
  #endif /* HAVE_PTHREAD */
  #ifdef HAVE_SEMAPHORE
    #include <semaphore.h>
    #include <fcntl.h>
    typedef sem_t ani_sem_t;
  #else
    #error "Semaphores not available"
  #endif /*HAVE_SEMAPHORE */
#endif /* SYS_BEOS */

int ani_create_thread(ani_thread_t *thread, void *(*func)(void *), void *arg);
int ani_thread_join(ani_thread_t *thread);
int ani_thread_cancel(ani_thread_t *thread);

/*  wrappers for the actual operating system dependent functions */
ani_sem_t *ani_sem_open(const char *name, unsigned int value);
int ani_sem_unlink(const char *name);
int ani_sem_close(ani_sem_t *sem);
int ani_sem_post(ani_sem_t *sem);
int ani_sem_wait(ani_sem_t *sem);

void ani_encrypt(void *raw);
void ani_decrypt(void *raw);

/*  customs */
int ani_sem_cleanup(const char *name, ani_sem_t *sem);

#define ANI_KILL_SEM(x)                                                     \
{                                                                           \
    if (0 != ani_sem_unlink(x) && 0 != errno) errno = 0;                    \
}

ANI_END_C_DECLS

#endif /* ANIDB_PLATFORM_H */
