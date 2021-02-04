// file      : xsd-frontend/traversal/any-attribute.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_TRAVERSAL_ANY_ATTRIBUTE_HXX
#define XSD_FRONTEND_TRAVERSAL_ANY_ATTRIBUTE_HXX

#include <xsd-frontend/traversal/elements.hxx>
#include <xsd-frontend/semantic-graph/any-attribute.hxx>

namespace XSDFrontend
{
  namespace Traversal
  {
    typedef
    Node<SemanticGraph::AnyAttribute>
    AnyAttribute;
  }
}

#endif  // XSD_FRONTEND_TRAVERSAL_ANY_ATTRIBUTE_HXX
