# file      : makefile
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))/build-0.3/bootstrap.make

default  := $(out_base)/

.PHONY: $(default) test install dist dist-win clean

# Build.
#
$(default): $(out_base)/xsde/xsde/

# Test.
#
test: $(out_base)/xsde/.test

# Install.
#
install: $(out_base)/xsde/.install

# Dist.
#
dist: $(out_base)/xsde/.dist
dist-win: $(out_base)/xsde/.dist-win

# Clean.
#
clean: $(out_base)/libcult/.clean              \
       $(out_base)/libfrontend-elements/.clean \
       $(out_base)/libbackend-elements/.clean  \
       $(out_base)/libxsd-frontend/.clean      \
       $(out_base)/xsde/.clean

src_root := $(src_base)/libcult
scf_root := $(src_root)/build
out_root := $(src_root)
$(call import,$(src_base)/libcult/makefile)

src_root := $(src_base)/libfrontend-elements
scf_root := $(src_root)/build
out_root := $(src_root)
$(call import,$(src_base)/libfrontend-elements/makefile)

src_root := $(src_base)/libbackend-elements
scf_root := $(src_root)/build
out_root := $(src_root)
$(call import,$(src_base)/libbackend-elements/makefile)

src_root := $(src_base)/libxsd-frontend
scf_root := $(src_root)/build
out_root := $(src_root)
$(call import,$(src_base)/libxsd-frontend/makefile)

src_root := $(src_base)/xsde
scf_root := $(src_root)/build
out_root := $(src_root)

ifneq ($(filter $(MAKECMDGOALS),clean test install dist dist-win),)
$(call import,$(src_base)/xsde/makefile)
else
$(call import,$(src_base)/xsde/xsde/makefile)
endif
