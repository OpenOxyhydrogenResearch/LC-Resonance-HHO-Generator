// file      : cult/trace/record.txx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace Cult
{
  namespace Trace
  {
    template <typename T>
    inline
    Record& Record::
    operator<< (T const& arg)
    {
      os_ << arg;
      return *this;
    }
  }
}
