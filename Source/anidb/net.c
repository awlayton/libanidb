/*
 *  net.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: net.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#include <anidb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#ifndef IPPROTO_UDP
    #error "Your operating system does not support the UDP protocol"
#endif /* IPPROTO_UDP */

#ifndef SOCK_DGRAM
    #error "Your operating system does not support DGRAM sockets"
#endif /* SOCK_DGRAM */

#define ANIDB_HOSTNAME          "api.anidb.info"
#define ANIDB_REMOTE_PORT       9000
#define ANIDB_LOCAL_PORT        9000

#define ANIDB_RECV_TIMEOUT      { 30, 0 }
#define ANIDB_DELAY             4

extern int h_errno;

static int sockfd = -1;
static struct sockaddr_in server_in;
static struct sockaddr_in local_in;
static short status = 0;
static time_t last_send = 0;
static const char recver_lock_name[] = "RECVER_LOCK";
static const char sender_lock_name[] = "SENDER_LOCK";
static ani_sem_t *recver_lock = (ani_sem_t *)NULL;
static ani_sem_t *sender_lock = (ani_sem_t *)NULL;
static char *hostname = NULL;
static int local_port = 0;

static int init_semaphores(void);
static int cleanup_semaphores(void);
static int init_socket(void);
static int cleanup_socket(void);
static int set_sockopts(void);
static int bind_and_connect(void);
static void block_connection(void);
static void encrypt_packet(void *pkt);
static void decrypt_packet(void *pkt);

int ani_open_connection(const char *server, int localport)
{
    hostname = (NULL == server) ? xstrdup(ANIDB_HOSTNAME) : xstrdup(server);
    local_port = (localport > 0 && localport < 65535) ? localport :
        ANIDB_LOCAL_PORT;
    if (0 != init_semaphores())
    {
        return 1;
    }
    if (ani_status() != 0)
    {
        ERROR("Connection already opened", NULL);
        return 1;
    }
    if (0 != init_socket())
    {
        return 1;
    }
    if (0 != set_sockopts())
    {
        return 1;
    }
    if (0 != bind_and_connect())
    {
        return 1;
    }
    if (0 != ani_start_receiver())
    {
        return 1;
    }
    if (0 != ani_start_dispatcher())
    {
        return 1;
    }
    ANI_ENABLE_STATUS(STATUS_CONNECTED);
    INFO("Connection established\n", NULL);
    return 0;
}

int ani_close_connection(void)
{
    int retval = 0;

    if (!ANI_STATUS_ENABLED(STATUS_CONNECTED))
    {
        return 0;
    }
    if (ANI_STATUS_ENABLED(STATUS_NOTIFY_ENABLED))
    {
        (void)ani_stop_notification_service();
    }
    if (ANI_STATUS_ENABLED(STATUS_LOGGED_IN))
    {
        (void)ani_logout();
    }
    ANI_DISABLE_STATUS(STATUS_CONNECTED);
    if (0 != ani_stop_dispatcher() || 0 != cleanup_socket() ||
        0 != ani_stop_receiver() || 0 != cleanup_semaphores())
    {
        retval = 1;
    }
    INFO("Closed connection\n", NULL);
    return retval;
}

int ani_status(void)
{
    return status;
}

void ani_set_status(int mask)
{
    char status_str[RAW_LEN] = { '\0' };

    assert(mask >= 0);
    status = mask;
    if (ANI_STATUS_ENABLED(STATUS_CONNECTED))
    {
        (void)strcat(status_str, "STATUS_CONNECTED ");
    }
    if (ANI_STATUS_ENABLED(STATUS_LOGGED_IN))
    {
        (void)strcat(status_str, "STATUS_LOGGED_IN ");
    }
    if (ANI_STATUS_ENABLED(STATUS_NOTIFY_ENABLED))
    {
        (void)strcat(status_str, "STATUS_NOTIFY_ENABLED ");
    }
    DEBUG("Updated status to %s\n", status_str);
}

ssize_t ani_send(const void *buf, size_t len)
{
    ssize_t llen = 0;

    assert(NULL != buf);
    assert(len > 0);
    ani_sem_wait(sender_lock);
    block_connection();
    DEBUG("Sending (%s)\n", buf);
    encrypt_packet((void *)buf);
    if (-1 == (llen = send(sockfd, buf, len, 0)))
    {
        ERROR("Could not send on socket: %s\n", xstrerror());
    }
    DEBUG("Sent message\n", NULL);
    ani_sem_post(sender_lock);
    return llen;
}

ssize_t ani_recv(void *buf, size_t len)
{
    ssize_t llen = 0;

    assert(NULL != buf);
    assert(len > 0);
    ani_sem_wait(recver_lock);
    /* clear out the buffer */
    memset(buf, 0x00, len);
    if (-1 == (llen = recv(sockfd, buf, len, 0)))
    {
        if (errno == ECONNREFUSED)
        {
            ERROR("Connection refused\n", NULL);
            llen = -3;
        }
        if (errno == EWOULDBLOCK)
        {
            WARN("Socket timed out\n", NULL);
            llen = -2;
        }
    }
    else
    {
        decrypt_packet(buf);
        DEBUG("Received (%s)\n", buf);
    }
    ani_sem_post(recver_lock);
    return llen;
}

