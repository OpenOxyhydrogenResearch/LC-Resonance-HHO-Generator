// file      : cult/sched/exception.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_SCHED_EXCEPTION_HXX
#define CULT_SCHED_EXCEPTION_HXX

#include <cult/types/fundamental.hxx>

#include <cult/eh/exception.hxx>
#include <cult/os/exception.hxx>

namespace Cult
{
  namespace Sched
  {
    struct Exception: virtual EH::Exception {};

    struct Implementation: virtual Exception, virtual OS::Exception
    {
      Implementation (Int code) throw ()
          : OS::Exception (code)
      {
      }
    };
  }
}

#endif  // CULT_SCHED_EXCEPTION_HXX
