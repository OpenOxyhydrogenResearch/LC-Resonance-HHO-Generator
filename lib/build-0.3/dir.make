# file      : build/dir.make
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2004-2010 Code Synthesis Tools CC
# license   : GNU GPL v2; see accompanying LICENSE file

.PRECIOUS: %/.

%/. :
	$(call message,,mkdir -p $*)
