// file      : examples/diagnostic/driver.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/types.hxx>

#include <frontend-elements/diagnostic.hxx>

using namespace Cult::Types;
using namespace FrontendElements::Diagnostic;

// Some ideas: The first letter (`e') in `epsyntx' is for error.
// The second letter identifies part of the system (p - parser).
//
//
Error epsyntx ("EPSYNTX");

Warning wscoer ("WS001");

Stream dout;

Int
main ()
{
  dout << epsyntx << "foo.cxx" << 1UL << 12UL << "syntax error";

  dout << wscoer << "foo.cxx" << 2UL << "type coercion";
}
