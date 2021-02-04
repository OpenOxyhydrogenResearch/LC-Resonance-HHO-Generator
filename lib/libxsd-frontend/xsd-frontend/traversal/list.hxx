// file      : xsd-frontend/traversal/list.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_TRAVERSAL_LIST_HXX
#define XSD_FRONTEND_TRAVERSAL_LIST_HXX

#include <xsd-frontend/traversal/elements.hxx>
#include <xsd-frontend/semantic-graph/list.hxx>

namespace XSDFrontend
{
  namespace Traversal
  {
    struct List: Node<SemanticGraph::List>
    {
      virtual Void
      traverse (Type&);

      virtual Void
      pre (Type&);

      virtual Void
      argumented (Type&);

      virtual Void
      argumented (Type&, EdgeDispatcherBase& d);

      virtual Void
      name (Type&);

      virtual Void
      post (Type&);
    };
  }
}

#endif  // XSD_FRONTEND_TRAVERSAL_LIST_HXX
