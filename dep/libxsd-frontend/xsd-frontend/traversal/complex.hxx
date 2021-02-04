// file      : xsd-frontend/traversal/complex.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_TRAVERSAL_COMPLEX_HXX
#define XSD_FRONTEND_TRAVERSAL_COMPLEX_HXX

#include <xsd-frontend/traversal/elements.hxx>
#include <xsd-frontend/semantic-graph/complex.hxx>

namespace XSDFrontend
{
  namespace Traversal
  {
    struct Complex : ScopeTemplate<SemanticGraph::Complex>
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
      contains_compositor (Type&);

      Void
      contains_compositor (Type&, EdgeDispatcherBase&);

      virtual Void
      post (Type&);
    };
  }
}

#endif  // XSD_FRONTEND_TRAVERSAL_COMPLEX_HXX
