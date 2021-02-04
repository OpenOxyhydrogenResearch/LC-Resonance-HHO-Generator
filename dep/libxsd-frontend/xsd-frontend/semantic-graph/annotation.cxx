// file      : xsd-frontend/semantic-graph/annotation.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/semantic-graph/annotation.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    namespace RTTI = Cult::RTTI;

    using RTTI::Access;
    using RTTI::TypeInfo;


    // Annotates
    //
    namespace
    {
      struct AnnotatesInit
      {
        AnnotatesInit ()
        {
          TypeInfo ti (typeid (Annotates));
          ti.add_base (Access::public_, true, typeid (Edge));
          RTTI::insert (ti);
        }

      } annotates_init_;
    }

    // Annotation
    //
    namespace
    {
      struct AnnotationInit
      {
        AnnotationInit ()
        {
          TypeInfo ti (typeid (Annotation));
          ti.add_base (Access::public_, true, typeid (Node));
          RTTI::insert (ti);
        }

      } annotation_init_;
    }
  }
}
