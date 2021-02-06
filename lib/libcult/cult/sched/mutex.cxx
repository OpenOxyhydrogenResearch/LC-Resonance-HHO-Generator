// file      : cult/sched/mutex.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/sched/mutex.hxx>
#include <cult/sched/exception.hxx>

namespace Cult
{
  namespace Sched
  {
    Mutex::
    ~Mutex ()
    {
      if (Int e = pthread_mutex_destroy (&mutex_))
        throw Implementation (e);
    }

    Mutex::
    Mutex ()
    {
      if (Int e = pthread_mutex_init (&mutex_, 0))
        throw Implementation (e);
    }

    Void Mutex::
    lock ()
    {
      if (Int e = pthread_mutex_lock (&mutex_))
        throw Implementation (e);
    }

    Boolean Mutex::
    try_lock ()
    {
      Int e (pthread_mutex_trylock (&mutex_));

      switch (e)
      {
      case 0: return true;
      case EBUSY: return false;
      default: throw Implementation (e);
      }
    }

    Void Mutex::
    unlock ()
    {
      if (Int e = pthread_mutex_unlock (&mutex_))
        throw Implementation (e);
    }
  }
}
