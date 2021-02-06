// file      : cult/sched/spin.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_SCHED_SPIN_HXX
#define CULT_SCHED_SPIN_HXX

#include <cult/types/fundamental.hxx>

#include <pthread.h>

namespace Cult
{
  namespace Sched
  {
    class Spin: public NonCopyable
    {
    public:
      ~Spin ();

      Spin ();

      Void
      lock ();

      Boolean
      try_lock ();

      Void
      unlock ();

    private:
      pthread_spinlock_t spin_;
    };
  }
}

#include <cult/sched/spin.ixx>

#endif  // CULT_SCHED_SPIN_HXX
