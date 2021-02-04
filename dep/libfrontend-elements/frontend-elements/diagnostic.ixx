// file      : frontend-elements/diagnostic.ixx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace FrontendElements
{
  namespace Diagnostic
  {
    namespace Bits
    {
      inline
      Mediator::
      ~Mediator ()
      {
        s_ << r_;
      }
    }
  }
}

