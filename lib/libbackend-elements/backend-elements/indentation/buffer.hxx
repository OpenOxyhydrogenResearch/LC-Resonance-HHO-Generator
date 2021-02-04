// file      : backend-elements/indentation/buffer.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef BACKEND_ELEMENTS_INDENTATION_BUFFER_HXX
#define BACKEND_ELEMENTS_INDENTATION_BUFFER_HXX

#include <backend-elements/types.hxx>

#include <string>

namespace BackendElements
{
  namespace Indentation
  {
    template <typename C>
    class Buffer: public NonCopyable
    {
    public:
      struct Write {};

    public:
      virtual
      ~Buffer ()
      {
      }

    public:
      typedef
      std::char_traits<C>
      Traits;

      typedef
      typename Traits::char_type
      AsChar;

      typedef
      typename Traits::int_type
      AsInt;

    public:
      virtual AsInt
      put (AsChar c) = 0;

      // Unbuffer flushes internal formatting buffers (if any).
      // Note that unbuffer is not exactly flushing since it can
      // result in formatting errors and in general can not be
      // called at arbitrary points. Natural use case would be
      // to call unbuffer at the end of the stream when no more
      // data is expected.
      //
      virtual Void
      unbuffer () = 0;
    };
  }
}

#include <backend-elements/indentation/buffer.txx>

#endif  // BACKEND_ELEMENTS_INDENTATION_BUFFER_HXX
