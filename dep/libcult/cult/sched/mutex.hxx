// file      : cult/sched/mutex.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_SCHED_MUTEX_HXX
#define CULT_SCHED_MUTEX_HXX

#include <cult/types/fundamental.hxx>

#include <pthread.h>

namespace Cult
{
  namespace Sched
  {
    class Mutex: public NonCopyable
    {
    public:
      ~Mutex ();

      Mutex ();

      Void
      lock ();

      Boolean
      try_lock ();

      Void
      unlock ();

    private:
      friend class Condition;

      pthread_mutex_t mutex_;
    };
  }
}

#endif  // CULT_SCHED_MUTEX_HXX
