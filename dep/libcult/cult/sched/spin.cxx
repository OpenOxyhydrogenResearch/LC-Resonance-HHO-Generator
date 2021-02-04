// file      : cult/sched/spin.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/sched/spin.hxx>
#include <cult/sched/exception.hxx>

namespace Cult
{
  namespace Sched
  {
    Spin::
    ~Spin ()
    {
      if (Int e = pthread_spin_destroy (&spin_))
        throw Implementation (e);
    }

    Spin::
    Spin ()
    {
      if (Int e = pthread_spin_init (&spin_, PTHREAD_PROCESS_PRIVATE))
        throw Implementation (e);
    }
  }
}

