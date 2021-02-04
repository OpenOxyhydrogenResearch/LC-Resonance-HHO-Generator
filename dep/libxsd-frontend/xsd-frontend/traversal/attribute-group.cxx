// file      : xsd-frontend/traversal/attribute-group.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/traversal/attribute-group.hxx>

namespace XSDFrontend
{
  namespace Traversal
  {
    Void AttributeGroup::
    traverse (Type& g)
    {
      pre (g);
      names (g);
      post (g);
    }

    Void AttributeGroup::
    pre (Type&)
    {
    }

    Void AttributeGroup::
    post (Type&)
    {
    }
  }
}
