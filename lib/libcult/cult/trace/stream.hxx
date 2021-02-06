// file      : cult/trace/stream.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_TRACE_STREAM_HXX
#define CULT_TRACE_STREAM_HXX

#include <cult/types/fundamental.hxx>

#include <cult/trace/log.hxx>
#include <cult/trace/record.hxx>

namespace Cult
{
  namespace Trace
  {
    class Stream: public NonCopyable
    {
    public:
      Stream (Char const* id, Int level, Log& l = Log::instance ());

    public:
      Char const*
      id () const;

      Int
      level () const;

    public:
      Stream&
      operator<< (Record const& r);

    private:
      struct Mediator
      {
        ~Mediator ();
        Mediator (Stream&);

        Stream& s_;
        Record  r_;
      };

      friend Record&
      operator<< (Mediator const&, Int level);

      friend Record&
      operator<< (Mediator const&, Char const* s);

      template <typename T>
      friend Record&
      operator<< (Mediator const&, T const& arg);

    private:
      Char const* id_;
      Int level_;
      Log& log_;
    };
  }
}

#ifndef CULT_TRACE_NULL

#include <cult/trace/stream.ixx>
#include <cult/trace/stream.txx>

#else

#include <cult/trace/null/stream.ixx>
#include <cult/trace/null/stream.txx>

#endif

#endif  // CULT_TRACE_STREAM_HXX
