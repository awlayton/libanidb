/*
 *  platform.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: platform.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#include <anidb/platform.h>

int ani_create_thread(ani_thread_t *thread, void *(*func)(void *), void *arg)
{
    assert(NULL != thread);
    assert(NULL != func);
    assert(NULL == arg);
#ifdef SYS_BEOS
    return -1;
#elif defined (WINDOWS)
    return -1;
#else
  #ifdef HAVE_PTHREAD
    return pthread_create(thread, NULL, func, arg);
  #endif /* HAVE_PTHREAD */ 
#endif /* SYS_BEOS */
}

int ani_thread_join(ani_thread_t *thread)
{
    assert(NULL != thread);
#ifdef SYS_BEOS
    return -1;
#elif defined (WINDOWS)
    return -1;
#else
  #ifdef HAVE_PTHREAD
    return pthread_join(*thread, NULL);
  #endif /* HAVE_PTHREAD */ 
#endif /* SYS_BEOS */  
}

int ani_thread_cancel(ani_thread_t *thread)
{
    assert(NULL != thread);
#ifdef SYS_BEOS
    return -1;
#elif defined (WINDOWS)
    return -1;
#else
  #ifdef HAVE_PTHREAD
    return pthread_cancel(*thread);
  #endif /* HAVE_PTHREAD */ 
#endif /* SYS_BEOS */  
}

int ani_sem_close(ani_sem_t *sem)
{
    assert(NULL != sem);
#ifdef SYS_BEOS
    return -1;
#elif defined (WINDOWS)
    return -1;
#else
  #ifdef HAVE_SEMAPHORE
    return sem_close(sem);
  #endif /* HAVE_SEMAPHORE */ 
#endif /* SYS_BEOS */  
}

ani_sem_t *ani_sem_open(const char *name, unsigned int value)
{
    ani_sem_t *sem = (ani_sem_t *)NULL;
    
    assert(NULL != name);
#ifdef SYS_BEOS
    return NULL;
#elif defined (WINDOWS)
    return -1;
#else
  #ifdef HAVE_SEMAPHORE
    /*  somehow we carry a damaged errno state... */
    errno = 0;
    sem = sem_open(name, O_CREAT | O_EXCL, 0660, value);
    if (0 != errno)
    {
        WARN("Could not initialize semaphore (%s): %s\n", name, xstrerror());
        return NULL;
    }
    DEBUG("Initialized semaphore: %s\n", name);
    return sem;
  #endif /* HAVE_SEMAPHORE */
#endif /* SYS_BEOS */
}

int ani_sem_unlink(const char *name)
{
    assert(NULL != name);
#ifdef SYS_BEOS
    return -1;
#elif defined (WINDOWS)
    return -1;
#else
  #ifdef HAVE_SEMAPHORE
    return sem_unlink(name);
  #endif /* HAVE_SEMAPHORE */ 
#endif /* SYS_BEOS */  
}

int ani_sem_post(ani_sem_t *sem)
{
    assert(NULL != sem);
#ifdef SYS_BEOS
    return -1;
#elif defined (WINDOWS)
    return -1;
#else
  #ifdef HAVE_SEMAPHORE
    return sem_post(sem);
  #endif /* HAVE_SEMAPHORE */ 
#endif /* SYS_BEOS */  
}

int ani_sem_wait(ani_sem_t *sem)
{
    assert(NULL != sem);
#ifdef SYS_BEOS
    return -1;
#elif defined (WINDOWS)
    return -1;
#else
  #ifdef HAVE_SEMAPHORE
    return sem_wait(sem);
  #endif /* HAVE_SEMAPHORE */ 
#endif /* SYS_BEOS */  
}

/*  TODO */
void ani_encrypt(void *raw)
{
#ifdef HAVE_OPENSSL
    if (raw) return;
#endif /* HAVE_OPENSSL */
    if (raw) return;
}

/*  TODO */
void ani_decrypt(void *raw)
{
#ifdef HAVE_OPENSSL
    if (raw) return;
#endif /* HAVE_OPENSSL */
    if (raw) return;
}

int ani_sem_cleanup(const char *name, ani_sem_t *sem)
{
    assert(NULL != name);
    assert(NULL != sem);
    if (0 != ani_sem_close(sem))
    {
        ERROR("Could not close semaphore (%s): %s\n", sem, xstrerror());
        return 1;
    }
    if (0 != ani_sem_unlink(name))
    {
        ERROR("Could not unlink semaphore (%s): %s\n", name, xstrerror());
        return 1;
    }
    DEBUG("Cleaned up semaphore: %s\n", name);
    return 0;
}
