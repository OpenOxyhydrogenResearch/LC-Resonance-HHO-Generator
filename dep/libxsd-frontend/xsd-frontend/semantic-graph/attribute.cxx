// file      : xsd-frontend/semantic-graph/attribute.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/semantic-graph/attribute.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    namespace RTTI = Cult::RTTI;

    using RTTI::Access;
    using RTTI::TypeInfo;

    namespace
    {
      struct AttributeInit
      {
        AttributeInit ()
        {
          TypeInfo ti (typeid (Attribute));
          ti.add_base (Access::public_, true, typeid (Member));
          RTTI::insert (ti);
        }

      } attribute_init_;
    }

    Attribute::
    Attribute (Path const& file,
               UnsignedLong line,
               UnsignedLong column,
               Boolean optional,
               Boolean global,
               Boolean qualified)
        : Node (file, line, column),
          Member (global, qualified),
          optional_ (optional)
    {
    }
  }
}
