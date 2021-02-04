// file      : xsd-frontend/traversal/compositors.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_TRAVERSAL_COMPOSITORS_HXX
#define XSD_FRONTEND_TRAVERSAL_COMPOSITORS_HXX

#include <xsd-frontend/traversal/elements.hxx>
#include <xsd-frontend/semantic-graph/compositors.hxx>

namespace XSDFrontend
{
  namespace Traversal
  {
    //
    //
    struct ContainsParticle: Edge<SemanticGraph::ContainsParticle>
    {
      ContainsParticle ()
      {
      }

      ContainsParticle (NodeBase& n)
      {
        node_traverser (n);
      }

      virtual Void
      traverse (Type&);
    };


    //
    //
    struct ContainsCompositor: Edge<SemanticGraph::ContainsCompositor>
    {
      ContainsCompositor ()
      {
      }

      ContainsCompositor (NodeBase& n)
      {
        node_traverser (n);
      }

      virtual Void
      traverse (Type&);
    };

    //
    //
    struct Compositor : Node<SemanticGraph::Compositor>
    {
      virtual Void
      traverse (Type&);

      virtual Void
      pre (Type&);

      virtual Void
      contains (Type&);

      virtual Void
      contains (Type&, EdgeDispatcherBase&);

      virtual Void
      post (Type&);
    };


    //
    //
    struct All : Node<SemanticGraph::All>
    {
      virtual Void
      traverse (Type&);

      virtual Void
      pre (Type&);

      virtual Void
      contains (Type&);

      virtual Void
      contains (Type&, EdgeDispatcherBase&);

      virtual Void
      post (Type&);
    };


    //
    //
    struct Choice : Node<SemanticGraph::Choice>
    {
      virtual Void
      traverse (Type&);

      virtual Void
      pre (Type&);

      virtual Void
      contains (Type&);

      virtual Void
      contains (Type&, EdgeDispatcherBase&);

      virtual Void
      post (Type&);
    };


    //
    //
    struct Sequence : Node<SemanticGraph::Sequence>
    {
      virtual Void
      traverse (Type&);

      virtual Void
      pre (Type&);

      virtual Void
      contains (Type&);

      virtual Void
      contains (Type&, EdgeDispatcherBase&);

      virtual Void
      post (Type&);
    };
  }
}

#endif  // XSD_FRONTEND_TRAVERSAL_COMPOSITORS_HXX
