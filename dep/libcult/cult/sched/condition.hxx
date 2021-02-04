// file      : cult/sched/condition.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_SCHED_CONDITION_HXX
#define CULT_SCHED_CONDITION_HXX

#include <cult/types/fundamental.hxx>

#include <cult/sched/mutex.hxx>

#include <pthread.h>

namespace Cult
{
  namespace Sched
  {
    class Condition: public NonCopyable
    {
    public:
      ~Condition ();

      Condition (Mutex& mutex);

      Void
      signal ();

      Void
      broadcast ();

      Void
      wait ();

    private:
      Mutex& mutex_;
      pthread_cond_t cond_;
    };
  }
}

#endif  // CULT_SCHED_CONDITION_HXX
