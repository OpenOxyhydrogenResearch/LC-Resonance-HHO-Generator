// file      : backend-elements/indentation/clip.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef BACKEND_ELEMENTS_INDENTATION_CLIP_HXX
#define BACKEND_ELEMENTS_INDENTATION_CLIP_HXX

#include <backend-elements/types.hxx>

#include <backend-elements/indentation/buffer.hxx>

#include <ostream>

namespace BackendElements
{
  namespace Indentation
  {
    template <typename C>
    class ToStreambufAdapter: public std::basic_streambuf<C>,
                              public NonCopyable
    {
    public:
      typedef
      typename std::basic_streambuf<C>::traits_type
      Traits;

      typedef
      typename std::basic_streambuf<C>::char_type
      AsChar;

      typedef
      typename std::basic_streambuf<C>::int_type
      AsInt;

    public:
      ToStreambufAdapter (Buffer<C>& buffer)
          : buffer_ (buffer)
      {
      }

      virtual AsInt
      overflow (AsInt ch)
      {
        return buffer_.put (Traits::to_char_type (ch));
      }

      virtual Int
      sync ()
      {
        return 0;
      }

    private:
      Buffer<C>& buffer_;
    };


    template <typename C>
    class FromStreambufAdapter: public Buffer<C>
    {
    public:
      typedef
      typename Buffer<C>::Traits
      Traits;

      typedef
      typename Buffer<C>::AsChar
      AsChar;

      typedef
      typename Buffer<C>::AsInt
      AsInt;

      typedef
      typename Buffer<C>::Write
      Write;

    public:
      FromStreambufAdapter (std::basic_streambuf<C>& b)
          : buffer_ (b)
      {
      }

      virtual AsInt
      put (AsChar ch)
      {
        return buffer_.sputc (ch);
      }

      virtual Void
      unbuffer ()
      {
        try
        {
          if (buffer_.pubsync () == 0) return;
        }
        catch (std::ios_base::failure const&)
        {
        }

        throw Write ();
      }

    private:
      std::basic_streambuf<C>& buffer_;
    };


    template <template <typename> class Buffer, typename C = Char>
    class Clip: public NonCopyable
    {
    public:
      Clip (std::basic_ostream<C>& os)
          : os_ (os),
            prev_ (os_.rdbuf ()),
            from_adapter_ (*prev_),
            buffer_ (from_adapter_),
            to_adapter_ (buffer_)
      {
        os_.rdbuf (&to_adapter_);
      }

      /*
      template <typename Arg0>
      Clip (std::basic_ostream<C>& os, Arg0 a0)
          : os_ (os),
            prev_ (os_.rdbuf ()),
            from_adapter_ (*prev_),
            buffer_ (from_adapter_, a0),
            to_adapter_ (buffer_)
      {
        os_.rdbuf (&to_adapter_);
      }
      */

      ~Clip ()
      {
        try
        {
          buffer_.unbuffer ();
        }
        catch (...)
        {
          os_.rdbuf (prev_);
          throw;
        }

        os_.rdbuf (prev_);
      }

      Buffer<C>&
      buffer ()
      {
        return buffer_;
      }

    private:
      std::basic_ostream<C>& os_;
      std::basic_streambuf<C>* prev_;

      FromStreambufAdapter<C> from_adapter_;

      Buffer<C> buffer_;

      ToStreambufAdapter<C> to_adapter_;
    };
  }
}

#include <backend-elements/indentation/clip.txx>

#endif  // BACKEND_ELEMENTS_INDENTATION_CLIP_HXX
