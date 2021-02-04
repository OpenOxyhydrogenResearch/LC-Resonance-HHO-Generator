// file      : xsd-frontend/traversal/particle.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/traversal/particle.hxx>

namespace XSDFrontend
{
  namespace Traversal
  {
    // Particle
    //
    Void Particle::
    traverse (Type& c)
    {
      pre (c);
      post (c);
    }

    Void Particle::
    pre (Type&)
    {
    }

    Void Particle::
    post (Type&)
    {
    }
  }
}
