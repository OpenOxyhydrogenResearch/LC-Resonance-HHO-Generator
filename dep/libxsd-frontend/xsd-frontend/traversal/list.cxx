// file      : xsd-frontend/traversal/list.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/traversal/list.hxx>

namespace XSDFrontend
{
  namespace Traversal
  {
    Void List::
    traverse (Type& l)
    {
      pre (l);
      argumented (l);
      name (l);
      post (l);
    }

    Void List::
    pre (Type&)
    {
    }

    Void List::
    argumented (Type& l)
    {
      argumented (l, *this);
    }

    Void List::
    argumented (Type& l, EdgeDispatcherBase& d)
    {
      d.dispatch (l.argumented ());
    }

    Void List::
    name (Type&)
    {
    }

    Void List::
    post (Type&)
    {
    }
  }
}
