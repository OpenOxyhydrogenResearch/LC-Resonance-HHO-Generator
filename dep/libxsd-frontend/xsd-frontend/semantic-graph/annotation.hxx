// file      : xsd-frontend/semantic-graph/annotation.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_SEMANTIC_GRAPH_ANNOTATION_HXX
#define XSD_FRONTEND_SEMANTIC_GRAPH_ANNOTATION_HXX

#include <xsd-frontend/semantic-graph/elements.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    //
    //
    class Annotation;

    class Annotates: public virtual Edge
    {
    public:
      Annotation&
      annotation ()
      {
        return *annotation_;
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      Annotates ()
          : annotation_ (0)
      {
      }

      Void
      set_left_node (Annotation& a)
      {
        annotation_ = &a;
      }

      Void
      set_right_node (Node&)
      {
      }

      Void
      set_right_node (Edge&)
      {
      }

    private:
      Annotation* annotation_;
    };

    //
    //
    class Annotation: public virtual Node
    {
    public:
      WideString const&
      documentation () const
      {
        return documentation_;
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      Annotation (Path const& file,
                  UnsignedLong line,
                  UnsignedLong column,
                  WideString const& documentation)
          : Node (file, line, column), documentation_ (documentation)
      {
      }

      Void
      add_edge_left (Annotates&)
      {
      }

    private:
      WideString documentation_;
    };
  }
}

#endif  // XSD_FRONTEND_SEMANTIC_GRAPH_ANNOTATION_HXX
