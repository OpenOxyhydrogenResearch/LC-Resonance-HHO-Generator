// file      : xsd-frontend/semantic-graph/particle.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/semantic-graph/particle.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    namespace RTTI = Cult::RTTI;

    using RTTI::Access;
    using RTTI::TypeInfo;

    // ContainsParticle
    //
    namespace
    {
      struct ContainsParticleInit
      {
        ContainsParticleInit ()
        {
          TypeInfo ti (typeid (ContainsParticle));
          ti.add_base (Access::public_, true, typeid (Edge));
          RTTI::insert (ti);
        }

      } contains_particle_init_;
    }

    ContainsParticle::
    ContainsParticle (UnsignedLong min, UnsignedLong max)
        : particle_ (0), compositor_ (0), min_ (min), max_ (max)
    {
    }

    // Particle
    //
    namespace
    {
      struct ParticleInit
      {
        ParticleInit ()
        {
          TypeInfo ti (typeid (Particle));
          ti.add_base (Access::public_, true, typeid (Node));
          RTTI::insert (ti);
        }

      } particle_init_;
    }

    Particle::
    Particle ()
        : contained_particle_ (0)
    {
    }
  }
}
