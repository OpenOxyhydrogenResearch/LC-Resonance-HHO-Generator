// file      : xsd-frontend/traversal/namespace.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_TRAVERSAL_NAMESPACE_HXX
#define XSD_FRONTEND_TRAVERSAL_NAMESPACE_HXX

#include <xsd-frontend/traversal/elements.hxx>
#include <xsd-frontend/semantic-graph/namespace.hxx>

namespace XSDFrontend
{
  namespace Traversal
  {
    struct Namespace: ScopeTemplate<SemanticGraph::Namespace>
    {
      virtual Void
      traverse (Type& m)
      {
        pre (m);
        name (m);
        names (m);
        post (m);
      }

      virtual Void
      pre (Type&)
      {
      }

      virtual Void
      name (Type&)
      {
      }

      virtual Void
      post (Type&)
      {
      }
    };
  }
}

#endif  // XSD_FRONTEND_TRAVERSAL_NAMESPACE_HXX
