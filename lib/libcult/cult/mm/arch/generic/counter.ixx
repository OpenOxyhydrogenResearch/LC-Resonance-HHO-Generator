// file      : cult/mm/arch/generic/counter.ixx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/sched/lock.hxx>

namespace Cult
{
  namespace MM
  {
    inline
    Counter::
    Counter ()
        : value_ (1)
    {
    }

    inline
    Void Counter::
    inc_ref ()
    {
      Sched::Lock l (spin_);

      ++value_;
    }

    inline
    Boolean Counter::
    dec_ref ()
    {
      Sched::Lock l (spin_);

      return --value_ == 0;

    }

    inline
    Size Counter::
    count () const
    {
      Sched::Lock l (spin_);

      return value_;
    }
  }
}
