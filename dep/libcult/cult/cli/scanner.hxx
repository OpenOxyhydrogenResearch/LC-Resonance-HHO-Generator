// file      : cult/cli/scanner.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_CLI_SCANNER_HXX
#define CULT_CLI_SCANNER_HXX

#include <cult/types.hxx>

#include <cult/cli/exceptions.hxx>
#include <cult/cli/arguments.hxx>

namespace Cult
{
  namespace CLI
  {
    class Scanner: public NonCopyable
    {
    public:
      class Action
      {
      public:
        static Action const keep, erase;

        friend Boolean
        operator== (Action const& a, Action const& b)
        {
          return a.v_ == b.v_;
        }

        friend Boolean
        operator!= (Action const& a, Action const& b)
        {
          return a.v_ != b.v_;
        }

      private:
        enum Value { keep_, erase_ } v_;

        Action (Value v)
            : v_ (v)
        {
        }
      };

    public:
      Scanner (Arguments& args, Action a = Action::keep, Index start = 1)
          : cargs_ (args),
            args_ (a == Action::erase ? &args : 0),
            next_ (start)
      {
      }

      Scanner (Arguments const& args, Index start = 1)
          : cargs_ (args), args_ (0), next_ (start)
      {
      }

    public:
      static Char const* const eos;

      class PastEOS: public virtual Exception {};

      Char const*
      next ()
      {
        if (next_ > cargs_.size ())
        {
          throw PastEOS ();
        }
        else if (next_ == cargs_.size ())
        {
          ++next_;
          return eos;
        }
        else
        {
          Char const* r (cargs_[next_]);

          if (args_ != 0)
          {
            hold_ = r;
            args_->erase (next_);
            return hold_.c_str ();
          }
          else
          {
            ++next_;
            return r;
          }
        }
      }

      Char const*
      peek ()
      {
        if (next_ > cargs_.size ())
        {
          throw PastEOS ();
        }
        else if (next_ == cargs_.size ())
        {
          return eos;
        }
        else
        {
          return cargs_[next_];
        }
      }

      Void
      skip ()
      {
        if (next_ > cargs_.size ())
          throw PastEOS ();
        else
          ++next_;
      }

    private:
      Arguments const& cargs_;
      Arguments* args_;
      Index next_;
      String hold_;
    };
  }
}

#include <cult/cli/scanner.ixx>

#endif  // CULT_CLI_SCANNER_HXX
