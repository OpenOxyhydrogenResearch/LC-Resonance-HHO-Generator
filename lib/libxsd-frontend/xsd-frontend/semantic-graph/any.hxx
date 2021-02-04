// file      : xsd-frontend/semantic-graph/any.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_SEMANTIC_GRAPH_ANY_HXX
#define XSD_FRONTEND_SEMANTIC_GRAPH_ANY_HXX

#include <cult/containers/vector.hxx>

#include <xsd-frontend/semantic-graph/elements.hxx>
#include <xsd-frontend/semantic-graph/particle.hxx>
#include <xsd-frontend/semantic-graph/namespace.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    class Any: public virtual Nameable,
               public virtual Particle
    {
      typedef
      Cult::Containers::Vector<WideString>
      Namespaces;

    public:
      typedef Namespaces::ConstIterator NamespaceIterator;

      NamespaceIterator
      namespace_begin () const
      {
        return namespaces_.begin ();
      }

      NamespaceIterator
      namespace_end () const
      {
        return namespaces_.end ();
      }

    public:
      Boolean
      prototype_p ()
      {
        return prototype_ != 0;
      }

      Any&
      prototype ()
      {
        assert (prototype_ != 0);
        return *prototype_;
      }

      Void
      prototype (Any& a)
      {
        assert (prototype_ == 0);
        prototype_ = &a;
      }

    public:
      Namespace&
      definition_namespace ();

    protected:
      friend class Bits::Graph<Node, Edge>;

      Any (Path const& file,
           UnsignedLong line,
           UnsignedLong column,
           WideString const& namespaces);

      Any (Path const& file,
           UnsignedLong line,
           UnsignedLong column,
           NamespaceIterator begin,
           NamespaceIterator end);

      using Nameable::add_edge_right;
      using Particle::add_edge_right;

    private:
      Any* prototype_;
      Namespaces namespaces_;
    };
  }
}

#endif  // XSD_FRONTEND_SEMANTIC_GRAPH_ANY_HXX
