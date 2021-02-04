# file      : build/import/libfrontend-elements/stub.make
# author    : Boris Kolpackov <boris@kolpackov.net>
# copyright : Copyright (c) 2005-2010 Boris Kolpackov
# license   : GNU GPL v2; see accompanying LICENSE file

$(call include-once,$(src_root)/frontend-elements/makefile,$(out_root))

$(call export,\
  l: $(out_root)/frontend-elements/frontend-elements.l,\
  cpp-options: $(out_root)/frontend-elements/frontend-elements.l.cpp-options)
