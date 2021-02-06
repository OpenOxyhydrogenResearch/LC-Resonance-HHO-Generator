// file      : cult/sched/spin.ixx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/sched/exception.hxx>

namespace Cult
{
  namespace Sched
  {
    inline
    Void Spin::
    lock ()
    {
      if (Int e = pthread_spin_lock (&spin_))
        throw Implementation (e);
    }

    inline
    Boolean Spin::
    try_lock ()
    {
      Int e (pthread_spin_trylock (&spin_));

      switch (e)
      {
      case 0: return true;
      case EBUSY: return false;
      default: throw Implementation (e);
      }
    }

    inline
    Void Spin::
    unlock ()
    {
      if (Int e = pthread_spin_unlock (&spin_))
        throw Implementation (e);
    }
  }
}

