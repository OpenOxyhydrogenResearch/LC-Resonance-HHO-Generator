// file      : examples/mm/transfer/transfer.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/mm/evptr.hxx>

#include <iostream>

using std::cerr;
using std::endl;

using namespace Cult;

unsigned long count = 0;
unsigned long clone_count = 0;

struct Type
{
  Type ()
  {
    ++count;
  }

  ~Type ()
  {
    --count;
  }

  Evptr<Type>
  clone () const
  {
    ++clone_count;
    return Evptr<Type> (new Type);
  }

  Void
  f () const
  {
    Int i = i_;
    ++i;
  }

  Int i_;
};


Evptr<Type>
source ()
{
  return Evptr<Type> (new Type);
}

Void
sink (Evptr<Type> a, Boolean r = true)
{
  if (r)
  {
    sink (a, false);
  }
  else
  {
    Evptr<Type> b (a);

    cerr << "\tshare count: " << b.count () << endl;

    // Any of these will trigger cloning.
    //
    b->f ();
  }
}

Int
main ()
{
  // case 1
  //
  {
    cerr << "sink (new type)" << endl;

    clone_count = 0;
    sink (new Type);

    cerr << "\tclone count: " << clone_count << endl
         << endl;
  }

  // case 2
  //
  {
    cerr << "sink (source ())" << endl;

    clone_count = 0;
    sink (source ());

    cerr << "\tclone count: " << clone_count << endl
         << endl;
  }


  // case 3
  //
  {
    cerr << "sink (p)" << endl;

    clone_count = 0;

    Evptr<Type> p (new Type);
    sink (p);

    cerr << "\tclone count: " << clone_count << endl
         << endl;
  }


  cerr << "balance: " << count << endl;
}
