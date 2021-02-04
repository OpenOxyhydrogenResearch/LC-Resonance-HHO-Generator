// file      : tests/indentation/cxx/driver.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2006-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <iostream>

#include <cult/types.hxx>

#include <backend-elements/indentation/cxx.hxx>
#include <backend-elements/indentation/clip.hxx>

using namespace Cult::Types;
using namespace BackendElements::Indentation;

using std::cout;
using std::endl;

Int
main ()
{
  std::ostream& os (cout);
  Clip<CXX, Char> clip (os);

  os << "if (true)"
     << "{"
     << "// Hello there" << endl
     << "//" << endl
     << "a ();"
     << "}"
     << "else"
     << "{"
     << "b ();"
     << "}";

  os << "if (false)"
     << "{"
     << "if (true)"
     << "{"
     << "// test" << endl
     << "}"
     << "else"
     << "{"
     << "// test" << endl
     << "b ();"
     << "}"
     << "}";

  os << "namespace a"
     << "{"
     << "void f ();"
     << "}"
     << "#if defined(__HP_aCC) && __HP_aCC <= 39999" << endl
     << "#include <foo.h>" << endl
     << "#endif" << endl
     << endl
     << "namespace b"
     << "{"
     << "void f ();"
     << "}";

  // Test do-while handling.
  //
  os << "do" << endl
     << "f ();"
     << "while (false);"
     << endl;

  os << "do"
     << "{"
     << "f ();"
     << "}"
     << "while (false);"
     << endl;

  os << "do"
     << "{"
     << "if (f ())"
     << "{"
     << "g ();"
     << "}"
     << "}"
     << "while (false);"
     << endl;

  os << "do"
     << "{"
     << "do" << endl
     << "f ();"
     << "while (false);"
     << "}"
     << "while (false);"
     << endl;

  os << "do"
     << "{"
     << "do"
     << "{"
     << "f ();"
     << "}"
     << "while (false);"
     << "}"
     << "while (false);"
     << endl;
}
