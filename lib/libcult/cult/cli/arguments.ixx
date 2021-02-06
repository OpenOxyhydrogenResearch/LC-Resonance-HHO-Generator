// file      : cult/cli/arguments.ixx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cassert>

namespace Cult
{
  namespace CLI
  {
    inline
    BasicArguments::
    BasicArguments (Int& argc, Char** argv)
        : argc_ (argc), argv_ (argv)
    {
      assert (argc > 0);
    }
  }
}

