// file      : xsd-frontend/semantic-graph/elements.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_SEMANTIC_GRAPH_ELEMENTS_HXX
#define XSD_FRONTEND_SEMANTIC_GRAPH_ELEMENTS_HXX

#include <iosfwd>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/exception.hpp>

#include <cult/types.hxx>

#include <cult/rtti/type-info.hxx>

#include <cult/containers/set.hxx>
#include <cult/containers/map.hxx>
#include <cult/containers/list.hxx>
#include <cult/containers/pair.hxx>
#include <cult/containers/graph.hxx>
#include <cult/containers/vector.hxx>

#include <frontend-elements/context.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    using namespace Cult::Types;

    namespace Bits
    {
      using Cult::Containers::Graph;

      //@@ Should end up in Cult::Meta
      //
      template <typename X>
      struct strip_pointer
      {
        typedef X Type;
      };

      template <typename X>
      struct strip_pointer<X*>
      {
        typedef X Type;
      };

      template <typename I>
      struct PointerIterator
      {
        typedef
        typename strip_pointer<typename I::Value>::Type
        Value;

        typedef I BaseIterator;
        typedef Value& Reference;
        typedef Value* Pointer;

        PointerIterator ()
            : i_ () // i_ can be of a pointer type.
        {
        }

        PointerIterator (I const& i)
            : i_ (i)
        {
        }

      public:
        Reference
        operator* () const
        {
          return **i_;
        }

        Pointer
        operator-> () const
        {
          return *i_;
        }

        I const&
        base () const
        {
          return i_;
        }

      public:
        PointerIterator&
        operator++ ()
        {
          ++i_;
          return *this;
        }

        PointerIterator
        operator++ (Int)
        {
          PointerIterator r (*this);
          ++i_;
          return r;
        }

        PointerIterator&
        operator-- ()
        {
          --i_;
          return *this;
        }

        PointerIterator
        operator-- (Int)
        {
          PointerIterator r (*this);
          --i_;
          return r;
        }

      private:
        I i_;
      };

      template <typename I>
      inline
      Boolean
      operator== (PointerIterator<I> const& a, PointerIterator<I> const& b)
      {
        return a.base () == b.base ();
      }

      template <typename I>
      inline
      Boolean
      operator!= (PointerIterator<I> const& a, PointerIterator<I> const& b)
      {
        return a.base () != b.base ();
      }

      template <typename I>
      inline
      typename PointerIterator<I>::BaseIterator::difference_type
      operator- (PointerIterator<I> const& a, PointerIterator<I> const& b)
      {
        return a.base () - b.base ();
      }
    }

    //
    //
    typedef
    boost::filesystem::filesystem_error
    InvalidPath;

    typedef
    boost::filesystem::path
    Path;

    typedef
    Cult::Containers::Vector<Path>
    Paths;

    typedef
    FrontendElements::Context
    Context;

    //
    //
    class Node;
    class Edge;

    //
    //
    class Annotates;
    class Annotation;

    //
    //
    class Edge
    {
    public:
      Context&
      context () const
      {
        return context_;
      }

      virtual
      ~Edge ()
      {
      }

    public:
      template <typename X>
      Boolean
      is_a () const
      {
        return dynamic_cast<X const*> (this) != 0;
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      Edge ()
      {
      }

    private:
      mutable Context context_;
    };

    inline Boolean
    operator== (Edge const& x, Edge const& y)
    {
      return &x == &y;
    }


    //
    //
    class Node
    {
    public:
      Context&
      context () const
      {
        return context_;
      }

    public:
      Path const&
      file () const
      {
        return file_;
      }

      UnsignedLong
      line () const
      {
        return line_;
      }

      UnsignedLong
      column () const
      {
        return column_;
      }

    public:
      Boolean
      annotated_p () const
      {
        return annotates_ != 0;
      }

      Annotates&
      annotated () const
      {
        return *annotates_;
      }

      Annotation&
      annotation ();

    public:
      template <typename X>
      Boolean
      is_a () const
      {
        return dynamic_cast<X const*> (this) != 0;
      }

    public:

      virtual
      ~Node ()
      {
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      Node (Path const& file, UnsignedLong line, UnsignedLong column)
          : annotates_ (0), file_ (file), line_ (line), column_ (column)
      {
      }

      Node () // For virtual inheritance.
      {
        abort (); // Told you so!
      }

      Void
      add_edge_right (Annotates& a)
      {
        annotates_ = &a;
      }

    private:
      mutable Context context_;
      Annotates* annotates_;
      Path file_;
      UnsignedLong line_;
      UnsignedLong column_;
    };

    inline Boolean
    operator== (Node const& x, Node const& y)
    {
      return &x == &y;
    }


    //
    //
    typedef WideString Name;


    //
    //
    class Scope;
    class Nameable;


    //
    //
    class Names: public virtual Edge
    {
    public:
      Name
      name () const
      {
        return name_;
      }

      Scope&
      scope () const
      {
        return *scope_;
      }

      Nameable&
      named () const
      {
        return *named_;
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      Names (Name const& name)
          : name_ (name)
      {
      }

      Void
      set_left_node (Scope& n)
      {
        scope_ = &n;
      }

      Void
      set_right_node (Nameable& n)
      {
        named_ = &n;
      }

      Void
      clear_left_node (Scope& n)
      {
        assert (scope_ == &n);
        scope_ = 0;
      }

      Void
      clear_right_node (Nameable& n)
      {
        assert (named_ == &n);
        named_ = 0;
      }

    private:
      Scope* scope_;
      Nameable* named_;
      Name name_;
    };


    class Nameable: public virtual Node
    {
    public:
      Boolean
      named_p () const
      {
        return named_ != 0;
      }

      Name
      name () const
      {
        assert (named_p ());
        return named_->name ();
      }

      Scope&
      scope ()
      {
        assert (named_p ());
        return named_->scope ();
      }

      Names&
      named ()
      {
        assert (named_p ());
        return *named_;
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      Nameable ()
          : named_ (0)
      {
      }

      Void
      add_edge_right (Names& e)
      {
        named_ = &e;
      }

      Void
      remove_edge_right (Names& e)
      {
        assert (named_ == &e);
        named_ = 0;
      }

      using Node::add_edge_right;

    private:
      Names* named_;
    };


    //
    //
    typedef
    Cult::Containers::Set<Nameable*>
    Nameables;


    //
    //
    class Scope: public virtual Nameable
    {
    protected:
      typedef
      Cult::Containers::List<Names*>
      NamesList;

      typedef
      Cult::Containers::Map<Names*, NamesList::Iterator>
      ListIteratorMap;

      typedef
      Cult::Containers::Map<Name, NamesList>
      NamesMap;

    public:
      typedef
      Bits::PointerIterator<NamesList::Iterator>
      NamesIterator;

      typedef
      Bits::PointerIterator<NamesList::ConstIterator>
      NamesConstIterator;

      typedef
      Cult::Containers::Pair <NamesConstIterator, NamesConstIterator>
      NamesIteratorPair;

      NamesIterator
      names_begin ()
      {
        return names_.begin ();
      }

      NamesIterator
      names_end ()
      {
        return names_.end ();
      }

      NamesConstIterator
      names_begin () const
      {
        return names_.begin ();
      }

      NamesConstIterator
      names_end () const
      {
        return names_.end ();
      }

      virtual NamesIteratorPair
      find (Name const& name) const
      {
        NamesMap::ConstIterator i (names_map_.find (name));

        if (i == names_map_.end ())
          return NamesIteratorPair (names_.end (), names_.end ());
        else
          return NamesIteratorPair (i->second.begin (), i->second.end ());
      }

      NamesIterator
      find (Names& e)
      {
        ListIteratorMap::Iterator i (iterator_map_.find (&e));
        return i != iterator_map_.end () ? i->second : names_.end ();
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      Scope (Path const& file, UnsignedLong line, UnsignedLong column)
          : Node (file, line, column)
      {
      }

      Scope ()
      {
      }

      Void
      add_edge_left (Names& e)
      {
        NamesList::Iterator i (names_.insert (names_.end (), &e));
        iterator_map_[&e] = i;
        names_map_[e.name ()].push_back (&e);
      }

      Void
      remove_edge_left (Names& e)
      {
        ListIteratorMap::Iterator i (iterator_map_.find (&e));
        assert (i != iterator_map_.end ());

        names_.erase (i->second);
        iterator_map_.erase (i);

        NamesMap::Iterator j (names_map_.find (e.name ()));

        for (NamesList::Iterator i (j->second.begin ());
             i != j->second.end (); ++i)
        {
          if (*i == &e)
            i = j->second.erase (i);
        }
      }

      //@@ Ideally should be protected but then NodeArg has no way to
      //   access it. Maybe when (if) I move NodeArg into Grpah I can
      //   resolve this.
      //
    public:
      Void
      add_edge_left (Names& e, NamesIterator const& after)
      {
        NamesList::Iterator i;

        if (after.base () == names_.end ())
          i = names_.insert (names_.begin (), &e);
        else
        {
          NamesList::Iterator j (after.base ());
          i = names_.insert (++j, &e);
        }

        iterator_map_[&e] = i;
        names_map_[e.name ()].push_back (&e);
      }

    protected:
      using Nameable::add_edge_right;

    private:
      NamesList names_;
      ListIteratorMap iterator_map_;
      NamesMap names_map_;
    };


    //
    //
    class Belongs;
    class Inherits;
    class Arguments;

    class Type: public virtual Nameable
    {
    protected:
      typedef
      Cult::Containers::Vector<Belongs*>
      Classifies;

      typedef
      Cult::Containers::Vector<Inherits*>
      Begets;

      typedef
      Cult::Containers::Set<Arguments*>
      ArgumentsSet;

    public:
      typedef
      Bits::PointerIterator<Classifies::ConstIterator>
      ClassifiesIterator;

      ClassifiesIterator
      classifies_begin () const
      {
        return classifies_.begin ();
      }

      ClassifiesIterator
      classifies_end () const
      {
        return classifies_.end ();
      }

      //
      //
      Boolean
      inherits_p () const
      {
        return inherits_ != 0;
      }

      Inherits&
      inherits () const
      {
        assert (inherits_ != 0);
        return *inherits_;
      }

      //
      //
      typedef
      Bits::PointerIterator<Begets::ConstIterator>
      BegetsIterator;

      BegetsIterator
      begets_begin () const
      {
        return begets_.begin ();
      }

      BegetsIterator
      begets_end () const
      {
        return begets_.end ();
      }

      //
      //
      typedef
      Bits::PointerIterator<ArgumentsSet::ConstIterator>
      ArgumentsIterator;

      ArgumentsIterator
      arguments_begin () const
      {
        return arguments_.begin ();
      }

      ArgumentsIterator
      arguments_end () const
      {
        return arguments_.end ();
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      Type ()
          : inherits_ (0)
      {
      }

      Void
      add_edge_right (Belongs& e)
      {
        classifies_.push_back (&e);
      }

      Void
      add_edge_right (Inherits& e)
      {
        begets_.push_back (&e);
      }

      using Nameable::add_edge_right;

      Void
      add_edge_left (Arguments& a)
      {
        arguments_.insert (&a);
      }

      Void
      remove_edge_left (Arguments&);

      Void
      add_edge_left (Inherits& e)
      {
        inherits_ = &e;
      }

    private:
      Inherits* inherits_;
      Begets begets_;
      Classifies classifies_;
      ArgumentsSet arguments_;
    };


    class Instance: public virtual Nameable
    {
    public:
      Belongs&
      belongs () const
      {
        return *belongs_;
      }

      Type&
      type () const;

      Boolean
      typed_p () const
      {
        return belongs_ != 0;
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      Instance ()
          : belongs_ (0)
      {
      }

      Void
      add_edge_left (Belongs& e)
      {
        belongs_ = &e;
      }

    private:
      Belongs* belongs_;
    };


    class Belongs: public virtual Edge
    {
    public:
      Instance&
      instance () const
      {
        return *instance_;
      }

      Type&
      type () const
      {
        return *type_;
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      Belongs ()
      {
      }

      Void
      set_left_node (Instance& n)
      {
        instance_ = &n;
      }

      Void
      set_right_node (Type& n)
      {
        type_ = &n;
      }

    private:
      Instance* instance_;
      Type* type_;
    };


    //
    //
    class Inherits: public virtual Edge
    {
    public:
      Type&
      base () const
      {
        return *base_;
      }

      Type&
      derived () const
      {
        return *derived_;
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      Inherits ()
      {
      }

      Void
      set_left_node (Type& n)
      {
        derived_ = &n;
      }

      Void
      set_right_node (Type& n)
      {
        base_ = &n;
      }

    private:
      Type* base_;
      Type* derived_;
    };


    class Extends: public virtual Inherits
    {
    protected:
      friend class Bits::Graph<Node, Edge>;

      Extends ()
      {
      }
    };

    class Restricts: public virtual Inherits
    {
    protected:
      typedef
      Cult::Containers::Map<WideString, WideString>
      Facets;

    public:
      typedef
      Facets::Iterator
      FacetIterator;

      Boolean
      facet_empty ()
      {
        return facets_.empty ();
      }

      FacetIterator
      facet_begin ()
      {
        return facets_.begin ();
      }

      FacetIterator
      facet_end ()
      {
        return facets_.end ();
      }

      FacetIterator
      facet_find (WideString const& name)
      {
        return facets_.find (name);
      }

      Void
      facet_insert (String const& name, String const& value)
      {
        facets_[name] = value;
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      Restricts ()
      {
      }

    protected:
      Facets facets_;
    };


    //
    //
    class Member;
    class Namespace;

    class BelongsToNamespace: public virtual Edge
    {
    public:
      Member&
      member () const
      {
        assert (member_ != 0);
        return *member_;
      }

      Namespace&
      namespace_ () const
      {
        assert (namespace__ != 0);
        return *namespace__;
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      BelongsToNamespace ()
          : member_ (0), namespace__ (0)
      {
      }

      Void
      set_left_node (Member& n)
      {
        member_ = &n;
      }

      Void
      set_right_node (Namespace& n)
      {
        namespace__ = &n;
      }

    private:
      Member* member_;
      Namespace* namespace__;
    };

    //
    //
    class Member: public virtual Instance
    {
    public:
      // Member is global either if it is defined outside any type
      // or it is a ref="" of a global member.
      //
      Boolean
      global_p () const
      {
        return global_;
      }

      Boolean
      qualified_p () const
      {
        return qualified_;
      }

      // Note that only qualified members belong to a namespace.
      //
      Namespace&
      namespace_ () const
      {
        assert (belongs_to_namespace_ != 0);
        return belongs_to_namespace_->namespace_ ();
      }


      // Default and fixed value API. Note that the fixed value semantics
      // is a superset of the default value semantics. As such setting the
      // fixed value appears as if the default value was also set.
      //
      Boolean
      default_p () const
      {
        return value_type_ != ValueType::none;
      }

      Boolean
      fixed_p () const
      {
        return value_type_ == ValueType::fixed;
      }

      struct NoValue {};

      WideString
      value () const
      {
        if (value_type_ != ValueType::none)
          return value_;
        else
          throw NoValue ();
      }

      //
      //
      Void
      default_ (WideString const& v)
      {
        value_ = v;
        value_type_ = ValueType::default_;
      }

      Void
      fixed (WideString const& v)
      {
        value_ = v;
        value_type_ = ValueType::fixed;
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      Member (Boolean global, Boolean qualified)
          : global_ (global),
            qualified_ (qualified),
            belongs_to_namespace_ (0),
            value_type_ (ValueType::none)
      {
      }

      Void
      add_edge_left (BelongsToNamespace& e)
      {
        // In the parser we sometimes re-add the same adge.
        //
        belongs_to_namespace_ = &e;
      }

      using Instance::add_edge_left;

    private:
      Boolean global_;
      Boolean qualified_;
      BelongsToNamespace* belongs_to_namespace_;

      struct ValueType
      {
        enum Value
        {
          none,
          default_,
          fixed
        };
      };

      WideString value_;
      ValueType::Value value_type_;
    };


    // Parametric types.
    //

    class Specialization: public virtual Type
    {
      typedef
      Cult::Containers::Vector<Arguments*>
      Argumented;

    public:
      typedef
      Bits::PointerIterator<Argumented::Iterator>
      ArgumentedIterator;

      typedef
      Bits::PointerIterator<Argumented::ConstIterator>
      ArgumentedConstIterator;

      ArgumentedIterator
      argumented_begin ()
      {
        return argumented_.begin ();
      }

      ArgumentedConstIterator
      argumented_begin () const
      {
        return argumented_.begin ();
      }

      ArgumentedIterator
      argumented_end ()
      {
        return argumented_.end ();
      }

      ArgumentedConstIterator
      argumented_end () const
      {
        return argumented_.end ();
      }

      // Shortcut for one-argument specializations.
      //
      Arguments&
      argumented () const
      {
        return *argumented_[0];
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      using Type::add_edge_right;

      Void
      add_edge_right (Arguments& a)
      {
        argumented_.push_back (&a);
      }

      Void
      remove_edge_right (Arguments&);

    public:
      Void
      add_edge_right (Arguments& a, ArgumentedIterator const& pos)
      {
        argumented_.insert (pos.base (), &a);
      }

    private:
      Argumented argumented_;
    };


    class Arguments: public virtual Edge
    {
    public:
      Type&
      type () const
      {
        return *type_;
      }

      Specialization&
      specialization () const
      {
        return *specialization_;
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      void
      set_left_node (Type& n)
      {
        type_ = &n;
      }

      void
      clear_left_node (Type& n)
      {
        assert (type_ == &n);
        type_ = 0;
      }

      void
      set_right_node (Specialization& s)
      {
        specialization_ = &s;
      }

      void
      clear_right_node (Specialization& s)
      {
        assert (specialization_ == &s);
        specialization_ = 0;
      }

    private:
      Type* type_;
      Specialization* specialization_;
    };


    //
    //
    class AnyType: public virtual Type
    {
    protected:
      friend class Bits::Graph<Node, Edge>;

      AnyType (Path const& file, UnsignedLong line, UnsignedLong column)
          : Node (file, line, column)
      {
      }

      AnyType () // For virtual inheritance.
      {
      }
    };


    //
    //
    class AnySimpleType: public virtual Type
    {
    protected:
      friend class Bits::Graph<Node, Edge>;

      AnySimpleType (Path const& file, UnsignedLong line, UnsignedLong column)
          : Node (file, line, column)
      {
      }

      AnySimpleType () // For virtual inheritance.
      {
      }
    };
  }
}

// ADL won't find it because Path is a typedef. Note that this
// function prints in native format.
//
std::wostream&
operator<< (std::wostream& os, XSDFrontend::SemanticGraph::Path const& path);

#endif  // XSD_FRONTEND_SEMANTIC_GRAPH_ELEMENTS_HXX
