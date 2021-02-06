// file      : cult/trace/log.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/trace/log.hxx>

#include <iostream>

namespace Cult
{
  namespace Trace
  {
    Log::
    Log (Int level)
        : level_ (level)
    {
    }

    Int Log::
    level () const
    {
      return level_;
    }

    Void Log::
    level (Int level)
    {
      level_ = level;
    }

    Log& Log::
    instance ()
    {
      //@@ Need to use -once initialization. Plus is it legal to
      //   use trace in (static) dtors?
      //
      static Log log;
      return log;
    }

    Void Log::
    log_impl (Record const& r)
    {
      std::cerr << '[' << r.id () << ':' << r.level () << "] " << r.text ()
                << std::endl;
    }
  }
}
