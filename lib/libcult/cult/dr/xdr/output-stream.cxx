// file      : cult/dr/xdr/output-stream.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/dr/xdr/output-stream.hxx>

namespace Cult
{
  namespace DR
  {
    namespace XDR
    {
      OutputStream::
      OutputStream (Size hint)
          : buffer_ (new Buffer (hint ? hint : 256))
      {
        xdrmem_create (&xdr_, buffer_->data (), ~(u_int (0)), XDR_ENCODE);
      }


      OutputStream::
      ~OutputStream ()
      {
        xdr_destroy (&xdr_);
      }

      Shptr<Buffer> OutputStream::
      buffer ()
      {
        return buffer_;
      }

      Void OutputStream::
      ensure_space (Size size)
      {
        size += size % 4 ? 4 - size % 4 : 0;

        Size needed (size + xdr_getpos (&xdr_));

        if (needed > buffer_->capacity ())
        {
          Size new_size (buffer_->capacity () * 2);

          if (needed > new_size)
            new_size = needed % 8 ? 8 - new_size % 8 : 0;

          if (buffer_->capacity (new_size))
          {
            xdr_destroy (&xdr_);

            xdrmem_create (&xdr_,
                           buffer_->data () + buffer_->size (),
                           ~(u_int (0)),
                           XDR_ENCODE);
          }
        }
      }

      Void OutputStream::
      update_position (Size position)
      {
        // Align to 4-boundary.
        //
        position += position % 4 ? 4 - position % 4 : 0;

        buffer_->size (buffer_->size () + position);
      }

      OutputStream& OutputStream::
      operator<< (Boolean v)
      {
        ensure_space (4);

        bool_t b (v);

        if (!xdr_bool (&xdr_, &b))
          throw Insertion ();

        update_position (4);
        return *this;
      }

      OutputStream& OutputStream::
      operator<< (Int8 v)
      {
        ensure_space (4);

        if (!xdr_int8_t (&xdr_, &v))
          throw Insertion ();

        update_position (4);

        return *this;
      }

      OutputStream& OutputStream::
      operator<< (UnsignedInt8 v)
      {
        ensure_space (4);

        if (!xdr_uint8_t (&xdr_, &v))
          throw Insertion ();

        update_position (4);

        return *this;
      }

      OutputStream& OutputStream::
      operator<< (Int16 v)
      {
        ensure_space (4);

        if (!xdr_int16_t (&xdr_, &v))
          throw Insertion ();

        update_position (4);

        return *this;
      }

      OutputStream& OutputStream::
      operator<< (UnsignedInt16 v)
      {
        ensure_space (4);

        if (!xdr_uint16_t (&xdr_, &v))
          throw Insertion ();

        update_position (4);

        return *this;
      }

      OutputStream& OutputStream::
      operator<< (Int32 v)
      {
        ensure_space (4);

        if (!xdr_int32_t (&xdr_, &v))
          throw Insertion ();

        update_position (4);

        return *this;
      }

      OutputStream& OutputStream::
      operator<< (UnsignedInt32 v)
      {
        ensure_space (4);

        if (!xdr_uint32_t (&xdr_, &v))
          throw Insertion ();

        update_position (4);

        return *this;
      }

      OutputStream& OutputStream::
      operator<< (Int64 v)
      {
        ensure_space (8);

        if (!xdr_int64_t (&xdr_, (int64_t*)&v))
          throw Insertion ();

        update_position (8);

        return *this;
      }

      OutputStream& OutputStream::
      operator<< (UnsignedInt64 v)
      {
        ensure_space (8);

        if (!xdr_uint64_t (&xdr_, (uint64_t*)&v))
          throw Insertion ();

        update_position (8);

        return *this;
      }

      OutputStream& OutputStream::
      operator<< (String const& v)
      {
        UnsignedInt32 size (v.size ());

        ensure_space (4 + size);

        Char* p (const_cast<Char*>(v.c_str ()));

        if (!xdr_string (&xdr_, &p, size))
          throw Insertion ();

        update_position (4 + size);

        return *this;
      }

      Void OutputStream::
      write (Buffer const& buffer)
      {
        Size size (buffer.size () - buffer.position ());

        ensure_space (size);

        if (!xdr_opaque (
              &xdr_,
              const_cast<Char*> (buffer.data ()) + buffer.position (),
              size))
          throw Insertion ();

        update_position (size);
      }
    }
  }
}
