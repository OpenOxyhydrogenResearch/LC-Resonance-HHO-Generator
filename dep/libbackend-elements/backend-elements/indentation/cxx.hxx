// file      : backend-elements/indentation/cxx.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef BACKEND_ELEMENTS_INDENTATION_CXX_HXX
#define BACKEND_ELEMENTS_INDENTATION_CXX_HXX

#include <backend-elements/types.hxx>
#include <backend-elements/indentation/buffer.hxx>

#include <cult/containers/set.hxx>
#include <cult/containers/stack.hxx>
#include <cult/containers/deque.hxx>

#include <locale>

// #include <iostream> // @@ tmp

namespace BackendElements
{
  namespace Indentation
  {
    template <typename C>
    class CXX: public Buffer<C>/*, public NonCopyable*/
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
      CXX (Buffer<C>& out)
          : out_ (out),
            buffering_ (false),
            position_ (0),
            paren_balance_ (0),
            spaces_ (2),
            construct_ (Construct::other),
            lbrace_ ("{"),
            rbrace_ ("}")
        // locale_ ("C")
      {
        indentation_.push (0);

        single_line_blocks_.insert ("if");
        single_line_blocks_.insert ("do");
        single_line_blocks_.insert ("for");
        single_line_blocks_.insert ("else");
        single_line_blocks_.insert ("case");
        single_line_blocks_.insert ("while");

        follow_blocks_.insert ("else");
        follow_blocks_.insert ("case");
        follow_blocks_.insert ("catch");
        follow_blocks_.insert ("default");
      }

