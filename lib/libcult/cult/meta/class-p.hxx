// file      : cult/meta/class-p.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_META_CLASS_HXX
#define CULT_META_CLASS_HXX

#include <cult/types/fundamental.hxx>

#include <cult/meta/answer.hxx>

namespace Cult
{
  namespace Meta
  {
    template <typename X>
    class class_p
    {
      //@@ g++ bug 14881
    public:
      template <typename Y> static No test (...);
      template <typename Y> static Yes test (Void* Y::*);

    public:
      //@@ Qualification bug fixed for g++ 3.4.0.
      static Boolean const r =
        sizeof (class_p<X>::template test<X> (0)) == sizeof (Yes);
    };
  }
}

#endif  // CULT_META_CLASS_HXX
