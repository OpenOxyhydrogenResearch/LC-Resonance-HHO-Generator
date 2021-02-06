# file      : build/import/libbackend-elements/stub.make
# author    : Boris Kolpackov <boris@kolpackov.net>
# copyright : Copyright (c) 2005-2010 Boris Kolpackov
# license   : GNU GPL v2; see accompanying LICENSE file

$(call include-once,$(src_root)/backend-elements/makefile,$(out_root))

#$(out_root)/backend-elements/backend-elements.l

$(call export,\
  l: ,\
  cpp-options: $(out_root)/backend-elements/backend-elements.l.cpp-options)

