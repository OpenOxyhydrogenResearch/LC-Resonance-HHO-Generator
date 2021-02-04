// file      : xsd-frontend/semantic-graph/elements.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <algorithm>

#include <xsd-frontend/semantic-graph/elements.hxx>
#include <xsd-frontend/semantic-graph/annotation.hxx>

using namespace std;

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    // Node
    //
    Annotation& Node::
    annotation ()
    {
      return annotates_->annotation ();
    }

    // Type
    //
    Void Type::
    remove_edge_left (Arguments& a)
    {
      ArgumentsSet::Iterator i (arguments_.find (&a));
      assert (i != arguments_.end ());
      arguments_.erase (i);
    }

    // Specialization
    //
    Void Specialization::
    remove_edge_right (Arguments& a)
    {
      // The number of entries should be small so linear search will do.
      //
      Argumented::Iterator i (
        std::find (argumented_.begin (), argumented_.end (), &a));

      assert (i != argumented_.end ());
      argumented_.erase (i);
    }

    namespace RTTI = Cult::RTTI;

    using RTTI::Access;
    using RTTI::TypeInfo;

    namespace
    {
      // Edge
      //
      struct EdgeInit
      {
        EdgeInit ()
        {
          TypeInfo ti (typeid (Edge));
          RTTI::insert (ti);
        }

      } edge_init_;


      // Node
      //
      struct NodeInit
      {
        NodeInit ()
        {
          TypeInfo ti (typeid (Node));
          RTTI::insert (ti);
        }

      } node_init_;


      // Names
      //
      struct NamesInit
      {
        NamesInit ()
        {
          TypeInfo ti (typeid (Names));
          ti.add_base (Access::public_, true, typeid (Edge));
          RTTI::insert (ti);
        }

      } names_init_;


      // Nameable
      //
      struct NameableInit
      {
        NameableInit ()
        {
          TypeInfo ti (typeid (Nameable));
          ti.add_base (Access::public_, true, typeid (Node));
          RTTI::insert (ti);
        }

      } nameable_init_;


      // Scope
      //
      struct ScopeInit
      {
        ScopeInit ()
        {
          TypeInfo ti (typeid (Scope));
          ti.add_base (Access::public_, true, typeid (Nameable));
          RTTI::insert (ti);
        }

      } scope_init_;


      // Type
      //
      struct TypeInit
      {
        TypeInit ()
        {
          TypeInfo ti (typeid (Type));
          ti.add_base (Access::public_, true, typeid (Nameable));
          RTTI::insert (ti);
        }

      } type_init_;


      // Instance
      //
      struct InstanceInit
      {
        InstanceInit ()
        {
          TypeInfo ti (typeid (Instance));
          ti.add_base (Access::public_, true, typeid (Nameable));
          RTTI::insert (ti);
        }

      } instance_init_;


      // Belongs
      //
      struct BelongsInit
      {
        BelongsInit ()
        {
          TypeInfo ti (typeid (Belongs));
          ti.add_base (Access::public_, true, typeid (Edge));
          RTTI::insert (ti);
        }

      } belongs_init_;



      // Inherits
      //
      struct InheritsInit
      {
        InheritsInit ()
        {
          TypeInfo ti (typeid (Inherits));
          ti.add_base (Access::public_, true, typeid (Edge));
          RTTI::insert (ti);
        }

      } inherits_init_;


      // Extends
      //
      struct ExtendsInit
      {
        ExtendsInit ()
        {
          TypeInfo ti (typeid (Extends));
          ti.add_base (Access::public_, true, typeid (Inherits));
          RTTI::insert (ti);
        }

      } extends_init_;


      // Restricts
      //
      struct RestrictsInit
      {
        RestrictsInit ()
        {
          TypeInfo ti (typeid (Restricts));
          ti.add_base (Access::public_, true, typeid (Inherits));
          RTTI::insert (ti);
        }

      } restricts_init_;


      // BelongsToNamespace
      //
      struct BelongsToNamespaceInit
      {
        BelongsToNamespaceInit ()
        {
          TypeInfo ti (typeid (BelongsToNamespace));
          ti.add_base (Access::public_, true, typeid (Edge));
          RTTI::insert (ti);
        }

      } belongs_to_namespace_init_;


      // Member
      //
      struct MemberInit
      {
        MemberInit ()
        {
          TypeInfo ti (typeid (Member));
          ti.add_base (Access::public_, true, typeid (Instance));
          RTTI::insert (ti);
        }

      } member_init_;


      // Specialization
      //
      struct SpecializationInit
      {
        SpecializationInit ()
        {
          TypeInfo ti (typeid (Specialization));
          ti.add_base (Access::public_, true, typeid (Type));
          RTTI::insert (ti);
        }

      } specialization_init_;


      // Arguments
      //
      struct ArgumentsInit
      {
        ArgumentsInit ()
        {
          TypeInfo ti (typeid (Arguments));
          ti.add_base (Access::public_, true, typeid (Edge));
          RTTI::insert (ti);
        }

      } arguments_init_;


      /*
      // Contains
      //
      struct ContainsInit
      {
        ContainsInit ()
        {
          TypeInfo ti (typeid (Contains));
          ti.add_base (Access::public_, true, typeid (Edge));
          RTTI::insert (ti);
        }

      } contains_init_;


      // Container
      //
      struct ContainerInit
      {
        ContainerInit ()
        {
          TypeInfo ti (typeid (Container));
          ti.add_base (Access::public_, true, typeid (Node));
          RTTI::insert (ti);
        }

      } container_init_;
      */


      // AnyType
      //
      namespace
      {
        struct AnyTypeInit
        {
          AnyTypeInit ()
          {
            TypeInfo ti (typeid (AnyType));
            ti.add_base (Access::public_, true, typeid (SemanticGraph::Type));
            RTTI::insert (ti);
          }

        } any_type_init_;
      }


      // AnySimpleType
      //
      namespace
      {
        struct AnySimpleTypeInit
        {
          AnySimpleTypeInit ()
          {
            TypeInfo ti (typeid (AnySimpleType));
            ti.add_base (Access::public_, true, typeid (Type));
            RTTI::insert (ti);
          }

        } any_simple_type_init_;
      }
    }


    // Instance
    //
    Type& Instance::
    type () const
    {
      return belongs ().type ();
    }
  }
}

// Path
//
std::wostream&
operator<< (std::wostream& os, XSDFrontend::SemanticGraph::Path const& path)
{
#if !defined(BOOST_FILESYSTEM_VERSION) || BOOST_FILESYSTEM_VERSION == 2
  return os << path.native_file_string ().c_str ();
#else
  return os << path.string ().c_str ();
#endif
}
