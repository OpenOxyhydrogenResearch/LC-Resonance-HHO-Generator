# file      : examples/dr/xdr/makefile
# author    : Boris Kolpackov <boris@kolpackov.net>
# copyright : Copyright (c) 2005-2010 Boris Kolpackov
# license   : GNU GPL v2; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../build/bootstrap.make

cxx_tun   := xdr.cxx
cxx_obj   := $(addprefix $(out_base)/,$(cxx_tun:.cxx=.o))
cxx_od    := $(cxx_obj:.o=.o.d)

cult.l             := $(out_root)/cult/cult.l
cult.l.cpp-options := $(out_root)/cult/cult.l.cpp-options

xdr       := $(out_base)/xdr
clean     := $(out_base)/.clean


# Build.
#
$(xdr): $(cxx_obj) $(cult.l)

$(cxx_obj) $(cxx_od): $(cult.l.cpp-options)

$(call include-dep,$(cxx_od))


# Convenience alias for default target.
#
$(out_base)/: $(xdr)


# Clean.
#
$(clean): $(xdr).o.clean             \
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
