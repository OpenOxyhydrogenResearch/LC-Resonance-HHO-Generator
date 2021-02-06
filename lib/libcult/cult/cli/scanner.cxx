// file      : cult/cli/scanner.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/cli/scanner.hxx>

namespace Cult
{
  namespace CLI
  {
    Scanner::Action const Scanner::Action::keep (Scanner::Action::keep_);
    Scanner::Action const Scanner::Action::erase (Scanner::Action::erase_);

    Char const* const Scanner::eos = 0;
  }
}
