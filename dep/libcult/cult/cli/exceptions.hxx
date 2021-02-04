// file      : cult/cli/exceptions.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_CLI_EXCEPTIONS_HXX
#define CULT_CLI_EXCEPTIONS_HXX

#include <cult/types.hxx>

#include <cult/eh/exception.hxx>

namespace Cult
{
  namespace CLI
  {
    //
    //
    class Exception: public virtual EH::Exception
    {
    };

    // Exception for FileArguments class.
    //
    class OptionFile: public virtual Exception
    {
    public:
      ~OptionFile () throw ()
      {
      }

      OptionFile (String const& description)
          : description_ (description)
      {
      }

      OptionFile (String const& value,
                  String const& description)
          : value_ (value), description_ (description)
      {
      }

      String const&
      value () const
      {
        return value_;
      }

      String const&
      description () const
      {
        return description_;
      }

    private:
      String value_;
      String description_;
    };

    //
    //
    class UnexpectedOption: public virtual Exception
    {
    public:
      ~UnexpectedOption () throw ()
      {
      }

      UnexpectedOption (String const& option)
          : option_ (option)
      {
      }

      String const&
      option () const
      {
        return option_;
      }

    private:
      String option_;
    };


    //
    //
    class UnexpectedArgument: public virtual Exception
    {
    public:
      ~UnexpectedArgument () throw ()
      {
      }

      UnexpectedArgument (String const& argument)
          : argument_ (argument)
      {
      }

      String const&
      argument () const
      {
        return argument_;
      }

    private:
      String argument_;
    };


    //
    //
    class OptionFormat: public virtual Exception
    {
    public:
      ~OptionFormat () throw ()
      {
      }

      OptionFormat (String const& option)
          : option_ (option)
      {
      }

      String const&
      option () const
      {
        return option_;
      }

    private:
      String option_;
    };
  }
}

#endif  // CULT_CLI_EXCEPTIONS_HXX
