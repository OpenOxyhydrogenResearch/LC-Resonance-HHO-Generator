// file      : xsd-frontend/parser.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_PARSER_HXX
#define XSD_FRONTEND_PARSER_HXX

#include <cult/types.hxx>
#include <cult/containers/set.hxx>

#include <xsd-frontend/semantic-graph/schema.hxx>

namespace XSDFrontend
{
  using namespace Cult::Types;

  struct InvalidSchema {};

  class LocationTranslator
  {
  public:
    virtual
    ~LocationTranslator ();

    virtual NarrowString
    translate (NarrowString const& location) = 0;
  };

  // Set of disabled warning IDs. Special ID "all" disables all
  // warnings.
  //
  typedef Cult::Containers::Set<NarrowString> WarningSet;

  class Parser: public NonCopyable
  {
  public:
    ~Parser ();

    Parser (Boolean proper_restriction,
            Boolean multiple_imports,
            Boolean full_schema_check);

    Parser (Boolean proper_restriction,
            Boolean multiple_imports,
            Boolean full_schema_check,
            LocationTranslator&,
            const WarningSet& disabled);

  public:
    // Parse a schema file. Throws InvalidSchema in case of a failure.
    //
    Evptr<SemanticGraph::Schema>
    parse (SemanticGraph::Path const&);

    // Parse a number of schema files all into one semantic graph.
    // Each schema file is imported from an unnamed root translation
    // unit. Throws InvalidSchema in case of a failure.
    //
    Evptr<SemanticGraph::Schema>
    parse (SemanticGraph::Paths const&);

    // Returns a schema graph that corresponds to the XML Schema
    // namespace with built-in type definitions. The path is fake
    // and is only used as a lable.
    //
    Evptr<SemanticGraph::Schema>
    xml_schema (SemanticGraph::Path const&);

  private:
    class Impl;
    Evptr<Impl> impl_;
  };
}

#endif  // XSD_FRONTEND_PARSER_HXX
