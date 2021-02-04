// file      : xsd-frontend/semantic-graph/particle.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_FRONTEND_SEMANTIC_GRAPH_PARTICLE_HXX
#define XSD_FRONTEND_SEMANTIC_GRAPH_PARTICLE_HXX

#include <xsd-frontend/semantic-graph/elements.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    //
    //
    class Particle;
    class Compositor;


    //
    //
    class ContainsParticle: public virtual Edge
    {
    public:
      Particle&
      particle () const
      {
        return *particle_;
      }

      Compositor&
      compositor () const
      {
        return *compositor_;
      }

    public:
      UnsignedLong
      min () const
      {
        return min_;
      }

      UnsignedLong
      max () const
      {
        return max_;
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      ContainsParticle (UnsignedLong min, UnsignedLong max);

      Void
      set_left_node (Compositor& n)
      {
        compositor_ = &n;
      }

      Void
      set_right_node (Particle& n)
      {
        particle_ = &n;
      }

      Void
      clear_left_node (Compositor& n)
      {
        assert (compositor_ == &n);
        compositor_ = 0;
      }

      Void
      clear_right_node (Particle& n)
      {
        assert (particle_ == &n);
        particle_ = 0;
      }

    private:
      Particle* particle_;
      Compositor* compositor_;
      UnsignedLong min_, max_;
    };

    //
    //
    class Particle: public virtual Node
    {
    public:
      Boolean
      contained_particle_p ()
      {
        return contained_particle_ != 0;
      }

      ContainsParticle&
      contained_particle ()
      {
        assert (contained_particle_ != 0);
        return *contained_particle_;
      }

    public:
      UnsignedLong
      min () const
      {
        assert (contained_particle_ != 0);
        return contained_particle_->min ();
      }

      UnsignedLong
      max () const
      {
        assert (contained_particle_ != 0);
        return contained_particle_->max ();
      }

    protected:
      friend class Bits::Graph<Node, Edge>;

      Particle ();

      Void
      add_edge_right (ContainsParticle& e)
      {
        contained_particle_ = &e;
      }

      Void
      remove_edge_right (ContainsParticle& e)
      {
        assert (contained_particle_ == &e);
        contained_particle_ = 0;
      }

    private:
      ContainsParticle* contained_particle_;
    };
  }
}

#endif  // XSD_FRONTEND_SEMANTIC_GRAPH_PARTICLE_HXX
