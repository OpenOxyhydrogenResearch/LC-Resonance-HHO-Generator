# file      : makefile
# author    : Boris Kolpackov <boris@kolpackov.net>
# copyright : Copyright (c) 2005-2010 Boris Kolpackov
# license   : GNU GPL v2; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))build/bootstrap.make

default   := $(out_base)/
clean     := $(out_base)/.clean

$(default): $(out_base)/cult/ $(out_base)/examples/
$(clean): $(out_base)/cult/.clean $(out_base)/examples/.clean

$(call import,$(src_base)/cult/makefile)
$(call import,$(src_base)/examples/makefile)
