// file      : xsd-frontend/traversal/enumeration.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/traversal/enumeration.hxx>

namespace XSDFrontend
{
  namespace Traversal
  {
    // Enumeration
    //
    Void Enumeration::
    traverse (Type& e)
    {
      pre (e);
      name (e);
      inherits (e);
      names (e);
      post (e);
    }

    Void Enumeration::
    pre (Type&)
    {
    }

    Void Enumeration::
    name (Type&)
    {
    }

    Void Enumeration::
    inherits (Type& e)
    {
      inherits (e, *this);
    }

    Void Enumeration::
    inherits (Type& e, EdgeDispatcherBase& d)
    {
      if (e.inherits_p ())
        d.dispatch (e.inherits ());
    }

    Void Enumeration::
    post (Type&)
    {
    }


    // Enumerator
    //
    Void Enumerator::
    traverse (Type& e)
    {
      pre (e);
      belongs (e);
      name (e);
      post (e);
    }

    Void Enumerator::
    pre (Type&)
    {
    }

    Void Enumerator::
    belongs (Type& e, EdgeDispatcherBase& d)
    {
      d.dispatch (e.belongs ());
    }

    Void Enumerator::
    belongs (Type& e)
    {
      belongs (e, edge_traverser ());
    }

    Void Enumerator::
    name (Type&)
    {
    }

    Void Enumerator::
    post (Type&)
    {
    }
  }
}
