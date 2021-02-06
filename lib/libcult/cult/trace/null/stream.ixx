// file      : cult/trace/null/stream.ixx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace Cult
{
  namespace Trace
  {
    inline
    Stream::
    Stream (Char const* id, Int level, Log& l)
        : id_ (id), level_ (level), log_ (l)
    {
    }

    inline
    Char const* Stream::
    id () const
    {
      return id_;
    }

    inline
    Int Stream::
    level () const
    {
      return level_;
    }

    inline
    Stream& Stream::
    operator << (Record const& r)
    {
      return *this;
    }

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
    }

    inline
    Record&
    operator<< (Stream::Mediator const& mc, Int level)
    {
      Stream::Mediator& m (const_cast<Stream::Mediator&> (mc));
      // m.r_.level (level);
      return m.r_;
    }

    inline
    Record&
    operator<< (Stream::Mediator const& mc, Char const* s)
    {
      return const_cast<Stream::Mediator&> (mc).r_;
    }
  }
}
