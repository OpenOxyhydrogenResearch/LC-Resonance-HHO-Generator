# file      : examples/os/net/ipv4/datagram/makefile
# author    : Boris Kolpackov <boris@kolpackov.net>
# copyright : Copyright (c) 2005-2010 Boris Kolpackov
# license   : GNU GPL v2; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../../../build/bootstrap.make

client_cxx_tun   := client.cxx
server_cxx_tun   := server.cxx

client_cxx_obj := $(addprefix $(out_base)/,$(client_cxx_tun:.cxx=.o))
server_cxx_obj := $(addprefix $(out_base)/,$(server_cxx_tun:.cxx=.o))

cxx_obj   := $(client_cxx_obj) $(server_cxx_obj)
cxx_od    := $(cxx_obj:.o=.o.d)

cult.l             := $(out_root)/cult/cult.l
cult.l.cpp-options := $(out_root)/cult/cult.l.cpp-options

client  := $(out_base)/client
server  := $(out_base)/server
clean   := $(out_base)/.clean

# Convenience alias for default target.
#
$(out_base)/: $(client) $(server)

# Build.
#

$(client): $(client_cxx_obj) $(cult.l)
$(server): $(server_cxx_obj) $(cult.l)

$(cxx_obj) $(cxx_od): $(cult.l.cpp-options)

$(call include-dep,$(cxx_od))


# Clean.
#
$(clean): $(client).o.clean          \
  $(server).o.clean                  \
  $(addsuffix .cxx.clean,$(cxx_obj)) \
  $(addsuffix .cxx.clean,$(cxx_od))


# How to.
#
$(call include,$(bld_root)/cxx/o-e.make)
$(call include,$(bld_root)/cxx/cxx-o.make)
$(call include,$(bld_root)/cxx/cxx-d.make)

# Dependencies.
#
$(call import,$(src_root)/cult/makefile)
