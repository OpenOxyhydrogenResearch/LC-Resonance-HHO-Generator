// file      : cult/trace/log.ixx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace Cult
{
  namespace Trace
  {
    inline
    Log& Log::
    operator<< (Record const& r)
    {
      if (r.level () <= level_)
        log_impl (r);

      return *this;
    }
  }
}