static int init_semaphores(void)
{
    assert(NULL == recver_lock);
    assert(NULL == sender_lock);
    ANI_KILL_SEM(sender_lock_name);
    ANI_KILL_SEM(recver_lock_name);
    if (NULL == (recver_lock = ani_sem_open(recver_lock_name, (unsigned int)1)))
    {
        return 1;
    }
    if (NULL == (sender_lock = ani_sem_open(sender_lock_name, 1)))
    {
        return 1;
    }
    return 0;
}

static int cleanup_semaphores(void)
{
    assert(NULL != recver_lock);
    assert(NULL != sender_lock);
    if (0 != ani_sem_cleanup(recver_lock_name, recver_lock))
    {
        return 1;
    }
    if (0 != ani_sem_cleanup(sender_lock_name, sender_lock))
    {
        return 1;
    }
    recver_lock = sender_lock = (ani_sem_t *)NULL;
    return 0;
}

static int init_socket(void)
{
    struct hostent *hp;

    if (-1 == (sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)))
    {
        ERROR("Could not create socket: %s\n", xstrerror());
        return 1;
    }
    DEBUG("Created socket: %d\n", sockfd);
    if (NULL == (hp = gethostbyname(hostname)))
    {
        ERROR("Could not resolve host (%s): %s\n", hostname,
            hstrerror(h_errno));
        return 1;
    }
    DEBUG("Resolved hostname: %s\n", hostname);
    bzero((char *)&server_in, sizeof(server_in));
    server_in.sin_family = AF_INET;
    server_in.sin_port = htons(ANIDB_REMOTE_PORT);
    memcpy(&server_in.sin_addr, hp->h_addr_list[0],
        (unsigned)(hp->h_length));
    bzero((char *)&local_in, sizeof(local_in));
    local_in.sin_family = AF_INET;
    local_in.sin_addr.s_addr = htonl(INADDR_ANY);
    local_in.sin_port = htons(local_port);
    DEBUG("Initialized socket\n", NULL);
    return 0;
}

static int cleanup_socket(void)
{
    if (0 != close(sockfd))
    {
        ERROR("Could not close socket: %s\n", xstrerror());
        return 1;
    }
    bzero((char *)&server_in, sizeof(server_in));
    bzero((char *)&local_in, sizeof(local_in));
    DEBUG("Closed socket: %d\n", sockfd);
    return 0;
}

static int set_sockopts(void)
{
    struct timeval timeout = ANIDB_RECV_TIMEOUT;
    int x = 0;

    if (0 != setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout,
        sizeof(timeout)))
    {
        ERROR("Could not set SO_SNDTIMEO: %s\n", xstrerror());
        return 1;
    }
    if (0 != setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &x, sizeof(x)))
    {
        ERROR("Could not set SO_REUSEADDR: %s\n", xstrerror());
        return 1;
    }
#if defined(SO_REUSEPORT)
    if (0 != setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &x, sizeof(x)))
    {
        ERROR("Could not set SO_REUSEPORT: %s\n", xstrerror());
        return 1;
    }
#endif /* SO_REUSEPORT */
    if (0 != setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &x, sizeof(x)))
    {
        ERROR("Could not set SO_KEEPALIVE: %s\n", xstrerror());
        return 1;
    }
    DEBUG("Set socket options\n", NULL);
    return 0;
}

static int bind_and_connect(void)
{
    if (0 != bind(sockfd, (struct sockaddr *)(&local_in),
        sizeof(local_in)))
    {
        ERROR("Could not bind: %s\n", xstrerror());
        return 1;
    }
    DEBUG("Bound socket\n", NULL);
    if (0 != connect(sockfd, (struct sockaddr *)(&server_in),
        sizeof(server_in)))
    {
        ERROR("Could not connect: %s\n", xstrerror());
        return 1;
    }
    DEBUG("Connected socket\n", NULL);
    return 0;
}

static void block_connection(void)
{
    int delay = last_send - time(NULL);
    int x = 0;

    if (0 != last_send && delay > 0)
    {
        DEBUG("Sleeping for %d s\n", delay);
        if (0 != (x = sleep((unsigned int)delay)))
        {
            WARN("Sleep interrupted (%d seconds left)\n", x);
        }
    }
    last_send = time(NULL) + ANIDB_DELAY;
}

static void encrypt_packet(void *pkt)
{
    if (ANI_ENCRYPT_NONE == ani_get_encryption())
    {
        return;
    }
    DEBUG("Encrypting packet with: %d\n", ani_get_encryption());
    ani_encrypt(pkt);
}

static void decrypt_packet(void *pkt)
{
    if (ANI_ENCRYPT_NONE == ani_get_encryption())
    {
        return;
    }
    DEBUG("Decrypting packet with: %d\n", ani_get_encryption());
    ani_decrypt(pkt);
}
