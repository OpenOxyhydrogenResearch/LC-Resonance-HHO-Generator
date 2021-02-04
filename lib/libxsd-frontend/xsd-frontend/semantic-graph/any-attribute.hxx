// file      : xsd-frontend/semantic-graph/any-attribute.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_SEMANTIC_GRAPH_ANY_ATTRIBUTE_HXX
#define XSD_FRONTEND_SEMANTIC_GRAPH_ANY_ATTRIBUTE_HXX

#include <cult/containers/vector.hxx>

#include <xsd-frontend/semantic-graph/elements.hxx>
#include <xsd-frontend/semantic-graph/namespace.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    class AnyAttribute: public virtual Nameable
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

      AnyAttribute&
      prototype ()
      {
        assert (prototype_ != 0);
        return *prototype_;
      }

      Void
      prototype (AnyAttribute& a)
      {
        assert (prototype_ == 0);
        prototype_ = &a;
      }

    public:
      Namespace&
      definition_namespace ();

    protected:
      friend class Bits::Graph<Node, Edge>;

      AnyAttribute (Path const& file,
                    UnsignedLong line,
                    UnsignedLong column,
                    WideString const& namespaces);

      AnyAttribute (Path const& file,
                    UnsignedLong line,
                    UnsignedLong column,
                    NamespaceIterator begin,
                    NamespaceIterator end);

    private:
      AnyAttribute* prototype_;
      Namespaces namespaces_;
    };
  }
}

#endif  // XSD_FRONTEND_SEMANTIC_GRAPH_ANY_ATTRIBUTE_HXX
