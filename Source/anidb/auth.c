/*
 *  auth.c
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: auth.c 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#include <anidb.h>
#include <ctype.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <stdlib.h>
#include <stdio.h>

static short encryption = ANI_ENCRYPT_NONE;
static char username[RAW_LEN] = { '\0' };
static char password[RAW_LEN] = { '\0' };
static char api_password[RAW_LEN] = { '\0' };
static char session[SESSION_LEN] = { '\0' };
static char salt[SALT_LEN] = { '\0' };

ani_response_t *ani_set_encryption(short type)
{
    ani_response_t *response = NULL;
    int i = 0;

    assert(type == 1);
    assert(*username != '\0');
    assert(*api_password != '\0');
    DEBUG("Enabling encryption: %d\n", type);
    response = ani_send_cmd(ANIDB_CMD_ENCRYPT, username, type);
    switch (response->status_code)
    {
        case ANI_STATUS_ENCRYPTION_ENABLED:
            for (i = 0; ' ' != response->msg[i]; i++)
            {
                salt[i] = response->msg[i];
            }
            DEBUG("Enabled encryption and got salt for encryption: %s\n", salt);
            encryption = type;
            break;
        case ANI_STATUS_API_PASSWORD_NOT_DEFINED:
        case ANI_STATUS_NO_SUCH_ENCRYPTION_TYPE:
        case ANI_STATUS_NO_SUCH_USER:
            ERROR("Encryption not enabled: %s\n", response->msg);
            break;
    }
    return response;
}

short ani_get_encryption(void)
{
    return encryption;
}

ani_response_t *ani_login(void)
{
	ani_response_t *response = NULL;

    response = ani_send_cmd(ANIDB_CMD_AUTH, username, password,
        ANI_PROTOVERSION, ANI_CLIENTVERSION);
    if (ANI_STATUS_LOGIN_ACCEPTED == response->status_code ||
        ANI_STATUS_LOGIN_ACCEPTED_NEW_VERSION == response->status_code)
    {
        INFO("Logged in\n", NULL);
        ANI_ENABLE_STATUS(STATUS_LOGGED_IN);
    }
    return response;
}

ani_response_t *ani_logout(void)
{
    ani_response_t *response = NULL;

    response = ani_send_cmd(ANIDB_CMD_LOGOUT);
    if (ANI_STATUS_LOGGED_OUT == response->status_code)
    {
        INFO("Logged out\n", NULL);
        ANI_DISABLE_STATUS(STATUS_LOGGED_IN);
    }
    return response;
}

ani_response_t *ani_relogin(void)
{
    ani_response_t *response = NULL;

    if (ANI_STATUS_ENABLED(STATUS_CONNECTED))
    {
        if (ANI_STATUS_ENABLED(STATUS_LOGGED_IN))
        {
            response = ani_logout();
            if (ANI_STATUS_LOGGED_OUT != response->status_code)
            {
                ERROR("Could not logout from anidb-server.\n", NULL);
                return response;
            }
        }
        return ani_login();
    }
    else
    {
        ERROR("Not connected to anidb-server.\n", NULL);
        return NULL;
    }
}

void ani_set_username(char *new_username)
{
    assert(NULL != username);
    (void)xstrncpy(username, new_username, RAW_LEN - 1);
    xto_lower(username);
}

const char *ani_username(void)
{
    return username;
}

void ani_set_password(char *new_password)
{
    assert(NULL != password);
    (void)xstrncpy(password, new_password, RAW_LEN - 1);
    xto_lower(password);
}

const char *ani_password(void)
{
    return password;
}

void ani_set_session(const char *new_session)
{
    assert(NULL != new_session);
    (void)xstrncpy(session, new_session, SESSION_LEN - 1);
}

const char *ani_session(void)
{
    return session;
}
