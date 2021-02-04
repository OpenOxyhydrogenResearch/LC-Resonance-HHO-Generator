// file      : xsd-frontend/semantic-graph/schema.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/semantic-graph/schema.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    namespace RTTI = Cult::RTTI;

    using RTTI::Access;
    using RTTI::TypeInfo;

    namespace
    {
      // Uses
      //
      struct UsesInit
      {
        UsesInit ()
        {
          TypeInfo ti (typeid (Uses));
          ti.add_base (Access::public_, true, typeid (Edge));
          RTTI::insert (ti);
        }

      } uses_init_;


      // Implies
      //
      struct ImpliesInit
      {
        ImpliesInit ()
        {
          TypeInfo ti (typeid (Implies));
          ti.add_base (Access::public_, true, typeid (Uses));
          RTTI::insert (ti);
        }

      } implies_init_;


      // Sources
      //
      struct SourcesInit
      {
        SourcesInit ()
        {
          TypeInfo ti (typeid (Sources));
          ti.add_base (Access::public_, true, typeid (Uses));
          RTTI::insert (ti);
        }

      } sources_init_;


      // Includes
      //
      struct IncludesInit
      {
        IncludesInit ()
        {
          TypeInfo ti (typeid (Includes));
          ti.add_base (Access::public_, true, typeid (Uses));
          RTTI::insert (ti);
        }

      } includes_init_;


      // Imports
      //
      struct ImportsInit
      {
        ImportsInit ()
        {
          TypeInfo ti (typeid (Imports));
          ti.add_base (Access::public_, true, typeid (Uses));
          RTTI::insert (ti);
        }

      } imports_init_;


      // Schema
      //
      struct SchemaInit
      {
        SchemaInit ()
        {
          TypeInfo ti (typeid (Schema));
          ti.add_base (Access::public_, true, typeid (Scope));
          RTTI::insert (ti);
        }

      } schema_init_;
    }


    // Schema
    //
    Schema::NamesIteratorPair Schema::
    find (Name const& name) const
    {
      // Here we are going to create an illusion that the namespace
      // hierarchy is flat.
      names_.clear ();
      schemas_.clear ();

      find_ (name, names_, schemas_);

      return NamesIteratorPair (NamesConstIterator (names_.begin ()),
                                NamesConstIterator (names_.end ()));
    }

    Void Schema::
    find_ (Name const& name, NamesList& names, SchemaSet& set) const
    {
      set.insert (this);

      // Check our own namespace first so it will end up first in the list.
      //
      NamesIteratorPair pair (Scope::find (name));
      names.insert (names.end (), pair.first.base (), pair.second.base ());

      for (UsesIterator i (uses_begin ()), end (uses_end ()); i != end; ++i)
      {
        Schema& s (i->schema ());

        if (set.find (&s) == set.end ())
          s.find_ (name, names, set);
      }
    }
  }
}
