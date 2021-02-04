# file      : build/import/libxsd-frontend/stub.make
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

$(call include-once,$(src_root)/xsd-frontend/makefile,$(out_root))

$(call export,\
  l: $(out_root)/xsd-frontend/xsd-frontend.l,\
  cpp-options: $(out_root)/xsd-frontend/xsd-frontend.l.cpp-options)
