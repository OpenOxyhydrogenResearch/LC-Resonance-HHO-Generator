// file      : cult/meta/remove-v.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_META_REMOVE_V_HXX
#define CULT_META_REMOVE_V_HXX

namespace Cult
{
  namespace Meta
  {
    template <typename X>
    struct remove_v
    {
      typedef X R;
    };

    template <typename X>
    struct remove_v<X volatile>
    {
      typedef X R;
    };
  }
}

#endif  // CULT_META_REMOVE_V_HXX
