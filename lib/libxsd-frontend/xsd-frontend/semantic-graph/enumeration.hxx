// file      : xsd-frontend/semantic-graph/enumeration.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_SEMANTIC_GRAPH_ENUMERATION_HXX
#define XSD_FRONTEND_SEMANTIC_GRAPH_ENUMERATION_HXX

#include <xsd-frontend/semantic-graph/elements.hxx>
#include <xsd-frontend/semantic-graph/complex.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    class Enumeration: public virtual Complex
    {
    protected:
      friend class Bits::Graph<Node, Edge>;

      Enumeration (Path const& file, UnsignedLong line, UnsignedLong column);
    };


    class Enumerator: public virtual Instance
    {
    protected:
      friend class Bits::Graph<Node, Edge>;

      Enumerator (Path const& file, UnsignedLong line, UnsignedLong column);
    };
  }
}

#endif  // XSD_FRONTEND_SEMANTIC_GRAPH_ENUMERATION_HXX
