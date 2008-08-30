#
#   Common.mk
#   libanidb
#
#   Created by Andreas Meingast on 17.03.07.
#   Copyright 2007 Andreas Meingast. All rights reserved.
#
#   $Id: common.mk 1 2007-03-24 13:06:42Z ameingast $
#
#

-include ../../Resources/MK/config.mk

CFLAGS		+=	-g -O0 -pedantic -Wall

INCLUDES	=	-I. -I..

MAKE		= 	make

ifeq ($(PTHREAD),yes)
	CFLAGS	+=	-DHAVE_PTHREAD
	LDFLAGS += 	-lpthread
endif

ifeq ($(OPENSSL),yes)
	CFLAGS 	+= 	-DHAVE_OPENSSL
	LDFLAGS += 	-lcrypto
endif

ifeq ($(SEMAPHORE),yes)
	CFLAGS 	+= 	-DHAVE_SEMAPHORE
endif

define CC_RULE
	@echo "  - [CC] $@"
	@CMD="$(CC) $(INCLUDES) $(CFLAGS) -o $@ -c $<"; $$CMD || \
	  ( echo "Compile line for $@ was:"; echo $$CMD; false )
endef

define LINK_RULE
	@echo "  - [CC] $@"
	@CMD="$(CC) $(INCLUDES) -o $@ $(OBJECTS) $(LDLIBS) $(LDFLAGS)"; $$CMD || \
	  ( echo "Compile line for $@ was:"; echo $$CMD; false )
endef

define AR_RULE
	@echo "  - [AR] $@"
	@ar ru $@ $(OBJECTS) > /dev/null 2>&1
	@ranlib $@
endef

define CLEAN_RULE
	@echo "  - [RM] $(TARGET)"
	@$(RM) -f $(OBJECTS) $(TARGET) .depend
endef

define DEP_RULE
	@echo "  - [DP] $(TARGET)"
	@$(RM) .depend
	@$(foreach SRC, $(SOURCES), $(CC) -MM $(INCLUDES) $(SRC) $(CFLAGS) >> .depend;)
endef
