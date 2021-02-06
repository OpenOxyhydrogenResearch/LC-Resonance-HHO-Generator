// file      : cult/trace/stream.ixx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace Cult
{
  namespace Trace
  {
    // Stream::Mediator
    //
    inline
    Stream::Mediator::
    Mediator (Stream& s)
        : s_ (s), r_ (s.id (), s.level ())
    {
    }

    inline
    Stream::Mediator::
    ~Mediator ()
    {
      s_ << r_;
    }

    // Stream
    //
    inline
    Stream::
    Stream (Char const* id, Int level, Log& log)
        : id_ (id), level_ (level), log_ (log)
    {
    }

    inline
    char const* Stream::
    id () const
    {
      return id_;
    }

    inline
    int Stream::
    level () const
    {
      return level_;
    }

    //
    //
    inline
    Stream& Stream::
    operator << (Record const& r)
    {
      log_ << r;
      return *this;
    }

    inline
    Record&
    operator<< (Stream::Mediator const& mc, Int level)
    {
      Stream::Mediator& m (const_cast<Stream::Mediator&> (mc));
      m.r_.level (level);
      return m.r_;
    }

    inline
    Record&
    operator<< (Stream::Mediator const& mc, Char const* s)
    {
      Stream::Mediator& m (const_cast<Stream::Mediator&> (mc));
      return m.r_ << s;
    }
  }
}
