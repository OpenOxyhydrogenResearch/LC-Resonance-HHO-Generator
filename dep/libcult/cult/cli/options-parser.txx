// file      : cult/cli/options-parser.txx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace Cult
{
  namespace CLI
  {
    // OptionParserBase
    //
    template <typename T>
    T OptionParserBase<T>::
    parse (Char const* o, Scanner& s)
    {
      Char const* v (s.next ());

      //@@ "expected something after --option"?
      //
      if (v == Scanner::eos)
        throw OptionFormat (o);

      T r;
      std::istringstream is (v);
      is >> r;

      if (is.fail () || !is.eof ())
        throw OptionFormat (o);

      return r;
    }
  }
}

