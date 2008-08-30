#
#   Default.mk
#   libanidb
#
#   Created by Andreas Meingast on 17.03.07.
#   Copyright 2007 Andreas Meingast. All rights reserved.
#
#   $Id: default.mk 1 2007-03-24 13:06:42Z ameingast $
#
#

include Resources/MK/config.mk
include Resources/MK/common.mk

TARGETS		=	anidb test anishell

all: $(TARGETS)
	
anidb anishell test: gen_tests
	@echo "* Compiling $@"
	@$(MAKE) $(MAKEARGS) -C Source/$@ -f ../../Resources/MK/$@.mk

gen_tests:
	@echo "* Generating Unit Tests"
	@echo "  - [RB] Resources/unit_test.rb"
	@ruby Resources/unit_test.rb Source/test
	
clean: 
	@$(foreach TRG, $(TARGETS), echo "* Cleaning $(TRG)"; $(MAKE) $(MAKEARGS) -C Source/$(TRG) -f ../../Resources/MK/$(TRG).mk clean;)
	@rm -f Source/test/main.c Resources/MK/config.mk