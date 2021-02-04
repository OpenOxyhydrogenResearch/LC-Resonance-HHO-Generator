# file      : examples/diagnostic/makefile
# author    : Boris Kolpackov <boris@kolpackov.net>
# copyright : Copyright (c) 2005-2010 Boris Kolpackov
# license   : GNU GPL v2; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../build/bootstrap.make

cxx_tun   := driver.cxx
cxx_obj   := $(addprefix $(out_base)/,$(cxx_tun:.cxx=.o))
cxx_od    := $(cxx_obj:.o=.o.d)

frontend_elements.l             := $(out_root)/frontend-elements/frontend-elements.l
frontend_elements.l.cpp-options := $(out_root)/frontend-elements/frontend-elements.l.cpp-options

diagnostic := $(out_base)/diagnostic
clean      := $(out_base)/.clean


# Build.
#
$(diagnostic): $(cxx_obj) $(frontend_elements.l)

$(cxx_obj) $(cxx_od): $(frontend_elements.l.cpp-options)

$(call include-dep,$(cxx_od))


# Convenience alias for default target.
#
$(out_base)/: $(diagnostic)


# Clean.
#
$(clean): $(diagnostic).o.clean      \
  $(addsuffix .cxx.clean,$(cxx_obj)) \
  $(addsuffix .cxx.clean,$(cxx_od))


# How to.
#
$(call include,$(bld_root)/cxx/o-e.make)
$(call include,$(bld_root)/cxx/cxx-o.make)
$(call include,$(bld_root)/cxx/cxx-d.make)

# Dependencies.
#
$(call import,$(src_root)/frontend-elements/makefile)
