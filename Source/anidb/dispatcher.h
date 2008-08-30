/*
 *  dispatcher.h
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: dispatcher.h 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#ifndef ANIDB_DISPATCHER_H
#define ANIDB_DISPATCHER_H

#include <anidb/utils.h>

ANI_BEGIN_C_DECLS

int ani_start_dispatcher(void);
int ani_stop_dispatcher(void);

int ani_pump(void);

ANI_END_C_DECLS

#endif /* ANIDB_DISPATCHER_H */
