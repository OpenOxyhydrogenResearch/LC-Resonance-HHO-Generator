// file      : cult/mm/arch/i386/i486/i586/i686/x86_64/counter.ixx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

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
      asm volatile ("lock; incq %0"
                    :"=m" (value_)
                    :"m" (value_));
    }

    inline
    Boolean Counter::
    dec_ref ()
    {
      register unsigned char r;

      asm volatile("lock; decq %0; setz %1"
                   :"=m" (value_), "=rm" (r)
                   :"m" (value_));

      return r != 0;
    }

    inline
    Size Counter::
    count () const
    {
      return value_;
    }
  }
}
