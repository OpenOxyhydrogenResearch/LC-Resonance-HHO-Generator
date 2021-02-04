// file      : cult/cli/options-parser.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/cli/options-parser.hxx>

namespace Cult
{
  namespace CLI
  {
    Trace::Stream OptionsParserBase::tout ("Cult::CLI::OptionsParser", 7);


    // OptionParserBooleanBase
    //
    Boolean OptionParserBooleanBase::
    parse (Char const*, Scanner&)
    {
      return true;
    }

    // OptionParserStringBase
    //
    String OptionParserStringBase::
    parse (Char const* o, Scanner& s)
    {
      Char const* v (s.next ());

      if (v == Scanner::eos)
      {
        //@@ "expected string literal after --option"?
        //
        throw OptionFormat (o);
      }

      return v;
    }
  }
}
