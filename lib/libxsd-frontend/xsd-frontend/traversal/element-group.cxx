// file      : xsd-frontend/traversal/element-group.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/traversal/element-group.hxx>

namespace XSDFrontend
{
  namespace Traversal
  {
    Void ElementGroup::
    traverse (Type& g)
    {
      pre (g);
      names (g);
      contains_compositor (g);
      post (g);
    }

    Void ElementGroup::
    pre (Type&)
    {
    }

    Void ElementGroup::
    contains_compositor (Type& g, EdgeDispatcherBase& d)
    {
      d.dispatch (g.contains_compositor ());
    }

    Void ElementGroup::
    contains_compositor (Type& g)
    {
      contains_compositor (g, *this);
    }

    Void ElementGroup::
    post (Type&)
    {
    }
  }
}
