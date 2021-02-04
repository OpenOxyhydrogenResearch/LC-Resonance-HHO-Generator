// file      : xsd-frontend/semantic-graph/element-group.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/semantic-graph/element-group.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    namespace RTTI = Cult::RTTI;

    using RTTI::Access;
    using RTTI::TypeInfo;


    namespace
    {
      struct ElementGroupInit
      {
        ElementGroupInit ()
        {
          TypeInfo ti (typeid (ElementGroup));
          ti.add_base (Access::public_, true, typeid (Scope));
          RTTI::insert (ti);
        }

      } element_group_init_;
    }

    ElementGroup::
    ElementGroup (Path const& file, UnsignedLong line, UnsignedLong column)
        : Node (file, line, column), contains_compositor_ (0)
    {
    }
  }
}
