/*
 *  net.h
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: net.h 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#ifndef ANIDB_NET_H
#define ANIDB_NET_H

#include <anidb/utils.h>
#include <sys/types.h>

ANI_BEGIN_C_DECLS

#define STATUS_CONNECTED        (1 << 0)
#define STATUS_LOGGED_IN        (1 << 1)
#define STATUS_NOTIFY_ENABLED   (1 << 2)

#define SESSION_LEN             8
#define TAG_LEN                 7
#define SALT_LEN                8
#define RAW_LEN                 1400

int ani_open_connection(const char *server, int localport);
int ani_close_connection(void);

#define ANI_ENABLE_STATUS(x)    (ani_set_status((ani_status()|x)))
#define ANI_DISABLE_STATUS(x)   (ani_set_status((ani_status()^(1<<(x/2)))))
#define ANI_STATUS_ENABLED(x)   (0!=(ani_status()&x))

int ani_status(void);
void ani_set_status(int mask);

ssize_t ani_send(const void *buf, size_t len);
ssize_t ani_recv(void *buf, size_t len);

ANI_END_C_DECLS

#endif /* ANIDB_NET_H */
