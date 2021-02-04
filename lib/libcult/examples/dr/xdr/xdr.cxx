// file      : examples/dr/xdr/xdr.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/types.hxx>

#include <cult/dr/xdr/input-stream.hxx>
#include <cult/dr/xdr/output-stream.hxx>

#include <iostream>

using namespace Cult;
using namespace DR::XDR;

using std::cerr;
using std::endl;

Int
main ()
{
  try
  {
    OutputStream o (8);

    o << true << false;

    UnsignedInt8 a8 (0xDE);
    UnsignedInt16 a16 (0xDEAD);
    UnsignedInt32 a32 (0xDEADBEEF);
    UnsignedInt64 a64 (0xDEADBEEFDEADBEEFULL);

    o << a8 << a16 << a32 << a64;

    Int8 b8 (-8);
    Int16 b16 (-16);
    Int32 b32 (-32);
    Int64 b64 (-64);

    o << b8 << b16 << b32 << b64;

    String s ("reasonably loooooooooooooong string with some junk in it");

    o << s;

    InputStream i (o.buffer ());

    Boolean t, f;
    String s1;

    i >> t >> f;
    i >> a8 >> a16 >> a32 >> a64;
    i >> b8 >> b16 >> b32 >> b64;
    i >> s1;

    if (!t
        || f
        || a8 != 0xDE
        || a16 != 0xDEAD
        || a32 != 0xDEADBEEF
        || a64 != 0xDEADBEEFDEADBEEFULL
        || b8 != -8
        || b16 != -16
        || b32 != -32
        || b64 != -64
        || s1 != s) return 1;

    try
    {
      i >> t;
    }
    catch (Extraction const&)
    {
      return 0;
    }
  }
  catch (Insertion const&)
  {
    cerr << "insertion" << endl;
  }
  catch (Extraction const&)
  {
    cerr << "extraction" << endl;
  }

  return 1;
}
