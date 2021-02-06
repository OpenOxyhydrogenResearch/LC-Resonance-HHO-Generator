// file      : cult/containers/stack.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_CONTAINERS_STACK_HXX
#define CULT_CONTAINERS_STACK_HXX

#include <cult/types.hxx>

#include <cult/containers/deque.hxx>

namespace Cult
{
  namespace Containers
  {
    template <typename T, typename C = Deque<T> >
    class Stack
    {
    public:
      typedef C Container;
      typedef typename Container::Value Value;


    public:
      explicit
      Stack (Container const& c = Container())
          : c_ (c)
      {
      }

      Boolean
      empty () const
      {
        return c_.empty();
      }

      Size
      size () const
      {
        return c_.size();
      }

      Value&
      top ()
      {
        return c_.back();
      }

      Value const&
      top () const
      {
        return c_.back();
      }

      Void
      push (const Value& x)
      {
        c_.push_back(x);
      }

      Void
      pop()
      {
        c_.pop_back();
      }

    protected:
      Container c_;
    };

    /*
    template <class T, class Container>
    bool operator==(const stack<T, Container>& x,
                    const stack<T, Container>& y);
    template <class T, class Container>
    bool operator< (const stack<T, Container>& x,
                    const stack<T, Container>& y);
    template <class T, class Container>
    bool operator!=(const stack<T, Container>& x,
                    const stack<T, Container>& y);
    template <class T, class Container>
    bool operator> (const stack<T, Container>& x,
                    const stack<T, Container>& y);
    template <class T, class Container>
    bool operator>=(const stack<T, Container>& x,
                    const stack<T, Container>& y);
    template <class T, class Container>
    bool operator<=(const stack<T, Container>& x,
                    const stack<T, Container>& y);
    */
  }
}

#endif  // CULT_CONTAINERS_STACK_HXX
