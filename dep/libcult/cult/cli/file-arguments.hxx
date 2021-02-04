// file      : cult/cli/file-arguments.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_CLI_FILE_ARGUMENTS_HXX
#define CULT_CLI_FILE_ARGUMENTS_HXX

#include <cult/types.hxx>
#include <cult/containers/vector.hxx>

#include <cult/cli/exceptions.hxx>
#include <cult/cli/arguments.hxx>

namespace Cult
{
  namespace CLI
  {
    class FileArguments: public Arguments
    {
    public:
      virtual
      ~FileArguments ();

      FileArguments (Int argc,
                     Char const* const* argv,
                     Char const* file_option);
    public:
      virtual Size
      size () const
      {
        return args_.size ();
      }

      virtual Char const*
      operator[] (Index i) const
      {
        if (i >= size ())
          throw Bounds ();

        return args_[i].c_str ();
      }

      virtual Void
      erase (Index i)
      {
        if (i >= size ())
          throw Bounds ();

        args_.erase (args_.begin () + i);
      }

    private:
      Containers::Vector<String> args_;
    };
  }
}

#endif  // CULT_CLI_FILE_ARGUMENTS_HXX
