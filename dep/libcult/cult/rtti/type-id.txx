// file      : cult/rtti/type-id.txx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace Cult
{
  namespace RTTI
  {
    template <typename X>
    inline
    TypeId::
    TypeId (X const volatile& x)
        : ti_ (&typeid (x))
    {
    }
  }
}
