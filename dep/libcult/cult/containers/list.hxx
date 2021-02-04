// file      : cult/containers/list.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_CONTAINERS_LIST_HXX
#define CULT_CONTAINERS_LIST_HXX

#include <cult/types.hxx>

#include <cult/containers/iterator.hxx>

#include <list>

namespace Cult
{
  namespace Containers
  {
    template <typename T>
    class List: public std::list<T>
    {
      typedef std::list<T> Base;

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
      List ()
          : Base ()
      {
      }

      explicit
      List (Size size, Value const& value = Value ())
          : Base (size, value)
      {
      }

      template <typename InputIterator>
      List (InputIterator first, InputIterator last)
          : Base (first, last)
      {
      }

      List (List<Value> const& other)
          : Base (other)
      {
      }

      List<Value>&
      operator= (List<Value> const& other)
      {
        base () = other;
        return *this;
      }

    public:
      Void
      swap (List<Value>& other)
      {
        base ().swap (other);
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
      Iterator
      insert (Iterator const& p, Value const& x)
      {
        return Iterator (base ().insert (p.base (), x));
      }

      template <typename I>
      Void
      insert (Iterator const& p, I const& first, I const& last)
      {
        base ().insert (p.base (), first, last);
      }

      template <typename I>
      Void
      insert (Iterator const& p,
              IteratorAdapter<I> const& first,
              IteratorAdapter<I> const& last)
      {
        base ().insert (p.base (), first.base (), last.base ());
      }

      Iterator
      erase (Iterator const& i)
      {
        return Iterator (base ().erase (i.base ()));
      }
    };
  }
}

#endif  // CULT_CONTAINERS_LIST_HXX
