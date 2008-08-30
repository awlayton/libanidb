#
#   OSX.mk
#   libanidb
#
#   Created by Andreas Meingast on 17.03.07.
#   Copyright 2007 Andreas Meingast. All rights reserved.
#
#   $Id: osx.mk 1 2007-03-24 13:06:42Z ameingast $
#
#

#
#	The build process is handled by XCode; just wrap around
#
all: anidb test anishell
	
anidb test anishell:
	@xcodebuild -configuration Default -target $@ | grep -v "^$$"
	
clean:
	@xcodebuild -configuration Default clean -alltargets | grep -v "^$$"
	@rm -f Source/test/main.c Resources/MK/config.mk
