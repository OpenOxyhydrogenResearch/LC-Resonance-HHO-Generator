// file      : xsd-frontend/transformations/anonymous.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_TRANSFORMATIONS_ANONYMOUS_HXX
#define XSD_FRONTEND_TRANSFORMATIONS_ANONYMOUS_HXX

#include <cult/types.hxx>

#include <xsd-frontend/semantic-graph/elements.hxx> // Path
#include <xsd-frontend/semantic-graph/schema.hxx>

namespace XSDFrontend
{
  namespace Transformations
  {
    using namespace Cult::Types;

    class AnonymousNameTranslator
    {
    public:
      virtual
      ~AnonymousNameTranslator ();

      // The file argument is empty for the currect translation
      // unit.
      //
      virtual WideString
      translate (WideString const& file,
                 WideString const& ns,
                 WideString const& name,
                 WideString const& xpath) = 0;
    };

    // This transformation morphs anonymous types into named ones
    // with the names derived from the enclosing attributes and
    // elements. If the detect_unstable_conflicts argument is true
    // then the transformation detects and reports unstable conflicts
    // in name assignment.
    //
    class Anonymous
    {
    public:
      struct Failed {};

      Anonymous (AnonymousNameTranslator&);

      Void
      transform (SemanticGraph::Schema&,
                 SemanticGraph::Path const&,
                 Boolean detect_unstable_conflicts);

    private:
      AnonymousNameTranslator& trans_;
    };
  }
}

#endif // XSD_FRONTEND_TRANSFORMATIONS_ANONYMOUS_HXX
