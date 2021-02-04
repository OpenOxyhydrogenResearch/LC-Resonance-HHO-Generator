// file      : xsd-frontend/semantic-graph/schema.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_SEMANTIC_GRAPH_SCHEMA_HXX
#define XSD_FRONTEND_SEMANTIC_GRAPH_SCHEMA_HXX

#include <cult/containers/set.hxx>

#include <xsd-frontend/semantic-graph/elements.hxx>
#include <xsd-frontend/semantic-graph/namespace.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    //
    //
    class Schema;


    class Uses: public virtual Edge
    {
    public:
      Schema&
      user () const
      {
        return *user_;
      }

      Schema&
      schema () const
      {
        return *schema_;
      }

      Path
      path () const
      {
        return path_;
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      Uses (Path const& path)
          : path_ (path)
      {
      }

      Void
      set_left_node (Schema& s)
      {
        user_ = &s;
      }

      Void
      set_right_node (Schema& s)
      {
        schema_ = &s;
      }

    private:
      Path path_;
      Schema* user_;
      Schema* schema_;
    };


    //
    //
    class Implies: public virtual Uses
    {
    protected:
      friend class Bits::Graph<Node, Edge>;

      Implies (Path const& path)
          : Uses (path)
      {
      }
    };


    //
    //
    class Sources: public virtual Uses
    {
    protected:
      friend class Bits::Graph<Node, Edge>;

      Sources (Path const& path)
          : Uses (path)
      {
      }
    };


    //
    //
    class Includes: public virtual Uses
    {
    protected:
      friend class Bits::Graph<Node, Edge>;

      Includes (Path const& path)
          : Uses (path)
      {
      }
    };


    //
    //
    class Imports: public virtual Uses
    {
    protected:
      friend class Bits::Graph<Node, Edge>;

      Imports (Path const& path)
          : Uses (path)
      {
      }
    };


    //
    //
    class Schema: public virtual Scope,
                  private Bits::Graph<Node, Edge>,
                  public NonCopyable
    {
      typedef
      Cult::Containers::Vector<Uses*>
      UsesList;

      typedef
      Cult::Containers::Vector<Uses*>
      UsedList;

    public:
      Schema (Path const& file, UnsignedLong line, UnsignedLong column)
          : SemanticGraph::Node (file, line, column)
      {
      }

    public:
      typedef
      Bits::PointerIterator<UsesList::ConstIterator>
      UsesIterator;

      UsesIterator
      uses_begin () const
      {
        return uses_.begin ();
      }

      UsesIterator
      uses_end () const
      {
        return uses_.end ();
      }

      typedef
      Bits::PointerIterator<UsedList::ConstIterator>
      UsedIterator;

      UsedIterator
      used_begin () const
      {
        return used_.begin ();
      }

      UsedIterator
      used_end () const
      {
        return used_.end ();
      }

      Boolean
      used_p () const
      {
        return used_begin () != used_end ();
      }

      virtual NamesIteratorPair
      find (Name const& name) const;

    public:
      using Bits::Graph<SemanticGraph::Node, Edge>::new_edge;
      using Bits::Graph<SemanticGraph::Node, Edge>::reset_left_node;
      using Bits::Graph<SemanticGraph::Node, Edge>::reset_right_node;
      using Bits::Graph<SemanticGraph::Node, Edge>::add_edge_left;
      using Bits::Graph<SemanticGraph::Node, Edge>::add_edge_right;
      using Bits::Graph<SemanticGraph::Node, Edge>::delete_node;
      using Bits::Graph<SemanticGraph::Node, Edge>::delete_edge;

      template <typename T>
      T&
      new_node (Path const& file, UnsignedLong line, UnsignedLong column)
      {
        return graph ().new_node<T> (file, line, column);
      }

      template <typename T, typename A0>
      T&
      new_node (Path const& file, UnsignedLong line, UnsignedLong column,
                A0 const& a0)
      {
        return graph ().new_node<T> (file, line, column, a0);
      }

      template <typename T, typename A0, typename A1>
      T&
      new_node (Path const& file, UnsignedLong line, UnsignedLong column,
                A0 const& a0, A1 const& a1)
      {
        return graph ().new_node<T> (file, line, column, a0, a1);
      }

      template <typename T, typename A0, typename A1, typename A2>
      T&
      new_node (Path const& file, UnsignedLong line, UnsignedLong column,
                A0 const& a0, A1 const& a1, A2 const& a2)
      {
        return graph ().new_node<T> (file, line, column, a0, a1, a2);
      }

      template <typename T, typename A0, typename A1, typename A2,
                typename A3>
      T&
      new_node (Path const& file, UnsignedLong line, UnsignedLong column,
                A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3)
      {
        return graph ().new_node<T> (file, line, column, a0, a1, a2, a3);
      }

    protected:
      //@@ gcc bug #21146
      //
      friend class Bits::Graph<SemanticGraph::Node, Edge>;

      using Scope::add_edge_left;
      using Node::add_edge_right;

      Void
      add_edge_left (Uses& e)
      {
        uses_.push_back (&e);
      }

      Void
      add_edge_right (Uses& e)
      {
        used_.push_back (&e);
      }

    private:
      Bits::Graph<SemanticGraph::Node, Edge>&
      graph ()
      {
        return *this;
      }

    private:
      UsesList uses_;
      UsedList used_;

    private:
      typedef Cult::Containers::Set<Schema const*> SchemaSet;

      Void
      find_ (Name const& name, NamesList&, SchemaSet&) const;

      mutable NamesList names_;
      mutable SchemaSet schemas_;
    };
  }
}

#endif  // XSD_FRONTEND_SEMANTIC_GRAPH_SCHEMA_HXX
