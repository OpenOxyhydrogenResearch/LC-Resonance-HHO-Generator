// file      : xsd-frontend/semantic-graph/element.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_SEMANTIC_GRAPH_ELEMENT_HXX
#define XSD_FRONTEND_SEMANTIC_GRAPH_ELEMENT_HXX

#include <xsd-frontend/semantic-graph/elements.hxx>
#include <xsd-frontend/semantic-graph/particle.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    class Element;

    class Substitutes: public virtual Edge
    {
    public:
      Element&
      substitution () const
      {
        return *substitution_;
      }

      Element&
      root () const
      {
        return *root_;
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      Substitutes ()
      {
      }

      Void
      set_left_node (Element& n)
      {
        substitution_ = &n;
      }

      Void
      set_right_node (Element& n)
      {
        root_ = &n;
      }

    private:
      Element* root_;
      Element* substitution_;
    };


    class Element: public virtual Member,
                   public virtual Particle
    {
    public:
      Boolean
      substitutes_p () const
      {
        return substitutes_ != 0;
      }

      Substitutes&
      substitutes () const
      {
        assert (substitutes_ != 0);
        return *substitutes_;
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      Element (Path const& file,
               UnsignedLong line,
               UnsignedLong column,
               Boolean global,
               Boolean qualified);

      Void
      add_edge_left (Substitutes& e)
      {
        substitutes_ = &e;
      }

      Void
      add_edge_right (Substitutes&)
      {
      }

      using Member::add_edge_left;
      using Member::add_edge_right;
      using Particle::add_edge_right;

    private:
      Substitutes* substitutes_;
    };
  }
}

#endif  // XSD_FRONTEND_SEMANTIC_GRAPH_ELEMENT_HXX
