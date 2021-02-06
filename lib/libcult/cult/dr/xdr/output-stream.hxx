// file      : cult/dr/xdr/output-stream.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_DR_XDR_OUTPUT_STREAM_HXX
#define CULT_DR_XDR_OUTPUT_STREAM_HXX

#include <cult/types.hxx>

#include <cult/eh/exception.hxx>

#include <cult/mm/buffer.hxx>

#include <rpc/xdr.h>

namespace Cult
{
  namespace DR
  {
    namespace XDR
    {
      struct Insertion: virtual EH::Exception {};

      //@@ I think I should use refernce to buffer instead of Shptr.
      //   To keep it simple, so to speak.
      //
      class OutputStream: public NonCopyable
      {
      public:
        OutputStream (Size hint = 0);

        ~OutputStream ();

      public:
        Shptr<Buffer>
        buffer ();

      public:
        OutputStream&
        operator<< (Boolean);

        OutputStream&
        operator<< (Int8);

        OutputStream&
        operator<< (UnsignedInt8);

        OutputStream&
        operator<< (Int16);

        OutputStream&
        operator<< (UnsignedInt16);

        OutputStream&
        operator<< (Int32);

        OutputStream&
        operator<< (UnsignedInt32);

        OutputStream&
        operator<< (Int64);

        OutputStream&
        operator<< (UnsignedInt64);

        OutputStream&
        operator<< (String const&);

      public:
        Void
        write (Buffer const& buffer);

      private:
        Void
        ensure_space (Size size);

        Void
        update_position (Size position);

      private:
        ::XDR xdr_;
        Shptr<Buffer> buffer_;
      };
    }
  }
}

#endif  // CULT_DR_XDR_OUTPUT_STREAM_HXX
