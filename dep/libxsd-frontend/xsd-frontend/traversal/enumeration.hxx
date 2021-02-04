// file      : xsd-frontend/traversal/enumeration.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_TRAVERSAL_ENUMERATION_HXX
#define XSD_FRONTEND_TRAVERSAL_ENUMERATION_HXX

#include <xsd-frontend/traversal/elements.hxx>
#include <xsd-frontend/semantic-graph/enumeration.hxx>

namespace XSDFrontend
{
  namespace Traversal
  {
    struct Enumeration : ScopeTemplate<SemanticGraph::Enumeration>
    {
      virtual Void
      traverse (Type&);

      virtual Void
      pre (Type&);

      virtual Void
      name (Type&);

      virtual Void
      inherits (Type&);

      Void
      inherits (Type&, EdgeDispatcherBase&);

      virtual Void
      post (Type&);
    };

    struct Enumerator : Node<SemanticGraph::Enumerator>
    {
      virtual Void
      traverse (Type&);

      virtual Void
      pre (Type&);

      virtual Void
      belongs (Type&, EdgeDispatcherBase&);

      virtual Void
      belongs (Type&);

      virtual Void
      name (Type&);

      virtual Void
      post (Type&);
    };
  }
}

#endif  // XSD_FRONTEND_TRAVERSAL_ENUMERATION_HXX
