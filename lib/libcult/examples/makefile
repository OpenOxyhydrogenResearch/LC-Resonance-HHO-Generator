# file      : examples/makefile
# author    : Boris Kolpackov <boris@kolpackov.net>
# copyright : Copyright (c) 2005-2010 Boris Kolpackov
# license   : GNU GPL v2; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../build/bootstrap.make
include $(scf_root)/configuration.make

default   := $(out_base)/
clean     := $(out_base)/.clean

examples := $(out_base)/cli                    \
            $(out_base)/mm/shptr               \
            $(out_base)/mm/transfer            \
            $(out_base)/trace

ifeq ($(cult_threads),y)
examples += $(out_base)/sched/main             \
            $(out_base)/sched/cancel
endif


ifeq ($(cult_network),y)
examples += $(out_base)/os/net/ipv4/datagram   \
            $(out_base)/os/net/ipv4/multicast
endif

ifeq ($(cult_dr),y)
examples += $(out_base)/dr/xdr
endif


$(default): $(addsuffix /,$(examples))
$(clean): $(addsuffix /.clean,$(examples))

$(foreach e,$(subst $(out_base),$(src_base),$(examples)),$(call import,$e/makefile))
