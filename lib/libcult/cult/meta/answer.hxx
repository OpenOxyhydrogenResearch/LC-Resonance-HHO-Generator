// file      : cult/meta/answer.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_META_ANSWER_HXX
#define CULT_META_ANSWER_HXX

#include <cult/types/fundamental.hxx>

namespace Cult
{
  namespace Meta
  {
    struct Yes
    {
      Char filling;
    };

    struct No
    {
      Char filling[2];
    };
  }
}

#endif  // CULT_META_ANSWER_HXX
