// file      : frontend-elements/diagnostic.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef FRONTEND_ELEMENTS_DIAGNOSTIC_HXX
#define FRONTEND_ELEMENTS_DIAGNOSTIC_HXX

#include <frontend-elements/types.hxx>

#include <ostream>
#include <sstream>

namespace FrontendElements
{
  namespace Diagnostic
  {
    struct Kind
    {
      virtual
      ~Kind ()
      {
      }

      Kind (String const& id)
          : id_ (id)
      {
      }

      Char const*
      id () const
      {
        return id_.c_str ();
      }

      virtual std::ostream&
      print (std::ostream& o) const = 0;

    private:
      String id_;
    };

    struct Error: Kind
    {
      virtual
      ~Error ()
      {
      }

      Error (String const& id)
          : Kind (id)
      {
      }

      virtual std::ostream&
      print (std::ostream& o) const
      {
        return o << "error " << id ();
      }
    };

    struct Warning: Kind
    {
      virtual
      ~Warning ()
      {
      }

      Warning (String const& id)
          : Kind (id)
      {
      }

      virtual std::ostream&
      print (std::ostream& o) const
      {
        return o << "warning " << id ();
      }
    };

    struct Remark: Kind
    {
      virtual
      ~Remark ()
      {
      }

      Remark (String const& id)
          : Kind (id)
      {
      }

      virtual std::ostream&
      print (std::ostream& o) const
      {
        return o << "remark " << id ();
      }
    };

    struct Info: Kind
    {
      virtual
      ~Info ()
      {
      }

      Info (String const& id)
          : Kind (id)
      {
      }

      virtual std::ostream&
      print (std::ostream& o) const
      {
        return o << "info " << id ();
      }
    };

    //
    //
    //
    namespace Bits
    {
      class Mediator;
    }

    class Record: public NonCopyable
    {
    public:
      Record (Kind const& kind,
              String const& file,
              UnsignedLong line,
              UnsignedLong char_)
          : kind_ (&kind),
            file_p_ (true),
            file_ (file),
            line_p_ (true),
            line_ (line),
            char_p_ (true),
            char__ (char_)
      {
      }

      Record (Kind const& kind,
              String const& file,
              UnsignedLong line)
          : kind_ (&kind),
            file_p_ (true),
            file_ (file),
            line_p_ (true),
            line_ (line),
            char_p_ (false)
      {
      }

    private:
      Record ()
          : kind_ (0),
            file_p_ (false),
            line_p_ (false),
            char_p_ (false)
      {
      }


      Void
      kind (Kind const& kind)
      {
        kind_ = &kind;
      }

      friend class Bits::Mediator;

      friend Record&
      operator<< (Bits::Mediator const&, Kind const&);

    public:
      class Undefined {};

      Kind const&
      kind () const
      {
        return *kind_;
      }

      Char const*
      file () const
      {
        if (file_p_) return file_.c_str ();

        throw Undefined ();
      }

      UnsignedLong
      line () const
      {
        if (line_p_) return line_;

        throw Undefined ();
      }

      Boolean
      char_p () const
      {
        return char_p_;
      }

      UnsignedLong
      char_ () const
      {
        if (char_p_) return char__;

        throw Undefined ();
      }

      String
      text () const
      {
        return o_.str ();
      }

    public:
      Record&
      operator<< (Char const* s)
      {
        if (!char_p_ && !line_p_ && !file_p_)
        {
          file_ = s;
          file_p_ = true;
        }
        else
          o_ << s;

        return *this;
      }

      //@@ Make it Int.
      //
      Record&
      operator<< (UnsignedLong l)
      {
        if (file_p_ && !char_p_)
        {
          if (line_p_)
          {
            char__ = l;
            char_p_ = true;
          }
          else
          {
            line_ = l;
            line_p_ = true;
          }
        }
        else
          o_ << l;

        return *this;
      }

      template <typename X>
      Record&
      operator<< (X const& x)
      {
        o_ << x;
        return *this;
      }

    private:
      Kind const* kind_;

      Boolean file_p_;
      String file_;

      Boolean line_p_;
      UnsignedLong line_;

      Boolean char_p_;
      UnsignedLong char__;

      std::ostringstream o_;
    };


    //
    //
    //
    class Log: public NonCopyable
    {
    public:
      virtual
      ~Log ()
      {
      }

    public:
      virtual Log&
      operator<< (Record const& r);

    public:
      static Log&
      instance ();
    };


    //
    //
    //
    class Stream;

    namespace Bits
    {
      class Mediator
      {
      public:
        Mediator (Stream& s)
            : s_ (s)
        {
        }

        ~Mediator ();

        Stream& s_;
        mutable Record r_;
      };
    }

    class Stream: public NonCopyable
    {
    public:
      Stream (Log& l = Log::instance ())
          : log_ (l)
      {
      }

    public:
      Stream&
      operator<< (Record const& r)
      {
        log_ << r;
        return *this;
      }

      friend Record&
      operator<< (Bits::Mediator const& m, Kind const& k)
      {
        Record& r (m.r_);

        r.kind (k);

        return r;
      }

    private:
      Log& log_;
    };

  }
}

#include <frontend-elements/diagnostic.ixx>
#include <frontend-elements/diagnostic.txx>

#endif  // FRONTEND_ELEMENTS_DIAGNOSTIC_HXX