    public:
      virtual AsInt
      put (AsChar c)
      {
        AsInt result (Traits::to_int_type (c));

        try
        {
          // First determine what kind of construct we are in.
          //
          typename Construct::Value new_construct (construct_);
          typename Construct::Value old_construct (construct_);

          switch (c)
          {
          case '\n':
            {
              if (construct_ == Construct::pp_directive ||
                  construct_ == Construct::cxx_comment)
                construct_ = new_construct = Construct::other;

              break;
            }
          case '#':
            {
              if (construct_ == Construct::other)
                construct_ = new_construct = Construct::pp_directive;

              break;
            }
          case '\"':
            {
              if (construct_ != Construct::pp_directive &&
                  construct_ != Construct::c_comment &&
                  construct_ != Construct::cxx_comment &&
                  construct_ != Construct::char_literal)
              {
                // We might be in an escape sequence.
                //
                Boolean es (!hold_.empty () && hold_.back () == '\\');

                if (es)
                {
                  // Scan the hold sequence backwards to figure out if this
                  // backslash is part of this escape sequence or a preceding
                  // one.
                  //
                  for (typename Hold::ReverseIterator i (hold_.rbegin () + 1),
                         e (hold_.rend ()); i != e && *i == '\\'; ++i)
                    es = !es;
                }

                if (!es)
                {
                  // Not an escape sequence.
                  //
                  if (construct_ == Construct::string_literal)
                    new_construct = Construct::other;
                  else
                    construct_ = new_construct = Construct::string_literal;
                }
              }

              break;
            }
          case '\'':
            {
              if (construct_ != Construct::pp_directive &&
                  construct_ != Construct::c_comment &&
                  construct_ != Construct::cxx_comment &&
                  construct_ != Construct::string_literal)
              {
                // We might be in an escape sequence.
                //
                Boolean es (!hold_.empty () && hold_.back () == '\\');

                if (es)
                {
                  // Scan the hold sequence backwards to figure out if this
                  // backslash is part of this escape sequence or a preceding
                  // one.
                  //
                  for (typename Hold::ReverseIterator i (hold_.rbegin () + 1),
                         e (hold_.rend ()); i != e && *i == '\\'; ++i)
                    es = !es;
                }

                if (!es)
                {
                  if (construct_ == Construct::char_literal)
                    new_construct = Construct::other;
                  else
                    construct_ = new_construct = Construct::char_literal;
                }
              }

              break;
            }
          case '/':
            {
              if (construct_ == Construct::other)
              {
                if (!hold_.empty () && hold_.back () == '/')
                  construct_ = new_construct = Construct::cxx_comment;
              }

              if (construct_ == Construct::c_comment)
              {
                if (!hold_.empty () && hold_.back () == '*')
                  construct_ = new_construct = Construct::other;
              }

              break;
            }
          case '*':
            {
              if (construct_ == Construct::other)
              {
                if (!hold_.empty () && hold_.back () == '/')
                  construct_ = new_construct = Construct::c_comment;
              }

              break;
            }
          default:
            {
              break;
            }
          }

          // Special handling of CPP directives.
          //
          if (construct_ == Construct::pp_directive)
          {
            result = write (c);
            position_++;
            return result;
          }

          //
          //
          tokenize (c, old_construct);


          // Indentation in parenthesis. We don't need to make sure
          // we are not in a comments, etc. because we make sure we
          // don't hold anything in those states.
          //
          if (!hold_.empty () && hold_.back () == '(')
          {
            unbuffer (); // We don't need to hold it anymore.

            if (c == '\n')
              indentation_.push (indentation_.top () + spaces_);
            else
              indentation_.push (position_);
          }


          //
          //
          Boolean defaulting (false);

          switch (c)
          {
          case '\n':
            {
              if (!indent_block_.empty () && construct_ == Construct::other)
                indent_block_.top ().newline_ = true;

              hold_.push_back (c);
              position_ = 0; // Starting a new line.

              break;
            }
          case '{':
            {
              if (construct_ == Construct::other)
              {
                if (!indent_block_.empty ())
                {
                  // Pop all the blocks until the one that was indented.
                  //
                  while (!indent_block_.top ().indented_)
                    indent_block_.pop ();

                  if (indentation_.size () > 1)
                    indentation_.pop ();

                  indent_block_.pop ();
                }

                ensure_new_line ();
                output_indentation ();
                result = write (c);
                ensure_new_line ();

                indentation_.push (indentation_.top () + spaces_);
              }
              else
                defaulting = true;

              break;
            }
          case '}':
            {
              if (construct_ == Construct::other)
              {
                if (indentation_.size () > 1)
                  indentation_.pop ();

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
                position_ = 0;

                buffering_ = true;
              }
              else
                defaulting = true;

              break;
            }
          case ';':
            {
              if (construct_ == Construct::other)
              {
                // for (;;)
                //
                if (!indent_block_.empty () && paren_balance_ == 0)
                {
                  // Pop all the blocks until the one that was indented.
                  //
                  while (!indent_block_.top ().indented_)
                    indent_block_.pop ();

                  if (indentation_.size () > 1)
                    indentation_.pop ();

                  indent_block_.pop ();
                }

                if (paren_balance_ != 0)
                {
                  // We are inside for (;;) statement. Nothing to do here.
                  //
                  defaulting = true;
                }
                else
                {
                  // Handling '};' case.
                  //

                  Boolean brace (false);

                  if (hold_.size () > 1 && hold_.back () == '\n')
                  {
                    Boolean pop_nl (false);

                    for (typename Hold::ReverseIterator
                           i (hold_.rbegin ()), e (hold_.rend ());
                         i != e; ++i)
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
                  position_++;

                  if (brace)
                  {
                    hold_.push_back ('\n');
                    hold_.push_back ('\n');
                  }

                  ensure_new_line ();
                }
              }
              else
                defaulting = true;

              break;
            }
          case ' ':
            {
              if (construct_ == Construct::other)
              {
                // Handling '} foo_;' case.
                //
                if (hold_.size () > 1 && hold_.back () == '\n')
                {
                  Boolean pop_nl (false);

                  for (typename Hold::ReverseIterator
                         i (hold_.rbegin ()), e (hold_.rend ());
                       i != e; ++i)
                  {
                    if (*i != '\n')
                    {
                      if (*i == '}')
                        pop_nl = true;

                      break;
                    }
                  }

                  if (pop_nl)
                    while (hold_.back () == '\n')
                      hold_.pop_back ();
                }
              }

              defaulting = true;
              break;
            }
          case '\\':
            {
              if (construct_ != Construct::pp_directive &&
                  construct_ != Construct::c_comment &&
                  construct_ != Construct::cxx_comment)
              {
                output_indentation ();
                hold_.push_back (c);
                position_++;
              }
              else
                defaulting = true;

            break;

            }
          case '(':
            {
              if (construct_ == Construct::other)
              {
                // Hold it so that we can see what's coming next.
                //
                output_indentation ();
                hold_.push_back (c);
                position_++;
                paren_balance_++;
              }
              else
                defaulting = true;
              break;
            }
          case ')':
            {
              if (construct_ == Construct::other)
              {
                if (indentation_.size () > 1)
                  indentation_.pop ();

                if (paren_balance_ > 0)
                  paren_balance_--;
              }

              defaulting = true;
              break;
            }
          case '/':
            {
              if (construct_ == Construct::other)
              {
                output_indentation ();
                hold_.push_back (c);
                position_++;
              }
              else
                defaulting = true;

              break;
            }
          case '*':
            {
              if (construct_ == Construct::c_comment)
              {
                output_indentation ();
                hold_.push_back (c);
                position_++;
              }
              else
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
            position_++;
          }

          construct_ = new_construct;
        }
        catch (Write const&)
        {
          result = Traits::eof ();
        }

        return result;
      }

    private:
      typedef Cult::StringTemplate<C> String;

      Void
      next_token (String const& old, AsChar c)
      {
        //std::cerr << "next token: " << token_
        //          << "; old token: " << old << std::endl;

        // Handle one line indentation blocks (if, else, etc).
        //
        if (single_line_blocks_.find (token_) != single_line_blocks_.end ())
        {
          // Only indent sub-blocks if we are on a new line.
          //
          Boolean indent (indent_block_.empty () ||
                          indent_block_.top ().newline_);

          indent_block_.push (IndentBlockInfo (c == '\n', indent));

          if (indent)
            indentation_.push (indentation_.top () + spaces_);
        }

        // Keep track of the do ... while construct in order to suppress
        // the newline after } and before while.
        //
        if (old == String ("do") && token_ == lbrace_)
        {
          do_while_state_.push (0);
        }

        if (!do_while_state_.empty ())
        {
          if (token_ == lbrace_)
            do_while_state_.top ()++;

          if (token_ == rbrace_)
            do_while_state_.top ()--;
        }

        // Suppress double newline in the "}else", etc., cases.
        //
        if (old == rbrace_)
        {
          Boolean dw (!do_while_state_.empty () &&
                      do_while_state_.top () == 0);

          if (follow_blocks_.find (token_) != follow_blocks_.end () || dw)
          {
            if (dw)
              do_while_state_.pop ();

            // Reduce double newline after "}" into a single one.
            //
            typename Hold::Iterator i (hold_.end ()), b (hold_.begin ());

            for (--i; i != b; --i)
            {
              // See if this is the end of the "}\n\n" sequence.
              //
              if (*i == '\n')
              {
                --i;
                if (i != b && *i == '\n')
                {
                  --i;
                  if (*i == '}')
                  {
                    ++i;
                    hold_.erase (i);
                    break;
                  }
                }
              }
            }
          }
          else if (token_ != rbrace_)
          {
            buffering_ = false;
          }
        }
      }

    public:
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
        {
          hold_.push_back ('\n');
          position_ = 0; // Starting a new line.
        }
      }


      Void
      output_indentation ()
      {
        if (!hold_.empty () && hold_.back () == '\n')
        {
          for (UnsignedLong i (0); i < indentation_.top (); ++i)
            write (' ');

          position_ += indentation_.top ();
        }
      }

      AsInt
      write (AsChar c)
      {
        hold_.push_back (c);

        if (!buffering_)
        {
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
        else
          return c;
      }

    private:
      struct Construct
      {
        enum Value
        {
          other,
          pp_directive,
          c_comment,
          cxx_comment,
          string_literal,
          char_literal
        };
      };

      Void
      tokenize (AsChar c, typename Construct::Value old)
      {
        //
        //
        switch (construct_)
        {
        case Construct::pp_directive:
          {
            if (old == Construct::other) // Start PP directive
              retire (c);

            return;
          }
        case Construct::c_comment:
          {
            if (old == Construct::other) // Start C comment.
              lexeme_.clear ();

            return;
          }
        case Construct::cxx_comment:
          {
            if (old == Construct::other) // Start C++ comment.
              lexeme_.clear ();

            return;
          }
        case Construct::string_literal:
          {
            if (old == Construct::other) // Start string literal
              retire (c);

            lexeme_ += c;
            return;
          }
        case Construct::char_literal:
          {
            if (old == Construct::other) // Start char literal
              retire (c);

            lexeme_ += c;
            return;
          }
        default:
          break;
        }

        // construct_ == other
        //
        switch (old)
        {
        case Construct::pp_directive:
          {
            // End  PP directive (newline).
            //
            return;
          }
        case Construct::c_comment:
          {
            // End  C comment.
            //
            return;
          }
        case Construct::cxx_comment:
          {
            // End  C++ comment (newline).
            //
            return;
          }
        case Construct::string_literal:
          {
            // End string literal (").
            //
            lexeme_ += c;
            return;
          }
        case Construct::char_literal:
          {
            // End char literal (').
            //
            lexeme_ += c;
            return;
          }
        default:
          break;
        }


        // construct_ == old == other
        //

        /*

        The code below is equivalent to this (simpler) code which is
        unfortunately not fast enough.

        using std::isalpha;
        using std::isalnum;
        using std::isdigit;
        using std::isspace;

        if (c == '_' || isalpha (c, locale_))
        {
          if (lexeme_.empty () ||
              lexeme_[0] == '_' || isalpha (lexeme_[0], locale_))
            lexeme_ += c;
          else
          {
            retire (c);
            lexeme_ += c;
          }
        }
        else if (isdigit (c, locale_))
        {
          if (lexeme_.empty () ||
              lexeme_[0] == '_' || isalnum (lexeme_[0], locale_))
            lexeme_ += c;
          else
          {
            retire (c);
            lexeme_ += c;
          }
        }
        else // Delimiters
        {
          retire (c);

          if (!isspace (c, locale_))
            lexeme_ += c;
        }
        */

        switch (char_class (c))
        {
        case CharClass::alpha:
          {
            if (lexeme_.empty () ||
                char_class (lexeme_[0]) == CharClass::alpha)
              lexeme_ += c;
            else
            {
              retire (c);
              lexeme_ += c;
            }
            break;
          }
        case CharClass::digit:
          {
            if (lexeme_.empty ())
              lexeme_ += c;
            else
            {
              typename CharClass::Value cc (char_class (lexeme_[0]));

              if (cc == CharClass::alpha || cc == CharClass::digit)
                lexeme_ += c;
              else
              {
                retire (c);
                lexeme_ += c;
              }
            }
            break;
          }
        case CharClass::op_punc:
          {
            retire (c);
            lexeme_ += c;
            break;
          }
        case CharClass::space:
          {
            retire (c);
            break;
          }
        }
      }

      struct CharClass
      {
        enum Value
        {
          alpha,   // Alpha + '_'.
          digit,
          op_punc, // Operator or punctuation.
          space
        };

      };

      typename CharClass::Value
      char_class (C c)
      {
        switch (c)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
          return CharClass::digit;

        case '!':
        case '%':
        case '^':
        case '&':
        case '*':
        case '(':
        case ')':
        case '-':
        case '+':
        case '=':
        case '{':
        case '}':
        case '|':
        case '~':
        case '[':
        case ']':
        case '\\':
        case ';':
        case '\'':
        case ':':
        case '"':
        case '<':
        case '>':
        case '?':
        case ',':
        case '.':
        case '/':
          return CharClass::op_punc;

        case ' ':
        case '\n':
        case '\t':
        case '\f':
        case '\r':
        case '\v':
          return CharClass::space;

        default:
          return CharClass::alpha;
        }
      }


      Void
      retire (AsChar c)
      {
        if (!lexeme_.empty ())
        {
          token_.swap (lexeme_);
          next_token (lexeme_, c);
          lexeme_.clear ();
        }
      }

    private:
      Buffer<C>& out_;
      Boolean buffering_; // True if write() should buffer the char.
      UnsignedLong position_; // Current position on the line.
      UnsignedLong paren_balance_; // ( ) balance.
      Cult::Containers::Stack<UnsignedLong> indentation_;
      UnsignedLong spaces_;

      Boolean suppress_nl_;

      //@@ gcc bug# 18304
      //
      typename Construct::Value construct_;

      // Special state stach for the do-while construct. The presence
      // of an element in the stack indicates that we are in a braced
      // do-while construct. The value of the element is the brace
      // balance.
      Cult::Containers::Stack<UnsignedLong> do_while_state_;

      typedef
      Cult::Containers::Deque<AsInt>
      Hold;

      Hold hold_;

    private:
      String token_;  // previously fully recognized token
      String lexeme_; // current lexeme (accumulator)

      // std::locale locale_;

      // Keywords that may be folowed by a single-line block, e.g., if,
      // else, etc.
      //
      Cult::Containers::Set<String> single_line_blocks_;

      // Keywords that may follow (and be related) to a previous block,
      // e.g., else, case, catch.
      //
      Cult::Containers::Set<String> follow_blocks_;

      String lbrace_;
      String rbrace_;

    private:
      // Single-line indented blocks such as if, else, while, etc. The
      // newline flag indicates whether a new line has been seen after
      // the keyword. This is needed to properly distinguish cases such
      // as:
      //
      // else if (...)
      //   foo ();
      //
      // else
      //   if (...)
      //     foo ();
      //
      struct IndentBlockInfo
      {
        IndentBlockInfo (Boolean newline, Boolean indented)
            : newline_ (newline), indented_ (indented)
        {
        }

        Boolean newline_;
        Boolean indented_;
      };

      Cult::Containers::Stack<IndentBlockInfo> indent_block_;
    };
  }
}

#include <backend-elements/indentation/cxx.txx>

#endif  // BACKEND_ELEMENTS_INDENTATION_CXX_HXX
