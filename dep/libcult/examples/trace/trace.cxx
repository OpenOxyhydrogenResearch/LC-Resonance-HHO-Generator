// file      : examples/trace/trace.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/types.hxx>

#include <cult/trace/log.hxx>
#include <cult/trace/record.hxx>
#include <cult/trace/stream.hxx>

#include <ostream>

using namespace Cult;

struct Foo {};

std::ostream&
operator<< (std::ostream& o, Foo const&)
{
  return o << "::Foo";
}

Trace::Stream tout ("Examples::Trace", 4);

Int
main ()
{
  using Trace::Record;

  Trace::Log::instance ().level (9);

  Record a ("main", 2);
  a << "notationally burdensome";
  tout << a;

  Record b ("main", 2);
  tout << (b << "a bit better, but still burdensome");

  tout << (Record ("main", 2) << "this is"
           << " somewhat"
           << " twisted but nice to be able to");

  tout << "concise, using default level";

  tout << 9 << "concise, using custom level";

  Foo f;

  tout << 3 << f << " " << 5;
}
