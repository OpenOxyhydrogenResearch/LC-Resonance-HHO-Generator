// file      : cult/mm/buffer.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/mm/buffer.hxx>

#include <cstdlib> // malloc, realloc, free
#include <cstring> // memcpy

namespace Cult
{
  namespace MM
  {
    Buffer::
    ~Buffer ()
    {
      std::free (b_);
    }

    Buffer::
    Buffer (Size capacity, Size size) throw (ZeroCapacity, Bounds, BadAlloc)
        : c_ (capacity), s_ (size), p_ (0)
    {
      if (c_ == 0) throw ZeroCapacity ();
      if (s_ > c_) throw Bounds ();

      b_ = std::malloc (c_);

      if (b_ == 0) throw BadAlloc ();
    }

    Buffer::
    Buffer (void const* p, size_t s)
      : c_ (s), s_ (s), p_ (0)
    {
      if (c_ == 0) throw ZeroCapacity ();

      b_ = std::malloc (c_);

      if (b_ == 0) throw BadAlloc ();

      std::memcpy (b_, p, s);
    }


    Buffer::
    Buffer (Buffer const& b)
        : c_ (b.c_), s_ (b.s_), p_ (b.p_)
    {
      b_ = std::malloc (c_);

      if (b_ == 0) throw BadAlloc ();

      std::memcpy (b_, b.b_, s_);
    }
/*
    Buffer&
    operator= (Buffer const&)
    {
      return *this;
    }
*/

    // capacity
    //

    Size Buffer::
    capacity () const throw ()
    {
      return c_;
    }

    Boolean Buffer::
    capacity (Size c) throw (ZeroCapacity, Bounds, BadAlloc)
    {
      if (c == 0) throw ZeroCapacity ();
      if (s_ > c) throw Bounds ();

      Void* b (std::realloc (b_, c));

      if (b == 0) throw BadAlloc ();

      c_ = c;

      if (b == b_) return false;

      b_ = b;

      return true;
    }

    // size
    //

    Size Buffer::
    size () const throw ()
    {
      return s_;
    }

    void Buffer::
    size (Size s) throw (Bounds)
    {
      if (s > c_ || p_ > s) throw Bounds ();

      s_ = s;
    }

    // position
    //

    Index Buffer::
    position () const throw ()
    {
      return p_;
    }

    Void Buffer::
    position (Index p) throw (Bounds)
    {
      if (p > s_) throw Bounds ();

      p_ = p;
    }


    Char const* Buffer::
    data () const
    {
      return reinterpret_cast<Char const*> (b_);
    }

    Char* Buffer::
    data ()
    {
      return reinterpret_cast<Char*> (b_);
    }
  }
}
