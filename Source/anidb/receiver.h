/*
 *  receiver.h
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: receiver.h 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#ifndef ANIDB_RECEIVER_H
#define ANIDB_RECEIVER_H

#include <anidb/request.h>
#include <anidb/response.h>
#include <anidb/utils.h>

ANI_BEGIN_C_DECLS

int ani_start_receiver(void);
int ani_stop_receiver(void);

ani_response_t *ani_get_response(const ani_request_t *request);
ani_response_t *ani_get_notification(void);

ANI_END_C_DECLS

#endif /* ANIDB_RECEIVER_H */
