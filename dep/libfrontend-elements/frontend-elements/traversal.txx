// file      : frontend-elements/traversal.txx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace FrontendElements
{
  namespace Traversal
  {
    // TraverserBase
    //

    template<typename X>
    TraverserBase<X>::
    ~TraverserBase ()
    {
    }

    // DispatcherBase
    //

    template <typename X>
    DispatcherBase<X>::
    ~DispatcherBase ()
    {
    }

    template <typename X>
    Void DispatcherBase<X>::
    dispatch (X& x)
    {
      dispatch_ (x);
    }

    template <typename X>
    void DispatcherBase<X>::
    dispatch (X const& x)
    {
      dispatch_ (x);
    }

    template <typename X>
    template <typename Y>
    void DispatcherBase<X>::
    dispatch_ (Y& y)
    {
      LevelMap levels;

      TypeInfo const& ti (Cult::RTTI::lookup (typeid (y)));

      UnsignedLong max (compute_levels (ti, 0, levels));

      tout << "starting dispatch process for " << ti.type_id ().name ()
           << " with " << max << " levels";

      for (UnsignedLong l (0); l < max + 1; ++l)
      {
        TypeInfoSet dispatched;

        for (typename LevelMap::ConstIterator
               i (levels.begin ()), e (levels.end ()); i != e; ++i)
        {
          if (i->second == l)
          {
            typename TraversalMap::ConstIterator v (
              traversal_map_.find (i->first.type_id ()));

            if (v != traversal_map_.end ())
            {
              tout << "dispatching traversers for " << ti.type_id ().name ()
                   << " as " << i->first.type_id ().name ();

              Traversers const& traversers (v->second);

              for (typename Traversers::ConstIterator
                     ti (traversers.begin ()), te (traversers.end ()); ti != te; ++ti)
              {
                (*ti)->trampoline (y);
              }

              flatten_tree (i->first, dispatched);
            }
          }
        }

        // Remove traversed types from the level map.
        //
        for (typename TypeInfoSet::ConstIterator i (dispatched.begin ());
             i != dispatched.end (); ++i)
        {
          levels.erase (*i);
        }
      }
    }


    template <typename X>
    UnsignedLong DispatcherBase<X>::
    compute_levels (TypeInfo const& ti, UnsignedLong cur, LevelMap& map)
    {
      UnsignedLong ret (cur);

      if (map.find (ti) == map.end () || map[ti] < cur) map[ti] = cur;

      for (TypeInfo::BaseIterator i (ti.begin_base ());
           i != ti.end_base (); ++i)
      {
        UnsignedLong tmp (compute_levels (i->type_info (), cur + 1, map));

        if (tmp > ret)
          ret = tmp;
      }

      return ret;
    }

    template <typename X>
    Void DispatcherBase<X>::
    flatten_tree (TypeInfo const& ti, TypeInfoSet& set)
    {
      set.insert (ti);

      for (TypeInfo::BaseIterator i = ti.begin_base ();
           i != ti.end_base (); ++i)
      {
        flatten_tree (i->type_info (), set);
      }
    }

    template <typename X>
    Cult::Trace::Stream DispatcherBase<X>::
    tout ("frontend-elements::traversal", 5);
  }
}

