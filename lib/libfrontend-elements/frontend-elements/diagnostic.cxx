// file      : frontend-elements/diagnostic.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <frontend-elements/diagnostic.hxx>

#include <iostream>

namespace FrontendElements
{
  namespace Diagnostic
  {
    using std::cerr;
    using std::endl;

    Log& Log::
    operator<< (Record const& r)
    {
      cerr << r.file () << ":" << r.line ();

      if (r.char_p ()) cerr << ":" << r.char_ ();

      cerr << ": ";

      r.kind ().print (cerr);

      cerr << ": " << r.text () << endl;

      return *this;
    }

    Log& Log::
    instance ()
    {
      static Log l;
      return l;
    }
  }
}

