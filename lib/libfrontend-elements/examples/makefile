# file      : examples/makefile
# author    : Boris Kolpackov <boris@kolpackov.net>
# copyright : Copyright (c) 2005-2010 Boris Kolpackov
# license   : GNU GPL v2; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../build/bootstrap.make

default   := $(out_base)/
clean     := $(out_base)/.clean

examples := $(out_base)/diagnostic

$(default): $(addsuffix /,$(examples))
$(clean): $(addsuffix /.clean,$(examples))

$(foreach e,$(subst $(out_base),$(src_base),$(examples)),$(call import,$e/makefile))
