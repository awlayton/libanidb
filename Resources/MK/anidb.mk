#
#   Library.mk
#   libanidb
#
#   Created by Andreas Meingast on 17.03.07.
#   Copyright 2007 Andreas Meingast. All rights reserved.
#
#   $Id: anidb.mk 1 2007-03-24 13:06:42Z ameingast $
#
#

include ../../Resources/MK/config.mk
include ../../Resources/MK/common.mk

TARGET 		= 	libanidb.a
SOURCES 	= 	auth.c buddy.c data.c dispatcher.c misc.c mylist.c net.c	\
				notify.c platform.c receiver.c request.c response.c types.c	\
				utils.c
OBJECTS		= 	$(SOURCES:%.c=%.o)	

$(TARGET): $(OBJECTS)
	$(AR_RULE)
	
%.o: %.c
	$(CC_RULE)

clean:
	$(CLEAN_RULE)

.depend: $(SOURCES)
	$(DEP_RULE)
	
-include .depend
