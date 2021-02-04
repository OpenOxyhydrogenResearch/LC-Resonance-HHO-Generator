// file      : xsd-frontend/traversal/attribute.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/traversal/attribute.hxx>

namespace XSDFrontend
{
  namespace Traversal
  {
    Void Attribute::
    traverse (Type& a)
    {
      pre (a);
      belongs (a);
      name (a);
      post (a);
    }

    Void Attribute::
    pre (Type&)
    {
    }

    Void Attribute::
    belongs (Type& a, EdgeDispatcherBase& d)
    {
      d.dispatch (a.belongs ());
    }

    Void Attribute::
    belongs (Type& a)
    {
      belongs (a, *this);
    }

    Void Attribute::
    name (Type&)
    {
    }

    Void Attribute::
    post (Type&)
    {
    }
  }
}
