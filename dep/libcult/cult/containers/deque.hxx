// file      : cult/containers/deque.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_CONTAINERS_DEQUE_HXX
#define CULT_CONTAINERS_DEQUE_HXX

#include <cult/types.hxx>

#include <cult/containers/iterator.hxx>

#include <deque>

namespace Cult
{
  namespace Containers
  {
    template <typename T>
    class Deque: public std::deque<T>
    {
      typedef std::deque<T> Base;

      Base&
      base ()
      {
        return *this;
      }

      Base const&
      base () const
      {
        return *this;
      }

    public:
      typedef typename Base::value_type Value;


      typedef typename Base::reference Reference;
      typedef typename Base::const_reference ConstReference;


      typedef typename Base::pointer Pointer;
      typedef typename Base::const_pointer ConstPointer;


      typedef
      IteratorAdapter<typename Base::iterator>
      Iterator;

      typedef
      IteratorAdapter<typename Base::const_iterator>
      ConstIterator;


      typedef
      IteratorAdapter<typename Base::reverse_iterator>
      ReverseIterator;

      typedef
      IteratorAdapter<typename Base::const_reverse_iterator>
      ConstReverseIterator;


      // Use Cult::Size and Cult::PtrDifference.
      //
      // typedef Base::size_type;
      // typedef Base::difference_type;

    public:
      explicit
      Deque ()
          : Base ()
      {
      }

      explicit
      Deque (Size size, Value const& value = Value ())
          : Base (size, value)
      {
      }

      template <typename InputIterator>
      Deque (InputIterator first, InputIterator last)
          : Base (first, last)
      {
      }

      Deque (Deque<Value> const& other)
          : Base (other)
      {
      }

      Deque<Value>&
      operator= (Deque<Value> const& other)
      {
        base () = other;
        return *this;
      }

    public:
      Iterator
      begin ()
      {
        return Iterator (base ().begin ());
      }

      Iterator
      end ()
      {
        return Iterator (base ().end ());
      }


      ConstIterator
      begin () const
      {
        return ConstIterator (base ().begin ());
      }

      ConstIterator
      end () const
      {
        return ConstIterator (base ().end ());
      }

      //
      //

      ReverseIterator
      rbegin ()
      {
        return ReverseIterator (base ().rbegin ());
      }

      ReverseIterator
      rend ()
      {
        return ReverseIterator (base ().rend ());
      }


      ConstReverseIterator
      rbegin () const
      {
        return ConstReverseIterator (base ().rbegin ());
      }

      ConstReverseIterator
      rend () const
      {
        return ConstReverseIterator (base ().rend ());
      }

    public:
      Void
      swap (Deque<Value>& other)
      {
        base ().swap (other);
      }
    };
  }
}

#endif  // CULT_CONTAINERS_DEQUE_HXX
