// file      : examples/cli/cli.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/types.hxx>

#include <cult/cli/options.hxx>
#include <cult/cli/options-spec.hxx>
#include <cult/cli/options-parser.hxx>

#include <iostream>

using std::cerr;
using std::endl;

using namespace Cult;

namespace
{
  extern Char const help[] = "help";
  extern Char const version[] = "version";
  extern Char const outdir[] = "outdir";
}

typedef
CLI::Options<help, Boolean,
             version, Boolean,
             outdir, String>
Options;

Int
main (Int argc, Char* argv[])
{
  try
  {
    Options options (CLI::parse<Options> (argc, argv));

    if (options.value<help> ())
    {
      cerr << "usage: " << argv[0] << " [--help] [--version] [--outdir <dir>]"
           << endl;
      return 0;
    }

    if (options.value<version> ())
    {
      cerr << argv[0] << " 1.2.3" << endl;
      return 0;
    }

    if (String dir = options.value<outdir> ())
    {
      cerr << "outdir: " << dir << endl;
    }
  }
  catch (CLI::UnexpectedOption const& e)
  {
    cerr << "unexpected option " << e.option () <<endl;
  }
  catch (CLI::OptionFormat const& e)
  {
    cerr << "bad format for " << e.option () << endl;
  }
}
