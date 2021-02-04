# file      : build/export/libcult/stub.make
# author    : Boris Kolpackov <boris@kolpackov.net>
# copyright : Copyright (c) 2005-2010 Boris Kolpackov
# license   : GNU GPL v2; see accompanying LICENSE file

$(call include-once,$(src_root)/cult/makefile,$(out_root))

$(call export,\
  l: $(out_root)/cult/cult.l,\
  cpp-options: $(out_root)/cult/cult.l.cpp-options)
