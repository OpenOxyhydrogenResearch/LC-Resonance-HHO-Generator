// file      : xsd-frontend/semantic-graph/union.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_SEMANTIC_GRAPH_UNION_HXX
#define XSD_FRONTEND_SEMANTIC_GRAPH_UNION_HXX

#include <xsd-frontend/semantic-graph/elements.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    class Union: public virtual Specialization
    {
    protected:
      friend class Bits::Graph<Node, Edge>;

      Union (Path const& file, UnsignedLong line, UnsignedLong column);
    };
  }
}

#endif  // XSD_FRONTEND_SEMANTIC_GRAPH_UNION_HXX
