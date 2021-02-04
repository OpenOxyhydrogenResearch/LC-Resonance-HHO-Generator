// file      : cult/mm/counter.ixx
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
      ++value_;
    }

    inline
    Boolean Counter::
    dec_ref ()
    {
      return --value_ == 0;
    }

    inline
    Size Counter::
    count () const
    {
      return value_;
    }
  }
}
