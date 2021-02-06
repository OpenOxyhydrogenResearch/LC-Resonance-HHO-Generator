// file      : cult/meta/polymorphic-p.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_META_POLYMORPHIC_HXX
#define CULT_META_POLYMORPHIC_HXX

#include <cult/types/fundamental.hxx>

#include <cult/meta/class-p.hxx>
#include <cult/meta/remove-cv.hxx>

namespace Cult
{
  namespace Meta
  {
    template <typename CVX>
    class polymorphic_p
    {
      typedef typename remove_cv<CVX>::R X;

      template <typename Y, Boolean c>
      struct impl
      {
        static const Boolean r = false;
      };

      template <typename Y>
      struct impl<Y, true>
      {
        //@@ private

        struct S1 : Y
        {
          S1 ();
        };

        struct S2 : Y
        {
          S2 ();

          virtual
          ~S2 () throw ();
        };

        static const Boolean r = sizeof (S1) == sizeof (S2);
      };

    public:
      static const Boolean r = impl<X, class_p<X>::r>::r;
    };
  }
}

#endif  // CULT_META_POLYMORPHIC_HXX
