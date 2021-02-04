// file      : cult/trace/record.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_TRACE_RECORD_HXX
#define CULT_TRACE_RECORD_HXX

#include <cult/types/fundamental.hxx>

#include <cstring> // memset
#include <ostream>
#include <streambuf>

namespace Cult
{
  namespace Trace
  {
    class Record: public NonCopyable
    {
    public:
      Record (Char const* id, Int level);

    public:
      Char const*
      text () const;

      Char const*
      id () const;

      Int
      level () const;

      Void
      level (Int);

    public:
      template <typename T>
      Record&
      operator<< (T const& arg);

    private:
      Char const* id_;
      Int level_;

      //@@ need to wrap streambuf.
      //
      class FixedBuffer : public std::streambuf
      {
      public:
        FixedBuffer (Char* buf, Size size)
        {
          std::memset (buf, 0, size);
          setp (buf, buf + size - 1);
        };

        virtual int_type
        overflow (int_type c)
        {
          return c;
        }
      };

#ifndef CULT_TRACE_NULL
      char buf_[1024];
      FixedBuffer sbuf_;
      std::ostream os_;
#endif
    };
  }
}

#ifndef CULT_TRACE_NULL

#include <cult/trace/record.ixx>
#include <cult/trace/record.txx>

#else

#include <cult/trace/null/record.ixx>
#include <cult/trace/null/record.txx>

#endif


#endif  // CULT_TRACE_RECORD_HXX
