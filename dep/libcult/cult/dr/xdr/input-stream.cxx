// file      : cult/dr/xdr/input-stream.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/dr/xdr/input-stream.hxx>

namespace Cult
{
  namespace DR
  {
    namespace XDR
    {
      InputStream::
      InputStream (Shptr<Buffer> buffer)
          : buffer_ (buffer)
      {
        xdrmem_create (&xdr_, buffer_->data (), buffer_->size (), XDR_DECODE);
      }

      InputStream::
      ~InputStream ()
      {
        xdr_destroy (&xdr_);
      }

      InputStream& InputStream::
      operator>> (Boolean& v)
      {
        bool_t b;

        if (!xdr_bool (&xdr_, &b))
          throw Extraction ();

        v = b;

        return *this;
      }

      InputStream& InputStream::
      operator>> (Int8& v)
      {
        if (!xdr_int8_t (&xdr_, &v))
          throw Extraction ();

        return *this;
      }

      InputStream& InputStream::
      operator>> (UnsignedInt8& v)
      {
        if (!xdr_uint8_t (&xdr_, &v))
          throw Extraction ();

        return *this;
      }

      InputStream& InputStream::
      operator>> (Int16& v)
      {
        if (!xdr_int16_t (&xdr_, &v))
          throw Extraction ();

        return *this;
      }

      InputStream& InputStream::
      operator>> (UnsignedInt16& v)
      {
        if (!xdr_uint16_t (&xdr_, &v))
          throw Extraction ();

        return *this;
      }

      InputStream& InputStream::
      operator>> (Int32& v)
      {
        if (!xdr_int32_t (&xdr_, &v))
          throw Extraction ();

        return *this;
      }

      InputStream& InputStream::
      operator>> (UnsignedInt32& v)
      {
        if (!xdr_uint32_t (&xdr_, &v))
          throw Extraction ();

        return *this;
      }

      InputStream& InputStream::
      operator>> (Int64& v)
      {
        if (!xdr_int64_t (&xdr_, (int64_t*)&v))
          throw Extraction ();

        return *this;
      }

      InputStream& InputStream::
      operator>> (UnsignedInt64& v)
      {
        if (!xdr_uint64_t (&xdr_, (uint64_t*)&v))
          throw Extraction ();

        return *this;
      }

      InputStream& InputStream::
      operator>> (String& v)
      {
        UnsignedInt32 size;

        if (!xdr_uint32_t (&xdr_, &size))
          throw Extraction ();

        // I dare to change the guts!
        //
        v.resize (size);

        Char* p (const_cast<Char*> (v.data ()));

        if (!xdr_opaque (&xdr_, p, size))
          throw Extraction ();

        return *this;
      }

      Void InputStream::
      read (Buffer& buffer, Size size)
      {
        Size new_size (buffer.position () + size);

        buffer.capacity (new_size);

        if (!xdr_opaque (&xdr_, buffer.data () + buffer.position (), size))
          throw Extraction ();

        buffer.size (new_size);
      }

      Boolean InputStream::
      eos () const
      {
        return xdr_getpos (&xdr_) >= buffer_->size ();
      }
    }
  }
}
