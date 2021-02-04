// file      : cult/sched/condition.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/sched/condition.hxx>
#include <cult/sched/exception.hxx>

namespace Cult
{
  namespace Sched
  {
    Condition::
    ~Condition ()
    {
      if (Int e = pthread_cond_destroy (&cond_))
        throw Implementation (e);
    }

    Condition::
    Condition (Mutex& mutex)
        : mutex_ (mutex)
    {
      if (Int e = pthread_cond_init (&cond_, 0))
        throw Implementation (e);
    }

    Void Condition::
    signal ()
    {
      if (Int e = pthread_cond_signal (&cond_))
        throw Implementation (e);
    }

    Void Condition::
    broadcast ()
    {
      if (Int e = pthread_cond_broadcast (&cond_))
        throw Implementation (e);
    }

    Void Condition::
    wait ()
    {
      if (Int e = pthread_cond_wait (&cond_, &mutex_.mutex_))
        throw Implementation (e);
    }
  }
}
