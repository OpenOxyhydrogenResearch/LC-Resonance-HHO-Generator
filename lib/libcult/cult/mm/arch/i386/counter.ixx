// file      : cult/mm/arch/i386/counter.ixx
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
      asm volatile ("lock; incl %0"
                    :"=m" (value_)
                    :"m" (value_));
    }

    inline
    Boolean Counter::
    dec_ref ()
    {
      register unsigned char r;

      asm volatile("lock; decl %0; setz %1"
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
