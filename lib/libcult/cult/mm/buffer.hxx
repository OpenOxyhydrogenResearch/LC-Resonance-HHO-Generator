// file      : cult/mm/buffer.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_MM_BUFFER_HXX
#define CULT_MM_BUFFER_HXX

#include <cult/types/fundamental.hxx>

#include <cult/mm/exception.hxx>

namespace Cult
{
  namespace MM
  {
    //@@ why can't capacity be zero?
    //

    class Buffer
    {
    public:
      struct Bounds: virtual Exception {};
      struct ZeroCapacity: virtual Exception {};

    public:
      virtual
      ~Buffer ();

      Buffer (Size capacity, Size size = 0)
        throw (ZeroCapacity, Bounds, BadAlloc);

      Buffer (Void const*, Size size);

      Buffer (Buffer const& other);

    private:
      Buffer&
      operator= (Buffer const&);

    public:
      Size
      capacity () const throw ();

      // Returns true if the underlying buffer has been moved.
      //
      Boolean
      capacity (Size capacity) throw (ZeroCapacity, Bounds, BadAlloc);

    public:
      Size
      size () const throw ();

      Void
      size (Size size) throw (Bounds);

    public:
      Index
      position () const throw ();

      Void
      position (Index) throw (Bounds);

    public:
      Char const*
      data () const;

      Char*
      data ();

    private:
      Void* b_;
      Size c_, s_, p_;
    };
  }

  using MM::Buffer;
}

#endif  // CULT_MM_BUFFER_HXX
