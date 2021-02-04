// file      : cult/containers/pair.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_CONTAINERS_PAIR_HXX
#define CULT_CONTAINERS_PAIR_HXX

#include <utility>

namespace Cult
{
  namespace Containers
  {
    template <typename T1, typename T2>
    class Pair: public std::pair<T1, T2>
    {
      typedef std::pair<T1, T2> Base;

      Base&
      base ()
      {
        return *this;
      }

    public:
      typedef T1 First;
      typedef T2 Second;

    public:
      Pair ()
          : Base ()
      {
      }

      Pair (First const& first, Second const& second)
          : Base (first, second)
      {
      }

      template <typename X, typename Y>
      Pair (std::pair<X, Y> const& pair)
          : Base (pair)
      {
      }

      template <typename X, typename Y>
      Pair&
      operator= (std::pair<X, Y> const& pair)
      {
        base () = pair;
        return *this;
      }
    };
  }
}

#endif  // CULT_CONTAINERS_PAIR_HXX
