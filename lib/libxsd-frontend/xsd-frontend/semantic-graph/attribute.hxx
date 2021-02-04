// file      : xsd-frontend/semantic-graph/attribute.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_SEMANTIC_GRAPH_ATTRIBUTE_HXX
#define XSD_FRONTEND_SEMANTIC_GRAPH_ATTRIBUTE_HXX

#include <xsd-frontend/semantic-graph/elements.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    class Attribute: public virtual Member
    {
    public:
      Boolean
      optional_p () const
      {
        return optional_;
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      Attribute (Path const& file,
                 UnsignedLong line,
                 UnsignedLong column,
                 Boolean optional,
                 Boolean global,
                 Boolean qualified);
    private:
      Boolean optional_;
    };
  }
}

#endif  // XSD_FRONTEND_SEMANTIC_GRAPH_ATTRIBUTE_HXX
