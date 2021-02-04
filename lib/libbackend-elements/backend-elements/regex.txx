// file      : backend-elements/regex.txx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace BackendElements
{
  namespace Regex
  {
    template <typename C>
    Void Pattern<C>::
    init (StringTemplate<C> const& r)
    {
      try
      {
        pat_ = r;
      }
      catch (boost::regex_error const& e)
      {
        throw Format<C> (r, e.what ());
      }
    }

    //
    //
    template <typename C>
    Void Expression<C>::
    init (StringTemplate<C> const& r)
    {
      typedef StringTemplate<C> String;

      if (r.empty ())
        throw Format<C> (r, "empty expression");

      C d (r[0]);

      Size first (0);
      Size middle (r.find (d, first + 1));

      if (middle == String::npos)
        throw Format<C> (r, "missing second pattern-substitution separator");

      Size last (r.find (d, middle + 1));

      if (last == String::npos)
        throw Format<C> (r, "missing third pattern-substitution separator");

      pat_ = String (r, first + 1, middle - first - 1);
      sub_.assign (r, middle + 1, last - middle - 1);
    }
  }
}
