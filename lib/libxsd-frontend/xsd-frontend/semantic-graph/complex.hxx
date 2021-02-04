// file      : xsd-frontend/semantic-graph/complex.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_SEMANTIC_GRAPH_COMPLEX_HXX
#define XSD_FRONTEND_SEMANTIC_GRAPH_COMPLEX_HXX

#include <xsd-frontend/semantic-graph/elements.hxx>
#include <xsd-frontend/semantic-graph/compositors.hxx>

#include <cult/containers/vector.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    class Complex: public virtual Type, public virtual Scope
    {
    public:
      Boolean
      mixed_p () const
      {
        return mixed_;
      }

    public:
      Boolean
      contains_compositor_p ()
      {
        return contains_compositor_ != 0;
      }

      ContainsCompositor&
      contains_compositor ()
      {
        assert (contains_compositor_ != 0);
        return *contains_compositor_;
      }

    public:
      Void
      mixed_p (Boolean m)
      {
        mixed_ = m;
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      Complex (); // Virtual inheritance (Enumeration).
      Complex (Path const& file, UnsignedLong line, UnsignedLong column);

      using Type::add_edge_right;
      using Type::add_edge_left;
      using Scope::add_edge_left;

      Void
      add_edge_left (ContainsCompositor& e)
      {
        contains_compositor_ = &e;
      }

      Void
      remove_edge_left (ContainsCompositor& e)
      {
        assert (contains_compositor_ == &e);
        contains_compositor_ = 0;
      }

    private:
      Boolean mixed_;
      ContainsCompositor* contains_compositor_;
    };
  }
}

#endif  // XSD_FRONTEND_SEMANTIC_GRAPH_COMPLEX_HXX
