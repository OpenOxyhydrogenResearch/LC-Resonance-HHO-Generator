// file      : xsd-frontend/transformations/schema-per-type.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_TRANSFORMATIONS_SCHEMA_PER_TYPE_HXX
#define XSD_FRONTEND_TRANSFORMATIONS_SCHEMA_PER_TYPE_HXX

#include <cult/types.hxx>
#include <cult/containers/vector.hxx>

#include <xsd-frontend/semantic-graph/elements.hxx> // Path
#include <xsd-frontend/semantic-graph/schema.hxx>

namespace XSDFrontend
{
  namespace Transformations
  {
    using namespace Cult::Types;

    class SchemaPerTypeTranslator
    {
    public:
      virtual
      ~SchemaPerTypeTranslator ();

      // The following two functions should return empty string if
      // there is no match.
      //
      virtual WideString
      translate_type (WideString const& ns, WideString const& name) = 0;

      virtual NarrowString
      translate_schema (NarrowString const& abs_path) = 0;
    };

    // This transformation restructures the semantic graph to have
    // each type definition in a seperate schema file.
    //
    class SchemaPerType
    {
    public:
      struct Failed {};

      // If a type of an element or attribute has a context entry
      // with the by_value_key key and it is true, then the schema
      // for this type is included "strongly".
      //
      SchemaPerType (SchemaPerTypeTranslator&, Char const* by_value_key = 0);

      Cult::Containers::Vector<SemanticGraph::Schema*>
      transform (SemanticGraph::Schema&);

    private:
      Char const* by_value_key_;
      SchemaPerTypeTranslator& trans_;
    };
  }
}

#endif // XSD_FRONTEND_TRANSFORMATIONS_SCHEMA_PER_TYPE_HXX
