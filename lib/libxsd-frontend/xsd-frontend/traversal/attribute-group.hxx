// file      : xsd-frontend/traversal/attribute-group.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_TRAVERSAL_ATTRIBUTE_GROUP_HXX
#define XSD_FRONTEND_TRAVERSAL_ATTRIBUTE_GROUP_HXX

#include <xsd-frontend/traversal/elements.hxx>
#include <xsd-frontend/semantic-graph/attribute-group.hxx>

namespace XSDFrontend
{
  namespace Traversal
  {
    struct AttributeGroup: ScopeTemplate<SemanticGraph::AttributeGroup>
    {
      virtual Void
      traverse (Type&);

      virtual Void
      pre (Type&);

      virtual Void
      post (Type&);
    };
  }
}

#endif  // XSD_FRONTEND_TRAVERSAL_ATTRIBUTE_GROUP_HXX
