// file      : xsd-frontend/semantic-graph/enumeration.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/semantic-graph/enumeration.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    namespace RTTI = Cult::RTTI;

    using RTTI::Access;
    using RTTI::TypeInfo;

    namespace
    {
      // Enumeration
      //
      struct EnumerationInit
      {
        EnumerationInit ()
        {
          TypeInfo ti (typeid (Enumeration));
          ti.add_base (Access::public_, true, typeid (Complex));
          RTTI::insert (ti);
        }

      } enumeration_init_;


      // Enumerator
      //
      struct EnumeratorInit
      {
        EnumeratorInit ()
        {
          TypeInfo ti (typeid (Enumerator));
          ti.add_base (Access::public_, true, typeid (Instance));
          RTTI::insert (ti);
        }

      } enumerator_init_;
    }


    // Enumeration
    //

    Enumeration::
    Enumeration (Path const& file, UnsignedLong line, UnsignedLong column)
        : Node (file, line, column)
    {
    }


    // Enumerator
    //

    Enumerator::
    Enumerator (Path const& file, UnsignedLong line, UnsignedLong column)
        : Node (file, line, column)
    {
    }
  }
}
