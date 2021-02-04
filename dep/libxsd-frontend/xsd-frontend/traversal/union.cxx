// file      : xsd-frontend/traversal/union.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/traversal/union.hxx>

namespace XSDFrontend
{
  namespace Traversal
  {
    Void Union::
    traverse (Type& u)
    {
      pre (u);
      argumented (u);
      name (u);
      post (u);
    }

    Void Union::
    pre (Type&)
    {
    }

    Void Union::
    argumented (Type& u)
    {
      argumented (u, *this);
    }

    Void Union::
    argumented (Type& u, EdgeDispatcherBase& d)
    {
      iterate_and_dispatch (u.argumented_begin (), u.argumented_end (), d);
    }

    Void Union::
    name (Type&)
    {
    }

    Void Union::
    post (Type&)
    {
    }
  }
}
