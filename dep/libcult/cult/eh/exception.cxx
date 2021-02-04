// file      : cult/eh/exception.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/eh/exception.hxx>

#include <typeinfo>

namespace Cult
{
  namespace EH
  {
    Char const* Exception::
    what () const throw ()
    {
      try
      {
        return typeid (*this).name ();
      }
      catch (...)
      {
        return "";
      }
    }
  }
}
