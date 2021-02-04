# file      : tests/indentation/cxx/makefile
# author    : Boris Kolpackov <boris@kolpackov.net>
# copyright : Copyright (c) 2006-2010 Boris Kolpackov
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../build/bootstrap.make

cxx_tun := driver.cxx
cxx_obj := $(addprefix $(out_base)/,$(cxx_tun:.cxx=.o))
cxx_od  := $(cxx_obj:.o=.o.d)

#be.l             := $(out_root)/backend-elements/backend-elements.l
be.l.cpp-options := $(out_root)/backend-elements/backend-elements.l.cpp-options

driver := $(out_base)/driver
test   := $(out_base)/.test
clean  := $(out_base)/.clean


# Build.
#
$(driver): $(cxx_obj) #$(be.l)

$(cxx_obj) $(cxx_od): $(be.l.cpp-options)

$(call include-dep,$(cxx_od))


# Convenience alias for default target.
#
$(out_base)/: $(driver)


# Test.
#
$(test): driver := $(driver)
$(test): $(driver) $(src_base)/output.cxx
	$(driver) | diff -u $(src_base)/output.cxx -


# Clean.
#
$(clean): $(driver).o.clean          \
  $(addsuffix .cxx.clean,$(cxx_obj)) \
  $(addsuffix .cxx.clean,$(cxx_od))


# How to.
#
$(call include,$(bld_root)/cxx/o-e.make)
$(call include,$(bld_root)/cxx/cxx-o.make)
$(call include,$(bld_root)/cxx/cxx-d.make)


# Dependencies.
#
$(call import,$(src_root)/backend-elements/makefile)
