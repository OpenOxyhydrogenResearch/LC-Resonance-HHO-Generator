// file      : cult/eh/exception.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_EH_EXCEPTION_HXX
#define CULT_EH_EXCEPTION_HXX

#include <cult/types/fundamental.hxx>

#include <exception> // std::exception

namespace Cult
{
  namespace EH
  {
    struct Exception : std::exception
    {
      virtual Char const*
      what () const throw ();
    };
  }
}

#endif  // CULT_EH_EXCEPTION_HXX
