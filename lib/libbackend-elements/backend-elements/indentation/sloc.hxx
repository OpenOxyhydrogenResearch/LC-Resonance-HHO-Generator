// file      : backend-elements/indentation/sloc.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef BACKEND_ELEMENTS_INDENTATION_SLOC_HXX
#define BACKEND_ELEMENTS_INDENTATION_SLOC_HXX

#include <backend-elements/types.hxx>
#include <backend-elements/indentation/buffer.hxx>

#include <cctype>
#include <iostream> //@@ tmp

namespace BackendElements
{
  namespace Indentation
  {
    template <typename C>
    class SLOC: public Buffer<C>/*, public NonCopyable*/
    {
    public:
      typedef
      typename Buffer<C>::Traits
      Traits;

      typedef
      typename Buffer<C>::AsChar
      AsChar;

      typedef
      typename Buffer<C>::AsInt
      AsInt;

      typedef
      typename Buffer<C>::Write
      Write;

    public:
      SLOC (Buffer<C>& out)
          : out_ (out),
            count_ (0),
            prev_ ('\0'),
            code_counted_ (false),
            construct_ (Construct::code)
      {
      }

      UnsignedLong
      count () const
      {
        return count_;
      }

    public:
      virtual AsInt
      put (AsChar c)
      {
        typename Construct::Value old (construct_);

        switch (construct_)
        {
        case Construct::code:
          {
            code (c);
            break;
          }
        case Construct::c_comment:
          {
            c_comment (c);
            break;
          }
        case Construct::cxx_comment:
          {
            cxx_comment (c);
            break;
          }
        case Construct::char_literal:
          {
            char_literal (c);
            break;
          }
        case Construct::string_literal:
          {
            string_literal (c);
            break;
          }
        }

        // There are cases when a previous character has been already
        // 'used' and therefore can not be used again. Good example
        // would be '/* *//'. Here, the second slash doesn't start
        // C++ comment since it was already used by C comment.
        //
        // To account for this we are going to set prev_ to '\0' when
        // the mode changes.
        //

        prev_ = (old == construct_) ? c : '\0';

        return out_.put (c);
      }

      virtual Void
      unbuffer ()
      {
      }

    private:
      Void
      code (AsChar c)
      {
        bool count (true);

        switch (c)
        {
        case '/':
          {
            if (prev_ == '/')
            {
              construct_ = Construct::cxx_comment;
              count = false;
            }
            else
            {
              // This slash can be a beginning of a comment but we
              // yet have no way to know. Will have to examine it later
              // (see below).
              //
              count = false;
            }

            break;
          }
        case '*':
          {
            if (prev_ == '/')
            {
              construct_ = Construct::c_comment;
              count = false;
            }
            break;
          }
        case '\'':
          {
            construct_ = Construct::char_literal;
            break;
          }
        case '"':
          {
            construct_ = Construct::string_literal;
            break;
          }
        case '\n':
          {
            code_counted_ = false; // reset for a new line
            count = false;
            break;
          }
        default:
          {
            if (std::isspace (c))
              count = false;
            break;
          }
        }

        // The second condition here accounts for the fact that we cannot
        // count '/' right away since it can be a beginning of a comment.
        //
        if (!code_counted_ &&
            (count || (prev_ == '/' && construct_ == Construct::code)))
        {
          //std::wcerr << "detected code @ " << c << std::endl;
          count_++;
          code_counted_ = true;
        }
      }

      Void
      c_comment (AsChar c)
      {
        switch (c)
        {
        case '/':
          {
            if (prev_ == '*')
              construct_ = Construct::code;
            break;
          }
        case '\n':
          {
            code_counted_ = false; // reset for a new line
            break;
          }
        }
      }

      Void
      cxx_comment (AsChar c)
      {
        switch (c)
        {
        case '\n':
          {
            construct_ = Construct::code;
            code_counted_ = false; // reset for a new line
            break;
          }
        }
      }

      Void
      char_literal (AsChar c)
      {
        switch (c)
        {
        case '\'':
          {
            if (prev_ != '\\')
              construct_ = Construct::code;
            break;
          }
        }
      }

      Void
      string_literal (AsChar c)
      {
        switch (c)
        {
        case '"':
          {
            if (prev_ != '\\')
              construct_ = Construct::code;
            break;
          }
        case '\n':
          {
            /*@@ Should I count multi-line string literal as multiple SLOC? */
            break;
          }
        }
      }

    private:
      Buffer<C>& out_;
      UnsignedLong count_;

      AsChar prev_; // previous character or '\0'

      struct Construct
      {
        enum Value
        {
          code,
          c_comment,
          cxx_comment,
          char_literal,
          string_literal
        };
      };

      // code
      //
      bool code_counted_;

      //@@ gcc bug# 18304
      //
      typename Construct::Value construct_;
    };
  }
}

//#include <backend-elements/indentation/sloc.txx>

#endif  // BACKEND_ELEMENTS_INDENTATION_SLOC_HXX
