// file      : xsd-frontend/semantic-graph/list.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/semantic-graph/list.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    namespace RTTI = Cult::RTTI;

    using RTTI::Access;
    using RTTI::TypeInfo;

    namespace
    {
      struct ListInit
      {
        ListInit ()
        {
          TypeInfo ti (typeid (List));
          ti.add_base (Access::public_, true, typeid (Specialization));
          RTTI::insert (ti);
        }

      } list_init_;
    }

    List::
    List (Path const& file, UnsignedLong line, UnsignedLong column)
        : Node (file, line, column)
    {
    }
  }
}
