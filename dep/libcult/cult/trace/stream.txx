// file      : cult/trace/stream.txx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace Cult
{
  namespace Trace
  {
    template <typename T>
    inline
    Record&
    operator<< (Stream::Mediator const& mc, T const& arg)
    {
      Stream::Mediator& m (const_cast<Stream::Mediator&> (mc));
      return m.r_ << arg;
    }
  }
}
