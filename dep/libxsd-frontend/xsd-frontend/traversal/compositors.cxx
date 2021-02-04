// file      : xsd-frontend/traversal/compositors.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/traversal/compositors.hxx>

namespace XSDFrontend
{
  namespace Traversal
  {
    // ContainsParticle
    //
    Void ContainsParticle::
    traverse (Type& c)
    {
      dispatch (c.particle ());
    }


    // ContainsCompositor
    //
    Void ContainsCompositor::
    traverse (Type& c)
    {
      dispatch (c.compositor ());
    }


    // Compositor
    //
    Void Compositor::
    traverse (Type& c)
    {
      pre (c);
      contains (c);
      post (c);
    }

    Void Compositor::
    pre (Type&)
    {
    }

    Void Compositor::
    contains (Type& c)
    {
      iterate_and_dispatch (
        c.contains_begin (), c.contains_end (), edge_traverser ());
    }

    Void Compositor::
    contains (Type& c, EdgeDispatcherBase& d)
    {
      iterate_and_dispatch (c.contains_begin (), c.contains_end (), d);
    }

    Void Compositor::
    post (Type&)
    {
    }


    // All
    //
    Void All::
    traverse (Type& c)
    {
      pre (c);
      contains (c);
      post (c);
    }

    Void All::
    pre (Type&)
    {
    }

    Void All::
    contains (Type& c)
    {
      iterate_and_dispatch (
        c.contains_begin (), c.contains_end (), edge_traverser ());
    }

    Void All::
    contains (Type& c, EdgeDispatcherBase& d)
    {
      iterate_and_dispatch (c.contains_begin (), c.contains_end (), d);
    }

    Void All::
    post (Type&)
    {
    }


    // Choice
    //
    Void Choice::
    traverse (Type& c)
    {
      pre (c);
      contains (c);
      post (c);
    }

    Void Choice::
    pre (Type&)
    {
    }

    Void Choice::
    contains (Type& c)
    {
      iterate_and_dispatch (
        c.contains_begin (), c.contains_end (), edge_traverser ());
    }

    Void Choice::
    contains (Type& c, EdgeDispatcherBase& d)
    {
      iterate_and_dispatch (c.contains_begin (), c.contains_end (), d);
    }

    Void Choice::
    post (Type&)
    {
    }


    // Sequence
    //
    Void Sequence::
    traverse (Type& c)
    {
      pre (c);
      contains (c);
      post (c);
    }

    Void Sequence::
    pre (Type&)
    {
    }

    Void Sequence::
    contains (Type& c)
    {
      iterate_and_dispatch (
        c.contains_begin (), c.contains_end (), edge_traverser ());
    }

    Void Sequence::
    contains (Type& c, EdgeDispatcherBase& d)
    {
      iterate_and_dispatch (c.contains_begin (), c.contains_end (), d);
    }

    Void Sequence::
    post (Type&)
    {
    }
  }
}
