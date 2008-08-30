#
#   Anishell.mk
#   libanidb
#
#   Created by Andreas Meingast on 17.03.07.
#   Copyright 2007 Andreas Meingast. All rights reserved.
#
#   $Id: anishell.mk 1 2007-03-24 13:06:42Z ameingast $
#
#

include ../../Resources/MK/config.mk
include ../../Resources/MK/common.mk

TARGET 		= 	anishell
SOURCES 	= 	main.c
OBJECTS		= 	$(SOURCES:%.c=%.o)	

CFLAGS		+=	-I../anidb
LDLIBS		+=	../anidb/libanidb.a

$(TARGET): $(OBJECTS) ../anidb/libanidb.a
	$(LINK_RULE)
	
%.o: %.c
	$(CC_RULE)

clean:
	$(CLEAN_RULE)

.depend: $(SOURCES)
	$(DEP_RULE)
	
-include .depend
