# file      : makefile
# author    : Boris Kolpackov <boris@kolpackov.net>
# copyright : Copyright (c) 2005-2010 Boris Kolpackov
# license   : GNU GPL v2; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))build/bootstrap.make

default := $(out_base)/
test    := $(out_base)/.test
clean   := $(out_base)/.clean

$(default): $(out_base)/backend-elements/ $(out_base)/tests/
$(test): $(out_base)/tests/.test
$(clean): $(out_base)/backend-elements/.clean $(out_base)/tests/.clean

$(call import,$(src_base)/backend-elements/makefile)
$(call import,$(src_base)/tests/makefile)
