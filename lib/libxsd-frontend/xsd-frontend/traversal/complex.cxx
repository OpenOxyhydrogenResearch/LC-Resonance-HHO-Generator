// file      : xsd-frontend/traversal/complex.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/traversal/complex.hxx>

namespace XSDFrontend
{
  namespace Traversal
  {
    Void Complex::
    traverse (Type& c)
    {
      pre (c);
      name (c);
      inherits (c);
      names (c);
      contains_compositor (c);
      post (c);
    }

    Void Complex::
    pre (Type&)
    {
    }

    Void Complex::
    name (Type&)
    {
    }

    Void Complex::
    inherits (Type& c)
    {
      inherits (c, *this);
    }

    Void Complex::
    inherits (Type& c, EdgeDispatcherBase& d)
    {
      if (c.inherits_p ())
        d.dispatch (c.inherits ());
    }

    Void Complex::
    contains_compositor (Type& c)
    {
      contains_compositor (c, *this);
    }

    Void Complex::
    contains_compositor (Type& c, EdgeDispatcherBase& d)
    {
      if (c.contains_compositor_p ())
        d.dispatch (c.contains_compositor ());
    }

    Void Complex::
    post (Type&)
    {
    }
  }
}
