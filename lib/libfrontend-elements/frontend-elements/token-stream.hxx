// file      : frontend-elements/token-stream.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef FRONTEND_ELEMENTS_TOKEN_STREAM_HXX
#define FRONTEND_ELEMENTS_TOKEN_STREAM_HXX

#include <frontend-elements/types.hxx>

#include <string>   // std::char_traits
#include <istream>

namespace FrontendElements
{
  //
  //
  template <typename Token>
  class TokenStream
  {
  public:
    virtual
    ~TokenStream ()
    {
    }

  public:
    virtual Token
    next () = 0;
  };


  //
  //
  template <>
  class TokenStream<Char>
  {
  public:
    typedef
    std::char_traits<FrontendElements::Char>
    Traits;

    typedef
    Traits::int_type
    AsInt;

    typedef
    Traits::char_type
    AsChar;

  public:
    virtual
    ~TokenStream ()
    {
    }

  public:
    virtual AsInt
    next () = 0;

    static AsChar
    to_char (AsInt i)
    {
      return Traits::to_char_type (i);
    }

    static AsInt
    eos ()
    {
      return Traits::eof ();
    }
  };

  class InputStreamAdapter: public TokenStream<Char>
  {
  public:
    virtual
    ~InputStreamAdapter ()
    {
    }

    InputStreamAdapter (std::istream& is)
        : is_ (is)
    {
    }

  public:
    virtual AsInt
    next ()
    {
      return is_.get ();
    }

  private:
    std::istream& is_;
  };
}

#endif  // FRONTEND_ELEMENTS_TOKEN_STREAM_HXX
