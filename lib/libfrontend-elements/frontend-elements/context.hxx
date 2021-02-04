// file      : frontend-elements/context.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef FRONTEND_ELEMENTS_CONTEXT_HXX
#define FRONTEND_ELEMENTS_CONTEXT_HXX

#include <frontend-elements/types.hxx>

#include <cult/containers/any.hxx>
#include <cult/containers/map.hxx>

namespace FrontendElements
{
  class Context: public NonCopyable
  {
    typedef
    Cult::Containers::Map<String, Cult::Containers::Any>
    Map;

  public:
    struct NoEntry {};
    struct Typing {};

    Context ()
    {
    }

    Void
    swap (Context& c)
    {
      map_.swap (c.map_);
    }

    Size
    count (Char const* key) const
    {
      return map_.count (key);
    }

    template <typename X>
    X&
    get (Char const* key)
    {
      Map::Iterator i (map_.find (key));

      if (i == map_.end ())
        throw NoEntry ();

      try
      {
        return i->second. template value<X> ();
      }
      catch (Cult::Containers::Any::Typing const&)
      {
        throw Typing ();
      }
    }

    template <typename X>
    X const&
    get (Char const* key) const
    {
      Map::ConstIterator i (map_.find (key));

      if (i == map_.end ())
        throw NoEntry ();

      try
      {
        return i->second. template value<X> ();
      }
      catch (Cult::Containers::Any::Typing const&)
      {
        throw Typing ();
      }
    }

    template <typename X>
    X const&
    get (Char const* key, X const& default_value) const
    {
      Map::ConstIterator i (map_.find (key));

      if (i == map_.end ())
        return default_value;

      try
      {
        return i->second. template value<X> ();
      }
      catch (Cult::Containers::Any::Typing const&)
      {
        throw Typing ();
      }
    }

    template <typename X>
    Void
    set (Char const* key, X const& value)
    {
      try
      {
        if (!map_.insert (Map::Pair (key, value)).second)
        {
          Map::Iterator i (map_.find (key));
          i->second.template value <X> () = value;
        }
      }
      catch (Cult::Containers::Any::Typing const&)
      {
        throw Typing ();
      }
    }

    Void
    remove (Char const* key)
    {
      Map::Iterator i (map_.find (key));

      if (i == map_.end ())
        throw NoEntry ();

      map_.erase (i);
    }

  private:
    Map map_;
  };
}

#endif  // FRONTEND_ELEMENTS_CONTEXT_HXX
