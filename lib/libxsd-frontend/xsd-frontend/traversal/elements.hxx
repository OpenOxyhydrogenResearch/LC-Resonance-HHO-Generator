// file      : xsd-frontend/traversal/elements.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_TRAVERSAL_ELEMENTS_HXX
#define XSD_FRONTEND_TRAVERSAL_ELEMENTS_HXX

#include <cult/types.hxx>

#include <frontend-elements/traversal.hxx>

#include <xsd-frontend/semantic-graph/elements.hxx>

namespace XSDFrontend
{
  namespace Traversal
  {
    using namespace Cult::Types;

    namespace Bits
    {
      using FrontendElements::Traversal::TraverserBase;
      using FrontendElements::Traversal::Traverser;

      using FrontendElements::Traversal::DispatcherBase;
      using FrontendElements::Traversal::Dispatcher;

    }

    typedef Bits::DispatcherBase<SemanticGraph::Node> NodeDispatcherBase;
    typedef Bits::DispatcherBase<SemanticGraph::Edge> EdgeDispatcherBase;


    //
    //
    struct NodeBase : virtual Bits::Dispatcher<SemanticGraph::Node>,
                      virtual Bits::Dispatcher<SemanticGraph::Edge>
    {
      Void
      edge_traverser (EdgeDispatcherBase& d)
      {
        Bits::Dispatcher<SemanticGraph::Edge>::traverser (d);
      }

      EdgeDispatcherBase&
      edge_traverser ()
      {
        return *this;
      }

    public:
      using Bits::Dispatcher<SemanticGraph::Node>::dispatch;
      using Bits::Dispatcher<SemanticGraph::Edge>::dispatch;

      using Bits::Dispatcher<SemanticGraph::Node>::map;

      using Bits::Dispatcher<SemanticGraph::Edge>::iterate_and_dispatch;
    };


    //
    //
    template <typename T>
    struct Node : Bits::TraverserBase<SemanticGraph::Node>, virtual NodeBase
    {
      typedef
      T
      Type;

      Node ()
      {
        map (typeid (Type), *this);
      }

      virtual Void
      traverse (Type&) = 0;

      virtual Void
      trampoline (SemanticGraph::Node& i)
      {
        traverse (dynamic_cast<Type&> (i));
      }

      virtual Void
      trampoline (SemanticGraph::Node const&)
      {
        abort ();
      }
    };


    //
    //
    struct EdgeBase : virtual Bits::Dispatcher<SemanticGraph::Edge>,
                      virtual Bits::Dispatcher<SemanticGraph::Node>
    {
      Void
      node_traverser (NodeDispatcherBase& d)
      {
        Bits::Dispatcher<SemanticGraph::Node>::traverser (d);
      }

      NodeDispatcherBase&
      node_traverser ()
      {
        return *this;
      }

    public:
      using Bits::Dispatcher<SemanticGraph::Edge>::dispatch;
      using Bits::Dispatcher<SemanticGraph::Node>::dispatch;

      using Bits::Dispatcher<SemanticGraph::Edge>::map;

      using Bits::Dispatcher<SemanticGraph::Node>::iterate_and_dispatch;
    };

    template <typename T>
    struct Edge : Bits::TraverserBase<SemanticGraph::Edge>, virtual EdgeBase
    {
      typedef
      T
      Type;

      Edge ()
      {
        map (typeid (Type), *this);
      }

      virtual Void
      traverse (Type&) = 0;

      virtual Void
      trampoline (SemanticGraph::Edge& i)
      {
        traverse (dynamic_cast<Type&> (i));
      }

      virtual Void
      trampoline (SemanticGraph::Edge const&)
      {
        abort ();
      }
    };

    inline
    EdgeBase&
    operator>> (NodeBase& n, EdgeBase& e)
    {
      n.edge_traverser (e);
      return e;
    }

    inline
    NodeBase&
    operator>> (EdgeBase& e, NodeBase& n)
    {
      e.node_traverser (n);
      return n;
    }

    // Edges
    //

    //
    //
    struct Names : Edge<SemanticGraph::Names>
    {
      Names ()
      {
      }

      Names (NodeBase& n)
      {
        node_traverser (n);
      }

      virtual Void
      traverse (Type& e)
      {
        dispatch (e.named ());
      }
    };


    //
    //
    struct Belongs : Edge<SemanticGraph::Belongs>
    {
      Belongs ()
      {
      }

      Belongs (NodeBase& n)
      {
        node_traverser (n);
      }

      virtual Void
      traverse (Type& e)
      {
        dispatch (e.type ());
      }
    };


    // Nodes
    //


