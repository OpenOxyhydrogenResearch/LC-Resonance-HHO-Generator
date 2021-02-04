// file      : xsd-frontend/semantic-graph/attribute-group.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_SEMANTIC_GRAPH_ATTRIBUTE_GROUP_HXX
#define XSD_FRONTEND_SEMANTIC_GRAPH_ATTRIBUTE_GROUP_HXX

#include <xsd-frontend/semantic-graph/elements.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    class AttributeGroup: public virtual Scope
    {
    protected:
      friend class Bits::Graph<Node, Edge>;

      AttributeGroup (Path const& file,
                      UnsignedLong line,
                      UnsignedLong column);
    };
  }
}

#endif  // XSD_FRONTEND_SEMANTIC_GRAPH_ATTRIBUTE_GROUP_HXX
