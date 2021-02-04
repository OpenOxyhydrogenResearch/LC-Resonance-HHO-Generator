// file      : xsd-frontend/traversal/elements.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/traversal/elements.hxx>

namespace XSDFrontend
{
  namespace Traversal
  {
    // Instance
    //
    Void Instance::
    traverse (Type& a)
    {
      pre (a);
      belongs (a);
      post (a);
    }

    Void Instance::
    pre (Type&)
    {
    }

    Void Instance::
    belongs (Type& a, EdgeDispatcherBase& d)
    {
      d.dispatch (a.belongs ());
    }

    Void Instance::
    belongs (Type& a)
    {
      belongs (a, edge_traverser ());
    }

    Void Instance::
    post (Type&)
    {
    }


    // Member
    //
    Void Member::
    traverse (Type& a)
    {
      pre (a);
      belongs (a);
      post (a);
    }

    Void Member::
    pre (Type&)
    {
    }

    Void Member::
    belongs (Type& a, EdgeDispatcherBase& d)
    {
      d.dispatch (a.belongs ());
    }

    Void Member::
    belongs (Type& a)
    {
      belongs (a, edge_traverser ());
    }

    Void Member::
    post (Type&)
    {
    }
  }
}
