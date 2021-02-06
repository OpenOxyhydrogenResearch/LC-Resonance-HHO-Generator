// file      : cult/containers/iterator.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_CONTAINERS_ITERATOR_HXX
#define CULT_CONTAINERS_ITERATOR_HXX

#include <cult/types.hxx>

#include <iterator>

namespace Cult
{
  namespace Containers
  {
    template <typename I>
    class IteratorAdapter
    {
    public:
      typedef typename std::iterator_traits<I>::value_type Value;
      typedef typename std::iterator_traits<I>::difference_type Difference;
      typedef typename std::iterator_traits<I>::pointer Pointer;
      typedef typename std::iterator_traits<I>::reference Reference;
      typedef typename std::iterator_traits<I>::iterator_category Category;

      // For compatibility with std::iterator_traits
      //
    public:
      typedef Value value_type;
      typedef Reference reference;
      typedef Pointer pointer;
      typedef Category iterator_category;
      typedef Difference difference_type;

    public:
      IteratorAdapter ()
          : i_ () // i_ can be of a pointer type.
      {
      }

      explicit
      IteratorAdapter (I const& i)
          : i_ (i)
      {
      }

      template <typename J>
      IteratorAdapter (IteratorAdapter<J> const& j)
          : i_ (j.i_)
      {
      }
    public:
      // Forward iterator requirements.
      //
      Reference
      operator* () const
      {
        return *i_;
      }

      Pointer
      operator-> () const
      {
        return &(*i_);
      }

      IteratorAdapter&
      operator++ ()
      {
        ++i_;
        return *this;
      }

      IteratorAdapter
      operator++ (Int)
      {
        return IteratorAdapter (i_++);
      }

    public:
      // Bidirectional iterator requirements.
      //
      IteratorAdapter&
      operator-- ()
      {
        --i_;
        return *this;
      }

      IteratorAdapter
      operator-- (Int)
      {
        return IteratorAdapter (i_--);
      }

    public:
      // Random access iterator requirements.
      //
      Reference
      operator[] (Difference n) const
      {
        return i_[n];
      }

      IteratorAdapter
      operator+ (Difference n) const
      {
        return IteratorAdapter (i_ + n);
      }

      IteratorAdapter&
      operator+= (Difference n)
      {
        i_ += n;
        return *this;
      }

      IteratorAdapter
      operator- (Difference n) const
      {
        return IteratorAdapter (i_ - n);
      }

      IteratorAdapter&
      operator-= (Difference n)
      {
        i_ += n;
        return *this;
      }

    public:
      I const&
      base () const
      {
        return i_;
      }

      // @@ This is needed so that call to functions such as erase()
      // be possible without writing a wrapper. This should be a temporary
      // measure.

      operator I& ()
      {
        return i_;
      }

      operator I const& () const
      {
        return i_;
      }

    private:
      template<typename>
      friend class IteratorAdapter;

      I i_;
    };

    // Note: We use different types for left- and right-hand-side
    // arguments to allow comparison between iterator and const_iterator.
    //

    // Forward iterator requirements.
    //
    template <typename I, typename J>
    inline Boolean
    operator== (IteratorAdapter<I> const& i, IteratorAdapter<J> const& j)
    {
      return i.base () == j.base ();
    }

    template <typename I, typename J>
    inline Boolean
    operator!= (IteratorAdapter<I> const& i, IteratorAdapter<J> const& j)
    {
      return i.base () != j.base ();
    }

    // Random access iterator requirements
    //
    template <typename I, typename J>
    inline Boolean
    operator< (IteratorAdapter<I> const& i, IteratorAdapter<J> const& j)
    {
      return i.base() < j.base();
    }

    template <typename I, typename J>
    inline Boolean
    operator> (IteratorAdapter<I> const& i, IteratorAdapter<J> const& j)
    {
      return i.base() > j.base();
    }

    template <typename I, typename J>
    inline Boolean
    operator<= (IteratorAdapter<I> const& i, IteratorAdapter<J> const& j)
    {
      return i.base() <= j.base();
    }

    template <typename I, typename J>
    inline Boolean
    operator>= (IteratorAdapter<I> const& i, IteratorAdapter<J> const& j)
    {
      return i.base() >= j.base();
    }

    template <typename I, typename J>
    inline typename IteratorAdapter<I>::Difference
    operator- (IteratorAdapter<I> const& i, IteratorAdapter<J> const& j)
    {
      return i.base () - j.base ();
    }

    template <typename I>
    IteratorAdapter<I>
    operator+ (typename IteratorAdapter<I>::Difference n,
               IteratorAdapter<I> const& x)
    {
      return x + n;
    }
  }
}

#endif  // CULT_CONTAINERS_ITERATOR_HXX
