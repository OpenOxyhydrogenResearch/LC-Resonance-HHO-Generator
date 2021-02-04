// file      : cult/cli/arguments.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_CLI_ARGUMENTS_HXX
#define CULT_CLI_ARGUMENTS_HXX

#include <cult/types.hxx>

#include <cult/cli/exceptions.hxx>

namespace Cult
{
  namespace CLI
  {
    class Arguments: public NonCopyable
    {
    public:
      virtual
      ~Arguments ();

    public:
      class Bounds: public virtual Exception {};

      virtual Size
      size () const = 0;

      virtual Char const*
      operator[] (Index) const = 0;

      virtual Void
      erase (Index) = 0;
    };

    class BasicArguments: public Arguments
    {
    public:
      virtual
      ~BasicArguments ();

      BasicArguments (Int& argc, Char** argv);

    public:
      virtual Size
      size () const
      {
        return static_cast<Size> (argc_);
      }

      virtual Char const*
      operator[] (Index i) const
      {
        if (i >= size ())
          throw Bounds ();

        return argv_[i];
      }

      virtual Void
      erase (Index i)
      {
        if (i >= size ())
          throw Bounds ();

        for (++i; i < size (); ++i)
        {
          argv_[i - 1] = argv_[i];
        }

        --argc_;

        argv_[argc_] = 0;
      }

    private:
      Int& argc_;
      Char** argv_;
    };
  }
}

#include <cult/cli/arguments.ixx>

#endif  // CULT_CLI_ARGUMENTS_HXX
