// file      : xsd-frontend/semantic-graph/attribute-group.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/semantic-graph/attribute-group.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    namespace RTTI = Cult::RTTI;

    using RTTI::Access;
    using RTTI::TypeInfo;


    namespace
    {
      struct AttributeGroupInit
      {
        AttributeGroupInit ()
        {
          TypeInfo ti (typeid (AttributeGroup));
          ti.add_base (Access::public_, true, typeid (Scope));
          RTTI::insert (ti);
        }

      } attribute_group_init_;
    }

    AttributeGroup::
    AttributeGroup (Path const& file, UnsignedLong line, UnsignedLong column)
        : Node (file, line, column)
    {
    }

  }
}
