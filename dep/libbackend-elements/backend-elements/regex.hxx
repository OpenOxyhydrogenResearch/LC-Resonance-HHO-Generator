// file      : backend-elements/regex.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef BACKEND_ELEMENTS_REGEX_HXX
#define BACKEND_ELEMENTS_REGEX_HXX

#include <ostream>

#include <boost/regex.hpp>

#include <backend-elements/types.hxx>

namespace BackendElements
{
  namespace Regex
  {
    template <typename C>
    struct Format
    {
      Format (StringTemplate<C> const& expression,
              StringTemplate<C> const& description)
          : expression_ (expression), description_ (description)
      {
      }

      StringTemplate<C> const&
      expression () const
      {
        return expression_;
      }

      StringTemplate<C> const&
      description () const
      {
        return description_;
      }

    private:
      StringTemplate<C> expression_;
      StringTemplate<C> description_;
    };

    // Regex pattern.
    //
    template <typename C>
    struct Pattern
    {
      Pattern ()
      {
      }

      Pattern (Char const* p)
      {
        init (StringTemplate<C> (p));
      }

      Pattern (StringTemplate<C> const& p)
      {
        init (p);
      }

      Pattern&
      operator= (Char const* p)
      {
        init (StringTemplate<C> (p));
        return *this;
      }

      Pattern&
      operator= (StringTemplate<C> const& p)
      {
        init (p);
        return *this;
      }

    public:
      Boolean
      match (StringTemplate<C> const& s) const
      {
        return regex_match (s, pat_, boost::format_all);
      }

      StringTemplate<C>
      merge (StringTemplate<C> const& sub,
             StringTemplate<C> const& s,
             Boolean first_only = false) const
      {
        if (first_only)
          return regex_merge (
            s, pat_, sub, boost::format_all | boost::format_first_only);
        else
          return regex_merge ( s, pat_, sub, boost::format_all);
      }

    public:
      Boolean
      empty () const
      {
        return pat_.empty ();
      }

    public:
      boost::basic_regex<C> const&
      impl_pattern () const
      {
        return pat_;
      }

    private:
      Void
      init (StringTemplate<C> const& r);

    private:
      boost::basic_regex<C> pat_;
    };

    template <typename C1, typename C2>
    inline std::basic_ostream<C1>&
    operator<< (std::basic_ostream<C1>& os, Pattern<C2> const& p)
    {
      return os << p.impl_pattern ().str ().c_str ();
    }

    // Regex expression: '/pattern/substitution/'.
    //
    template <typename C>
    struct Expression
    {
      Expression ()
      {
      }

      // Expression is of the form /regex/format/ where '/' can be
      // replaced with any delimiter.
      //
      Expression (Char const* e)
      {
        init (StringTemplate<C> (e));
      }

      Expression (StringTemplate<C> const& e)
      {
        init (e);
      }

      Expression&
      operator= (Char const* e)
      {
        init (StringTemplate<C> (e));
        return *this;
      }

      Expression&
      operator= (StringTemplate<C> const& e)
      {
        init (e);
        return *this;
      }

    public:
      Boolean
      match (StringTemplate<C> const& s) const
      {
        return pat_.match (s);
      }

      StringTemplate<C>
      merge (StringTemplate<C> const& s, Boolean first_only = false) const
      {
        return pat_.merge (sub_, s, first_only);
      }

    public:
      const Pattern<C>&
      pattern () const
      {
        return pat_;
      }

      const StringTemplate<C>&
      substitution () const
      {
        return sub_;
      }

    public:
      Boolean
      empty () const
      {
        return pat_.empty () && sub_.empty ();
      }

    private:
      Void
      init (StringTemplate<C> const& r);

    private:
      Pattern<C> pat_;
      StringTemplate<C> sub_;
    };
  }
}

#include <backend-elements/regex.txx>

#endif  // BACKEND_ELEMENTS_REGEX_HXX
