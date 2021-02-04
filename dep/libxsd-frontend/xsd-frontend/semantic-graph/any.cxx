// file      : xsd-frontend/semantic-graph/any.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd-frontend/semantic-graph/any.hxx>
#include <xsd-frontend/semantic-graph/compositors.hxx>

namespace XSDFrontend
{
  namespace SemanticGraph
  {
    namespace RTTI = Cult::RTTI;

    using RTTI::Access;
    using RTTI::TypeInfo;

    namespace
    {
      struct AnyInit
      {
        AnyInit ()
        {
          TypeInfo ti (typeid (Any));
          ti.add_base (Access::public_, true, typeid (Nameable));
          ti.add_base (Access::public_, true, typeid (Particle));
          RTTI::insert (ti);
        }

      } any_init_;
    }

    Any::
    Any (Path const& file,
         UnsignedLong line,
         UnsignedLong column,
         WideString const& namespaces)
        : Node (file, line, column),
          prototype_ (0)
    {
      // Not sure if the separator is just space or any white-space
      // chararcter.
      //

      for (Size i (0), j (namespaces.find (L' '));;)
      {
        if (j != WideString::npos)
        {
          namespaces_.push_back (WideString (namespaces, i, j - i));

          i = j + 1;
          j = namespaces.find (L' ', i);
        }
        else
        {
          // Last element.
          //
          namespaces_.push_back (WideString (namespaces, i));
          break;
        }
      }
    }

    Any::
    Any (Path const& file,
         UnsignedLong line,
         UnsignedLong column,
         NamespaceIterator begin,
         NamespaceIterator end)
        : Node (file, line, column),
          prototype_ (0)
    {
      for (; begin != end; ++begin)
        namespaces_.push_back (*begin);
    }

    namespace
    {
      Namespace&
      namespace_ (Nameable& n)
      {
        // The basic idea goes like this: go up Names edges until you
        // reach Namespace. There are, however, anonymous types which
        // need special handling. In the case of an anonymous type we
        // will go up the first Belongs edge (because the first edge
        // is where the type was defined.
        //

        if (n.named_p ())
        {
          Scope& s (n.scope ());
          Namespace* ns (dynamic_cast<Namespace*> (&n));

          return ns ? *ns : namespace_ (s);
        }
        else
        {
          Type& t (dynamic_cast<Type&> (n));
          Belongs& b (*t.classifies_begin ());

          return namespace_ (b.instance ());
        }
      }
    }

    Namespace& Any::
    definition_namespace ()
    {
      if (prototype_p ())
        return prototype ().definition_namespace ();

      // Get to our scope.
      //
      Compositor* c (&contained_particle ().compositor ());

      while(!c->contained_compositor_p ())
        c = &c->contained_particle ().compositor ();

      Scope& scope (
        dynamic_cast<Scope&> (c->contained_compositor ().container ()));

      return namespace_ (scope);
    }
  }
}
