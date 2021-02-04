// file      : xsd-frontend/semantic-graph/element.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/semantic-graph/element.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    namespace RTTI = Cult::RTTI;

    using RTTI::Access;
    using RTTI::TypeInfo;


    // Substitutes
    //
    namespace
    {
      struct SubstitutesInit
      {
        SubstitutesInit ()
        {
          TypeInfo ti (typeid (Substitutes));
          ti.add_base (Access::public_, true, typeid (Edge));
          RTTI::insert (ti);
        }

      } substitutes_init_;
    }

    // Element
    //
    namespace
    {
      struct ElementInit
      {
        ElementInit ()
        {
          TypeInfo ti (typeid (Element));
          ti.add_base (Access::public_, true, typeid (Member));
          ti.add_base (Access::public_, true, typeid (Particle));
          RTTI::insert (ti);
        }

      } element_init_;
    }

    Element::
    Element (Path const& file,
             UnsignedLong line,
             UnsignedLong column,
             Boolean global,
             Boolean qualified)
        : Node (file, line, column),
          Member (global, qualified),
          substitutes_ (0)
    {
    }
  }
}
