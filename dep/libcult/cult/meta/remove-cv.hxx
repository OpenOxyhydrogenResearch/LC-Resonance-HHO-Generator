// file      : cult/meta/remove-cv.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_META_REMOVE_CV_HXX
#define CULT_META_REMOVE_CV_HXX

#include <cult/meta/remove-c.hxx>
#include <cult/meta/remove-v.hxx>

namespace Cult
{
  namespace Meta
  {
    template <typename X>
    struct remove_cv
    {
      typedef typename remove_v<typename remove_c<X>::R>::R R;
    };
  }
}

#endif  // CULT_META_REMOVE_CV_HXX
