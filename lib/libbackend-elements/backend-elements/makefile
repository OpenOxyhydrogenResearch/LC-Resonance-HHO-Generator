# file      : backend-elements/makefile
# author    : Boris Kolpackov <boris@kolpackov.net>
# copyright : Copyright (c) 2005-2010 Boris Kolpackov
# license   : GNU GPL v2; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../build/bootstrap.make

cxx_tun   :=
cxx_obj   := $(addprefix $(out_base)/,$(cxx_tun:.cxx=.o))
cxx_od    := $(cxx_obj:.o=.o.d)

backend_elements.l             := #$(out_base)/backend-elements.l
backend_elements.l.cpp-options := $(out_base)/backend-elements.l.cpp-options

clean     := $(out_base)/.clean


# Secure default target.
#
$(backend_elements.l.cpp-options):
#$(backend_elements.l):


# Imports.
#
$(call import,\
  $(scf_root)/import/libcult/stub.make,\
  l: cult.l,cpp-options: cult.l.cpp-options)

$(call import,\
  $(scf_root)/import/libboost/regex/stub.make,\
  l: re.l,cpp-options: re.l.cpp-options)


# Build.
#
#$(backend_elements.l): $(cxx_obj) $(cult.l)

#$(cxx_obj): $(backend_elements.l.cpp-options)

$(backend_elements.l.cpp-options): value := -I$(src_root)
$(backend_elements.l.cpp-options): $(re.l.cpp-options) $(cult.l.cpp-options)

#$(call include-dep,$(cxx_od))


# Convenience alias for default target.
#
$(out_base)/: $(backend_elements.l.cpp-options)


# Clean.
#
#$(BackendElements.l).clean \

$(clean): $(addsuffix .cxx.clean,$(cxx_obj)) \
          $(backend_elements.l.cpp-options).clean


# How to.
#
$(call include,$(bld_root)/cxx/o-l.make)
$(call include,$(bld_root)/cxx/cxx-o.make)
