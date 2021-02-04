// file      : frontend-elements/traversal.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef FRONTEND_ELEMENTS_TRAVERSAL_HXX
#define FRONTEND_ELEMENTS_TRAVERSAL_HXX

#include <frontend-elements/types.hxx>

#include <cult/containers/map.hxx>
#include <cult/containers/set.hxx>
#include <cult/containers/vector.hxx>

#include <cult/rtti/type-info.hxx>

#include <cult/trace/stream.hxx>

//@@ Move to trace next time you are about to uncomment this.
//
// #include <iostream>
// using std::wcerr;
// using std::endl;


namespace FrontendElements
{
  namespace Traversal
  {
    //
    //
    template<typename X>
    class TraverserBase
    {
    protected:
      virtual
      ~TraverserBase ();

      virtual Void
      trampoline (X&) = 0;

      virtual Void
      trampoline (X const&) = 0;

      template <typename>
      friend class DispatcherBase;
    };


    //
    //
    template <typename X>
    class DispatcherBase
    {
      typedef
      Cult::RTTI::TypeId
      TypeId;

      typedef
      Cult::RTTI::TypeInfo
      TypeInfo;

    public:
      virtual
      ~DispatcherBase ();

      virtual Void
      dispatch (X&);

      virtual Void
      dispatch (X const&);

      Void
      map (TypeId id, TraverserBase<X>& t)
      {
        //wcerr << "map for " << id.name () << " to " << &t
	//      << " in " << &traversal_map_ << endl;

        Traversers& traversers (traversal_map_[id]);
        traversers.push_back (&t);
      }

    public:
      typedef
      Cult::Containers::Vector<TraverserBase<X>*>
      Traversers;

      typedef
      Cult::Containers::Map<TypeId, Traversers>
      TraversalMap;

      typedef
      typename TraversalMap::ConstIterator
      Iterator;

      Iterator
      begin () const
      {
        return traversal_map_.begin ();
      }

      Iterator
      end () const
      {
        return traversal_map_.end ();
      }

    protected:
      static Cult::Trace::Stream tout;

    private:
      template<typename Y>
      Void
      dispatch_ (Y&);

    private:

      struct TypeInfoComparator
      {
        Boolean
        operator () (TypeInfo const& a, TypeInfo const& b) const
        {
          return a.type_id () < b.type_id ();
        }
      };

      typedef
      Cult::Containers::Map<TypeInfo, UnsignedLong, TypeInfoComparator>
      LevelMap;

      typedef
      Cult::Containers::Set<TypeInfo, TypeInfoComparator>
      TypeInfoSet;

      static UnsignedLong
      compute_levels (TypeInfo const& ti, UnsignedLong cur, LevelMap& map);

      static Void
      flatten_tree (TypeInfo const& ti, TypeInfoSet& set);

    private:
      TraversalMap traversal_map_;
    };


    //
    //
    template <typename X>
    class Dispatcher: public virtual DispatcherBase<X>
    {
    public:
      Dispatcher ()
          : merge_ (true)
      {
      }

      Void
      traverser (DispatcherBase<X>& d)
      {
        for (typename DispatcherBase<X>::Iterator
               i (d.begin ()), e (d.end ()); i != e; ++i)
        {
          for (typename DispatcherBase<X>::Traversers::ConstIterator
                 t (i->second.begin ()), e (i->second.end ()); t != e; ++t)
          {
            dispatcher_.map (i->first, **t);
          }
        }
      }

    public:
      virtual Void
      dispatch (X& x)
      {
        merge ();
        dispatcher_.dispatch (x);
      }

      virtual Void
      dispatch (X const& x)
      {
        merge ();
        dispatcher_.dispatch (x);
      }

      using DispatcherBase<X>::begin;
      using DispatcherBase<X>::end;

    private:
      Void
      merge ()
      {
        if (merge_)
        {
          for (typename DispatcherBase<X>::Iterator
                 i (begin ()), e (end ()); i != e; ++i)
          {
            for (typename DispatcherBase<X>::Traversers::ConstIterator
                   t (i->second.begin ()), e (i->second.end ()); t != e; ++t)
            {
              dispatcher_.map (i->first, **t);
            }
          }

          merge_ = false;
        }
      }

    protected:
      template <typename I, typename Y>
      Void
      iterate_and_dispatch (I begin, I end, DispatcherBase<Y>& d)
      {
        for (; begin != end; ++begin)
        {
          d.dispatch (*begin);
        }
      }

      template <typename T, typename A, typename I, typename Y>
      Void
      iterate_and_dispatch (I begin,
                            I end,
                            DispatcherBase<Y>& d,
                            T& t,
                            Void (T::*next)(A&),
                            A& a)
      {
        for (; begin != end;)
        {
          d.dispatch (*begin);

          if (++begin != end && next != 0)
            (t.*next) (a);
        }
      }

    private:
      Boolean merge_;
      DispatcherBase<X> dispatcher_;
    };


    //
    //
    template <typename T, typename X>
    struct Traverser : TraverserBase<X>, virtual Dispatcher<X>
    {
      typedef T Type;

      Traverser ()
      {
        map (typeid (Type), *this);
      }

      virtual Void
      traverse (Type&)
      {
        abort ();
      }

      virtual Void
      traverse (Type const&)
      {
        abort ();
      }

    protected:
      virtual Void
      trampoline (X& x)
      {
        //wcerr << "trampoline for " << &i << " to type "
        //      << typeid (type).name () << endl;

        traverse (dynamic_cast<Type&> (x));
      }

      virtual Void
      trampoline (X const& x)
      {
        //wcerr << "trampoline for " << &i << " to type "
        //      << typeid (Type).name () << endl;

        traverse (dynamic_cast<Type const&> (x));
      }
    };
  }
}

#include <frontend-elements/traversal.ixx>
#include <frontend-elements/traversal.txx>

#endif  // FRONTEND_ELEMENTS_TRAVERSAL_HXX
