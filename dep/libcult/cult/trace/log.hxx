// file      : cult/trace/log.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_TRACE_LOG_HXX
#define CULT_TRACE_LOG_HXX

#include <cult/types/fundamental.hxx>

#include <cult/trace/record.hxx>

namespace Cult
{
  namespace Trace
  {
    class Log: public NonCopyable
    {
    public:
      Log (Int level = -1);

    public:
      Int
      level () const;

      Void
      level (Int level);

    public:
      //@@ should it be virtual?
      //
      Log&
      operator<< (Record const& r);

    public:
      static Log&
      instance ();

    private:
      Void
      log_impl (Record const& r);

    private:
      Int level_;
    };
  }
}

#include <cult/trace/log.ixx>

#endif  // CULT_TRACE_LOG_HXX
