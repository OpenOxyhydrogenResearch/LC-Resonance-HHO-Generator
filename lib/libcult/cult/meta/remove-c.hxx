// file      : cult/meta/remove-c.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_META_REMOVE_C_HXX
#define CULT_META_REMOVE_C_HXX

namespace Cult
{
  namespace Meta
  {
    template <typename X>
    struct remove_c
    {
      typedef X R;
    };

    template <typename X>
    struct remove_c<X const>
    {
      typedef X R;
    };
  }
}

#endif  // CULT_META_REMOVE_C_HXX
