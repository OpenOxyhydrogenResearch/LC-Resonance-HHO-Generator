// file      : cult/mm/exceptions.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_MM_EXCEPTIONS_HXX
#define CULT_MM_EXCEPTIONS_HXX

#include <cult/eh/exception.hxx>

#include <new>  // std::bad_alloc

namespace Cult
{
  namespace MM
  {
    typedef std::bad_alloc StdBadAlloc;

    struct Exception: virtual EH::Exception {};

    struct BadAlloc: virtual Exception, StdBadAlloc {};

    //@@ who uses this?
    //
    struct SelfAssignment: virtual Exception {};

    struct NullPointer : virtual Exception {};
  }
}

#endif  // CULT_MM_EXCEPTIONS_HXX
