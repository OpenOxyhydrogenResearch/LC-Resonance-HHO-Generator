// file      : examples/mm/shptr/shptr.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/mm/shptr.hxx>
#include <cult/mm/new.hxx>     // MM::locate
#include <cult/mm/counter.hxx> // MM::inc_ref

#include <iostream>

using std::cerr;
using std::endl;

using namespace Cult;
using namespace MM;

struct Foo 
{
  virtual ~Foo () {} 
  char c;
};

struct Bar: virtual Foo {char c;};

struct Baz: virtual Foo {char c;};

struct Fox: Bar, Baz {};


struct A
{
  char c[8];
};

struct B
{
  char c[8];
};

struct C : A, B
{
  char c[8];
};

int
main ()
{
  {
    Baz* bp (new Fox);
    Foo* fp (bp);

    Counter* cp (locate (fp, *counted));

    inc_ref (bp);

    cp->dec_ref ();

    if (cp->dec_ref ()) cerr << "good: destroying" << endl;
    else cerr << "bad: leaking" << endl;

    delete bp;
  }

  {
    Shptr<Fox> pfox (new Fox);
    Shptr<Bar> pbar (pfox);

    Shptr<Foo> pfoo;

    pfoo = pbar;
  }
}
