// file      : xsd-frontend/traversal/element-group.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_TRAVERSAL_ELEMENT_GROUP_HXX
#define XSD_FRONTEND_TRAVERSAL_ELEMENT_GROUP_HXX

#include <xsd-frontend/traversal/elements.hxx>
#include <xsd-frontend/semantic-graph/element-group.hxx>

namespace XSDFrontend
{
  namespace Traversal
  {
    struct ElementGroup: ScopeTemplate<SemanticGraph::ElementGroup>
    {
      virtual Void
      traverse (Type&);

      virtual Void
      pre (Type&);

      virtual Void
      contains_compositor (Type&);

      virtual Void
      contains_compositor (Type&, EdgeDispatcherBase&);

      virtual Void
      post (Type&);
    };
  }
}

#endif  // XSD_FRONTEND_TRAVERSAL_ELEMENT_GROUP_HXX
