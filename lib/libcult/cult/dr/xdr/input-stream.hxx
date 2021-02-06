// file      : cult/dr/xdr/input-stream.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_DR_XDR_INPUT_STREAM_HXX
#define CULT_DR_XDR_INPUT_STREAM_HXX

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
      struct Extraction: virtual EH::Exception {};

      class InputStream: public NonCopyable
      {
      public:
        InputStream (Shptr<Buffer> buffer);

        ~InputStream ();

      public:
        InputStream&
        operator>> (Boolean&);

        InputStream&
        operator>> (Int8&);

        InputStream&
        operator>> (UnsignedInt8&);

        InputStream&
        operator>> (Int16&);

        InputStream&
        operator>> (UnsignedInt16&);

        InputStream&
        operator>> (Int32&);

        InputStream&
        operator>> (UnsignedInt32&);

        InputStream&
        operator>> (Int64&);

        InputStream&
        operator>> (UnsignedInt64&);

        InputStream&
        operator>> (String&);

      public:
        Void
        read (Buffer& buffer, Size size);

        Boolean
        eos () const;

      private:
        ::XDR xdr_;
        Shptr<Buffer> buffer_;
      };
    }
  }
}

#endif  // CULT_DR_XDR_INPUT_STREAM_HXX
