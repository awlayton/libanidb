#
#   Makefile
#   libanidb
#
#   Created by Andreas Meingast on 17.03.07.
#   Copyright 2007 Andreas Meingast. All rights reserved.
#
#   $Id: Makefile 1 2007-03-24 13:06:42Z ameingast $
#
#

-include Resources/MK/common.mk

default: all

config: Resources/MK/config.mk

Resources/MK/config.mk:
	@echo "* Running configure"
	@./configure

-include Resources/MK/config.mk

ifeq ($(SYSTEM),Darwin)
	MAKEARGS 	+= 	-f Resources/MK/osx.mk
else
	MAKEARGS	+= 	-f Resources/MK/default.mk
endif

all: config 
	@$(MAKE) $(MAKEARGS) all

clean: config
	@$(MAKE) $(MAKEARGS) clean

install: all
	@$(MAKE) $(MAKEARGS) install

package: all
	@$(MAKE) $(MAKEARGS) package		
