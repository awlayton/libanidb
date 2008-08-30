#
#   Test.mk
#   libanidb
#
#   Created by Andreas Meingast on 17.03.07.
#   Copyright 2007 Andreas Meingast. All rights reserved.
#
#   $Id: test.mk 1 2007-03-24 13:06:42Z ameingast $
#
#

include ../../Resources/MK/config.mk
include ../../Resources/MK/common.mk

TARGET 		= 	test
SOURCES 	= 	main.c test_auth.c test_buddy.c test_data.c test_misc.c 	\
				test_mylist.c test_net.c test_notify.c test_request.c 		\
				test_response.c test_types.c test_utils.c
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
