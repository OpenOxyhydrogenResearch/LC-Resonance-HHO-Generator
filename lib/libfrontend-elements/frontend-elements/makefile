# file      : frontend-elements/makefile
# author    : Boris Kolpackov <boris@kolpackov.net>
# copyright : Copyright (c) 2005-2010 Boris Kolpackov
# license   : GNU GPL v2; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../build/bootstrap.make

cxx_tun   := context.cxx       \
             diagnostic.cxx    \
             token-stream.cxx  \
             traversal.cxx

cxx_obj   := $(addprefix $(out_base)/,$(cxx_tun:.cxx=.o))
cxx_od    := $(cxx_obj:.o=.o.d)

frontend_elements.l             := $(out_base)/frontend-elements.l
frontend_elements.l.cpp-options := $(out_base)/frontend-elements.l.cpp-options

clean     := $(out_base)/.clean


# Secure default target.
#
$(frontend_elements.l):


# Import libcult.
#
$(call import,\
  $(scf_root)/import/libcult/stub.make,\
  l: cult.l,cpp-options: cult.l.cpp-options)

# Build.
#
$(frontend_elements.l): $(cxx_obj) $(cult.l)

$(cxx_obj) $(cxx_od): $(frontend_elements.l.cpp-options)

$(frontend_elements.l.cpp-options): value := -I$(src_root)
$(frontend_elements.l.cpp-options): $(cult.l.cpp-options)

$(call include-dep,$(cxx_od))


# Convenience alias for default target.
#
$(out_base)/: $(frontend_elements.l)


# Clean.
#
$(clean): $(frontend_elements.l).o.clean     \
  $(frontend_elements.l.cpp-options).clean \
  $(addsuffix .cxx.clean,$(cxx_obj))           \
  $(addsuffix .cxx.clean,$(cxx_od))



# How to.
#
$(call include,$(bld_root)/cxx/o-l.make)
$(call include,$(bld_root)/cxx/cxx-o.make)
$(call include,$(bld_root)/cxx/cxx-d.make)
