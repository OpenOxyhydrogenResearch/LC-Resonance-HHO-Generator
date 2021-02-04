// file      : xsd-frontend/traversal/element.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/traversal/element.hxx>

namespace XSDFrontend
{
  namespace Traversal
  {
    Void Element::
    traverse (Type& m)
    {
      pre (m);
      belongs (m);
      name (m);
      post (m);
    }

    Void Element::
    pre (Type&)
    {
    }

    Void Element::
    belongs (Type& m, EdgeDispatcherBase& d)
    {
      d.dispatch (m.belongs ());
    }

    Void Element::
    belongs (Type& m)
    {
      belongs (m, edge_traverser ());
    }

    Void Element::
    name (Type&)
    {
    }

    Void Element::
    post (Type&)
    {
    }
  }
}
