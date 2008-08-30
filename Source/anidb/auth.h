/*
 *  auth.h
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: auth.h 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#ifndef ANIDB_AUTH_H
#define ANIDB_AUTH_H

#include <anidb/response.h>
#include <anidb/utils.h>

ANI_BEGIN_C_DECLS

#define ANI_ENCRYPT_NONE    0
#define ANI_ENCRYPT_AES     1

/* TODO */
ani_response_t *ani_set_encryption(short type);
short ani_get_encryption(void);

ani_response_t *ani_login(void);
ani_response_t *ani_logout(void);
ani_response_t *ani_relogin(void);

void ani_set_username(char *username);
const char *ani_username(void);
void ani_set_password(char *password);
const char *ani_password(void);

void ani_set_session(const char *session);
const char *ani_session(void);

ANI_END_C_DECLS

#endif /* ANIDB_AUTH_H */
