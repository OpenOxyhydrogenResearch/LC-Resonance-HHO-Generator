// file      : xsd-frontend/semantic-graph/compositor.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/semantic-graph/compositors.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    namespace RTTI = Cult::RTTI;

    using RTTI::Access;
    using RTTI::TypeInfo;


    // ContainsCompositor
    //
    namespace
    {
      struct ContainsCompositorInit
      {
        ContainsCompositorInit ()
        {
          TypeInfo ti (typeid (ContainsCompositor));
          ti.add_base (Access::public_, true, typeid (Edge));
          RTTI::insert (ti);
        }

      } contains_compositor_init_;
    }

    ContainsCompositor::
    ContainsCompositor (UnsignedLong min, UnsignedLong max)
        : compositor_ (0), container_ (0), min_ (min), max_ (max)
    {
    }

    // Compositor
    //
    namespace
    {
      struct CompositorInit
      {
        CompositorInit ()
        {
          TypeInfo ti (typeid (Compositor));
          ti.add_base (Access::public_, true, typeid (Particle));
          RTTI::insert (ti);
        }

      } compositor_init_;
    }


    // All
    //
    namespace
    {
      struct AllInit
      {
        AllInit ()
        {
          TypeInfo ti (typeid (All));
          ti.add_base (Access::public_, true, typeid (Compositor));
          RTTI::insert (ti);
        }

      } all_init_;
    }

    All::
    All (Path const& file, UnsignedLong line, UnsignedLong column)
        : Node (file, line, column)
    {
    }


    // Choice
    //
    namespace
    {
      struct ChoiceInit
      {
        ChoiceInit ()
        {
          TypeInfo ti (typeid (Choice));
          ti.add_base (Access::public_, true, typeid (Compositor));
          RTTI::insert (ti);
        }

      } choice_init_;
    }

    Choice::
    Choice (Path const& file, UnsignedLong line, UnsignedLong column)
        : Node (file, line, column)
    {
    }

    // Sequence
    //
    namespace
    {
      struct SequenceInit
      {
        SequenceInit ()
        {
          TypeInfo ti (typeid (Sequence));
          ti.add_base (Access::public_, true, typeid (Compositor));
          RTTI::insert (ti);
        }

      } sequence_init_;
    }

    Sequence::
    Sequence (Path const& file, UnsignedLong line, UnsignedLong column)
        : Node (file, line, column)
    {
    }
  }
}
