// file      : xsd-frontend/semantic-graph/list.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_SEMANTIC_GRAPH_LIST_HXX
#define XSD_FRONTEND_SEMANTIC_GRAPH_LIST_HXX

#include <xsd-frontend/semantic-graph/elements.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    class List: public virtual Specialization
    {
    protected:
      friend class Bits::Graph<Node, Edge>;

      List (Path const& file, UnsignedLong line, UnsignedLong column);
    };
  }
}

#endif  // XSD_FRONTEND_SEMANTIC_GRAPH_LIST_HXX
