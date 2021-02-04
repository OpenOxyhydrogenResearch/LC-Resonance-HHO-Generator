// file      : cult/containers/set.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_CONTAINERS_SET_HXX
#define CULT_CONTAINERS_SET_HXX

#include <cult/types.hxx>

#include <cult/containers/iterator.hxx>

#include <set>

namespace Cult
{
  namespace Containers
  {
    template <typename K, typename C = std::less<K> >
    class Set: public std::set<K, C>
    {
      typedef std::set<K, C> Base;

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
      typedef typename Base::key_type Key;
      typedef typename Base::value_type Value; // Same as Key.
      typedef typename Base::key_compare Compare;

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
      Set (Compare const& comp = Compare ())
          : Base (comp)
      {
      }

      template <typename InputIterator>
      Set (InputIterator first,
           InputIterator last,
           Compare const& comp = Compare ())
          : Base (first, last, comp)
      {
      }

      Set (Set<Key, Compare> const& other)
          : Base (other)
      {
      }

      Set<Key, Compare>&
      operator= (Set<Key, Compare> const& other)
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
      Iterator
      find (Key const& k)
      {
        return Iterator (base ().find (k));
      }

      ConstIterator
      find (Key const& k) const
      {
        return ConstIterator (base ().find (k));
      }

    public:
      Void
      swap (Set<Key, Compare>& other)
      {
        base ().swap (other);
      }
    };
  }
}

#endif  // CULT_CONTAINERS_SET_HXX