    //
    //
    struct Nameable : Node<SemanticGraph::Nameable>
    {
    };


    //
    //
    template <typename T>
    struct ScopeTemplate : Node<T>
    {
    public:
      virtual Void
      traverse (T& s)
      {
        names (s);
      }

      template<typename X>
      Void
      names (T& s,
             EdgeDispatcherBase& d,
             Void (X::*pre_) (T&) = (Void (ScopeTemplate<T>::*)(T&)) (0),
             Void (X::*post_) (T&) = (Void (ScopeTemplate<T>::*)(T&)) (0),
             Void (X::*none_) (T&) = (Void (ScopeTemplate<T>::*)(T&)) (0),
             Void (X::*next_) (T&) = (Void (ScopeTemplate<T>::*)(T&)) (0))
      {
        X* this_ (dynamic_cast<X*> (this));

        typename T::NamesIterator b (s.names_begin ()), e (s.names_end ());

        if (b != e)
        {
          if (pre_)
            (this_->*pre_) (s);

          //iterate_and_dispatch (b, e, d, *this_, next_, s);

          for (; b != s.names_end ();)
          {
            d.dispatch (*b);

            if (++b != s.names_end () && next_ != 0)
              (this_->*next_) (s);
          }

          if (post_)
            (this_->*post_) (s);
        }
        else
        {
          if (none_)
            (this_->*none_) (s);
        }
      }

      virtual Void
      names (T& s, EdgeDispatcherBase& d)
      {
        names<ScopeTemplate<T> > (s, d);
      }

      virtual Void
      names (T& s)
      {
        names (s,
               *this,
               &ScopeTemplate<T>::names_pre,
               &ScopeTemplate<T>::names_post,
               &ScopeTemplate<T>::names_none,
               &ScopeTemplate<T>::names_next);
      }

      virtual Void
      names_pre (T&)
      {
      }

      virtual Void
      names_next (T&)
      {
      }

      virtual Void
      names_post (T&)
      {
      }

      virtual Void
      names_none (T&)
      {
      }
    };


    //
    //
    typedef
    ScopeTemplate<SemanticGraph::Scope>
    Scope;


    //
    //
    struct Type : Node<SemanticGraph::Type>
    {
      virtual Void
      traverse (SemanticGraph::Type&) = 0;
    };


    //
    //
    struct Instance : Node<SemanticGraph::Instance>
    {
      virtual Void
      traverse (Type&);

      virtual Void
      pre (Type&);

      virtual Void
      belongs (Type&, EdgeDispatcherBase&);

      virtual Void
      belongs (Type&);

      virtual Void
      post (Type&);
    };


    //
    //
    struct Member : Node<SemanticGraph::Member>
    {
      virtual Void
      traverse (Type&);

      virtual Void
      pre (Type&);

      virtual Void
      belongs (Type&, EdgeDispatcherBase&);

      virtual Void
      belongs (Type&);

      virtual Void
      post (Type&);
    };


    //
    //
    struct Inherits : Edge<SemanticGraph::Inherits>
    {
      Inherits ()
      {
      }

      Inherits (NodeBase& n)
      {
        node_traverser (n);
      }

      virtual Void
      traverse (Type& e)
      {
        dispatch (e.base ());
      }
    };


    //
    //
    struct Extends : Edge<SemanticGraph::Extends>
    {
      Extends ()
      {
      }

      Extends (NodeBase& n)
      {
        node_traverser (n);
      }

      virtual Void
      traverse (Type& e)
      {
        dispatch (e.base ());
      }
    };


    //
    //
    struct Restricts : Edge<SemanticGraph::Restricts>
    {
      Restricts ()
      {
      }

      Restricts (NodeBase& n)
      {
        node_traverser (n);
      }

      virtual Void
      traverse (Type& e)
      {
        dispatch (e.base ());
      }
    };


    //
    //
    struct Argumented : Edge<SemanticGraph::Arguments>
    {
      Argumented ()
      {
      }

      Argumented (NodeBase& n)
      {
        node_traverser (n);
      }

      virtual Void
      traverse (Type& a)
      {
        dispatch (a.type ());
      }
    };


    /*
    //
    //
    struct Contains : Edge<SemanticGraph::Contains>
    {
      virtual Void
      traverse (Type& e)
      {
        dispatch (e.element ());
      }
    };
    */

    //
    //
    typedef
    Node<SemanticGraph::AnyType>
    AnyType;


    //
    //
    typedef
    Node<SemanticGraph::AnySimpleType>
    AnySimpleType;
  }
}

#include <xsd-frontend/traversal/elements.txx>

#endif  // XSD_FRONTEND_TRAVERSAL_ELEMENTS_HXX
