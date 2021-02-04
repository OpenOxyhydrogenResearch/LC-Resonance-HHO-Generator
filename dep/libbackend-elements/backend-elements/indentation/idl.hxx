// file      : backend-elements/indentation/idl.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef BACKEND_ELEMENTS_INDENTATION_IDL_HXX
#define BACKEND_ELEMENTS_INDENTATION_IDL_HXX

#include <backend-elements/types.hxx>
#include <backend-elements/indentation/buffer.hxx>

#include <cult/containers/deque.hxx>

namespace BackendElements
{
  namespace Indentation
  {
    template <typename C>
    class IDL: public Buffer<C>, public NonCopyable
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
      IDL (Buffer<C>& out)
          : out_ (out),
            indentation_ (0),
            spaces_ (2),
            construct_ (Construct::other)
      {
      }

    public:
      virtual AsInt
      put (AsChar c)
      {
        AsInt result (Traits::to_int_type (c));

        try
        {
          Boolean defaulting (false);

          switch (c)
          {
          case '\n':
            {
              hold_.push_back (c);
              break;
            }
          case '{':
            {
              ensure_new_line ();
              output_indentation ();
              result = write (c);
              ensure_new_line ();
              indentation_++;
              break;
            }
          case '}':
            {
              if (indentation_ > 0) indentation_--;

              // Reduce multiple newlines to one.
              //
              while (hold_.size () > 1)
              {
                typename Hold::ReverseIterator i (hold_.rbegin ());

                if (*i == '\n' && *(i + 1) == '\n')
                  hold_.pop_back ();
                else
                  break;
              }

              ensure_new_line ();
              output_indentation ();

              hold_.push_back (c);

              // Add double newline after '}'.
              //
              hold_.push_back ('\n');
              hold_.push_back ('\n');


              break;
            }
          case ';':
            {
              // Handling '};' case.
              //

              Boolean brace (false);

              if (hold_.size () > 1 && hold_.back () == '\n')
              {
                Boolean pop_nl (false);

                for (typename Hold::ReverseIterator
                       i (hold_.rbegin ()), e (hold_.rend ()); i != e; ++i)
                {
                  if (*i != '\n')
                  {
                    if (*i == '}')
                      brace = pop_nl = true;

                    break;
                  }
                }

                if (pop_nl)
                  while (hold_.back () == '\n')
                    hold_.pop_back ();
              }

              output_indentation ();
              result = write (c);

              if (brace)
              {
                hold_.push_back ('\n');
                hold_.push_back ('\n');
              }

              if (construct_ != Construct::string_literal &&
                  construct_ != Construct::char_literal)
              {
                ensure_new_line ();
              }
              break;
            }
          case '\\':
            {
              hold_.push_back (c);
              break;
            }
          case '\"':
            {
              if (hold_.empty () || hold_.back () != '\\')
              {
                // not escape sequence
                if (construct_ == Construct::string_literal)
                {
                  construct_ = Construct::other;
                }
                else construct_ = Construct::string_literal;
              }

              defaulting = true;
              break;
            }
          case '\'':
            {
              if (hold_.empty () || hold_.back () != '\\')
              {
                // not escape sequence
                if (construct_ == Construct::char_literal)
                {
                  construct_ = Construct::other;
                }
                else construct_ = Construct::char_literal;
              }

              defaulting = true;
              break;
            }
          default:
            {
              defaulting = true;
              break;
            }
          }

          if (defaulting)
          {
            output_indentation ();
            result = write (c);
          }
        }
        catch (Write const&)
        {
          result = Traits::eof ();
        }

        return result;
      }

      virtual Void
      unbuffer ()
      {
        AsInt result;

        while (!hold_.empty ())
        {
          result = out_.put (hold_.front ());

          //@@ failed
          if (result == Traits::eof ())
            throw Write ();

          hold_.pop_front ();
        }
      }

    private:
      Void
      ensure_new_line ()
      {
        if (hold_.empty () || hold_.back () != '\n')
          hold_.push_back ('\n');
      }


      Void
      output_indentation ()
      {
        if (!hold_.empty () && hold_.back () == '\n')
          for (UnsignedLong i (0); i < indentation_ * spaces_; ++i)
            write (' ');
      }

      AsInt
      write (AsChar c)
      {
        hold_.push_back (c);

        AsInt result (Traits::eof ());

        while (!hold_.empty ())
        {
          result = out_.put (hold_.front ());

          if (result == Traits::eof ())
            throw Write ();

          hold_.pop_front ();
        }

        return result;
      }


    private:

      Buffer<C>& out_;
      UnsignedLong indentation_;
      UnsignedLong spaces_;

      Boolean suppress_nl_;

      struct Construct
      {
        enum Value
        {
          other,
          string_literal,
          char_literal
        };
      };

      //@@ gcc bug# 18304
      //
      typename Construct::Value construct_;

      typedef
      Cult::Containers::Deque<AsInt>
      Hold;

      Hold hold_;
    };
  }
}

#include <backend-elements/indentation/idl.txx>

#endif  // BACKEND_ELEMENTS_INDENTATION_IDL_HXX
