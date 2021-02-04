// file      : xsd-frontend/semantic-graph/complex.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/semantic-graph/complex.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    namespace RTTI = Cult::RTTI;

    using RTTI::Access;
    using RTTI::TypeInfo;

    namespace
    {
      struct ComplexInit
      {
        ComplexInit ()
        {
          TypeInfo ti (typeid (Complex));
          ti.add_base (Access::public_, true, typeid (Type));
          ti.add_base (Access::public_, true, typeid (Scope));
          RTTI::insert (ti);
        }

      } complex_init_;
    }

    Complex::
    Complex ()
        : mixed_ (false), contains_compositor_ (0)
    {
    }

    Complex::
    Complex (Path const& file, UnsignedLong line, UnsignedLong column)
        : Node (file, line, column),
          mixed_ (false), contains_compositor_ (0)
    {
    }
  }
}
