// file      : cult/containers/vector.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_CONTAINERS_VECTOR_HXX
#define CULT_CONTAINERS_VECTOR_HXX

#include <cult/types.hxx>

#include <cult/containers/iterator.hxx>

#include <vector>

namespace Cult
{
  namespace Containers
  {
    template <typename T>
    class Vector: public std::vector<T>
    {
      typedef std::vector<T> Base;

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
      Vector ()
          : Base ()
      {
      }

      explicit
      Vector (Size size, Value const& value = Value ())
          : Base (size, value)
      {
      }

      template <typename InputIterator>
      Vector (InputIterator first, InputIterator last)
          : Base (first, last)
      {
      }

      Vector (Vector<Value> const& other)
          : Base (other)
      {
      }

      Vector<Value>&
      operator= (Vector<Value> const& other)
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
      swap (Vector<Value>& other)
      {
        base ().swap (other);
      }
    };
  }
}

#endif  // CULT_CONTAINERS_VECTOR_HXX
