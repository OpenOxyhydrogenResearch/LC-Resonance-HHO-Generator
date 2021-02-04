// file      : xsd-frontend/semantic-graph/namespace.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/semantic-graph/namespace.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    namespace RTTI = Cult::RTTI;

    using RTTI::Access;
    using RTTI::TypeInfo;

    namespace
    {
      struct NamespaceInit
      {
        NamespaceInit ()
        {
          TypeInfo ti (typeid (Namespace));
          ti.add_base (Access::public_, true, typeid (Scope));
          RTTI::insert (ti);
        }

      } namespace_init_;
    }

    Namespace::
    Namespace (Path const& file, UnsignedLong line, UnsignedLong column)
        : Node (file, line, column)
    {
    }
  }
}
