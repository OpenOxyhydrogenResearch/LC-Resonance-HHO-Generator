// file      : cult/mm/bits/evptr.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_MM_BITS_EVPTR_HXX
#define CULT_MM_BITS_EVPTR_HXX

#include <cult/types/fundamental.hxx>

#include <cult/meta/answer.hxx>

#include <cult/mm/counter.hxx>
#include <cult/mm/exception.hxx>

#include <cassert> // assert

namespace Cult
{
  namespace MM
  {

    //@@ Should be in mm/evptr.hxx
    //
    struct Clone: virtual Exception {};

    template <typename X>
    class Evptr;

    namespace Bits
    {
      template <typename x, Evptr<x> (x::*f) () const = &x::clone>
      struct Helper;

      //@@ Should be generalized and moved to Cult::meta
      //
      template <typename X>
      struct has_clone
      {
        template <typename y>
        static Meta::Yes
        test (Helper<y>*);

        template <typename>
        static Meta::No
        test (...);

        static Boolean const r = sizeof (test<X> (0)) == sizeof (Meta::Yes);
      };

      //@@ Need to incorporate tests for polymorpism and NonCopyable.
      //

      template <typename X, Boolean = has_clone<X>::r>
      struct Cloner;

      template <typename X>
      struct Cloner<X, true>
      {
        static X*
        clone (X const* cp)
        {
          return cp->clone ().release ();
        }
      };

      template <typename X>
      struct Cloner<X, false>
      {
        static X*
        clone (X const*)
        {
          throw MM::Clone ();
        }
      };
    }

    namespace Bits
    {
      template <typename X>
      class Transfer;
    }

    namespace Bits
    {
      template <typename X>
      class EvptrBase
      {
      protected:
        ~EvptrBase ()
        {
          free (p_ ? p_ : cp_, c_);
        }

        EvptrBase (X* p, X const* cp, Counter* c, Boolean inc = true)
            : p_ (p), cp_ (cp), c_ (c)
        {
          assert (!(p_ != 0 && cp_ != 0));

          if (cp_ != 0 && c_ && inc) c_->inc_ref ();
        }

      public:
        X*
        get () const
        {
          return get_ ();
        }

        X*
        release ()
        {
          X* p (get_ ());

          c_ = 0;
          p_ = 0;
          cp_ = 0;

          return p;
        }

        Size
        count () const
        {
          if (c_ == 0) throw NullPointer ();
          return c_->count ();
        }

      public:
        // Conversion to Boolean.
        //
        typedef X* (EvptrBase::*BooleanConvertible)() const;

        operator BooleanConvertible () const
        {
          return c_ ? &EvptrBase::get : 0;
        }

      protected:
        Void
        assign (X const* cp, Counter* c)
        {
          if (c_ && c_ == c) throw SelfAssignment ();

          free (p_ ? p_ : cp_, c_);

          if (c) c->inc_ref ();

          c_ = c;
          p_ = 0;
          cp_ = cp;
        }

        Void
        transfer (X* p, X const* cp, Counter* c)
        {
          free (p_ ? p_ : cp_, c_);

          c_ = c;
          p_ = p;
          cp_ = cp;
        }

      protected:
        X*
        get_ () const
        {
          if (c_ == 0) return 0;

          assert (p_ != 0 || cp_ != 0);

          if (p_ != 0)
          {
            if (c_->count () == 1) return p_;
            else
            {
              // Convert to shared case.
              //
              cp_ = p_;
              p_ = 0;
            }
          }

          // Shared case with cloning.
          //

          // Check if we are the sole owner.
          //
          if (c_->count () == 1)
          {
            // Convert to exclusive case.
            //
            p_ = const_cast<X*> (cp_);
            cp_ = 0;
          }
          else
          {
            assert (cp_ != 0);

            //p_ = cp_->clone ().release ();

            p_ = Cloner<X>::clone (cp_);

            free (cp_, c_);

            cp_ = 0;
            c_ = locate (p_, *counted);
          }

          return p_;
        }

        static Void
        free (X const* p, Counter* c)
        {
          if (c && c->dec_ref ())
          {
            assert (p != 0);
            delete p;
          }
        }

      private:
        template <typename>
        friend class Evptr;

        template <typename>
        friend class Transfer;

        mutable X* p_;
        mutable X const* cp_;
        mutable Counter* c_;
      };


      template <typename X>
      class EvptrBase<X const>
      {
      protected:
        ~EvptrBase ()
        {
          free (p_ ? p_ : cp_, c_);
        }

        EvptrBase (X const* p, X const* cp, Counter* c, Boolean inc = true)
            : p_ (p), cp_ (cp), c_ (c)
        {
          assert (!(p_ != 0 && cp_ != 0));

          if (cp_ != 0 && c_ && inc) c_->inc_ref ();
        }

      public:
        X const*
        get ()
        {
          return get_ ();
        }

        //@@ Should clone if shared?
        //
        X const*
        release ()
        {
          X const* p (get_ ());

          c_ = 0;
          p_ = 0;
          cp_ = 0;

          return p;
        }

        Size
        count () const
        {
          if (c_ == 0) throw NullPointer ();
          return c_->count ();
        }

      public:
        // Conversion to Boolean.
        //
        typedef X const* (EvptrBase::*BooleanConvertible)() const;

        operator BooleanConvertible () const
        {
          return c_ ? &EvptrBase::get : 0;
        }

      protected:
        Void
        assign (X const* cp, Counter* c)
        {
          if (c_ && c_ == c) throw SelfAssignment ();

          free (p_ ? p_ : cp_, c_);

          if (c) c->inc_ref ();

          c_ = c;
          p_ = 0;
          cp_ = cp;
        }

        Void
        transfer (X const* p, X const* cp, Counter* c)
        {
          free (p_ ? p_ : cp_, c_);

          c_ = c;
          p_ = p;
          cp_ = cp;
        }

      protected:
        X const*
        get_ () const
        {
          return p_ ? p_ : cp_;
        }

        static Void
        free (X const* p, Counter* c)
        {
          if (c && c->dec_ref ())
          {
            assert (p != 0);
            delete p;
          }
        }

      private:
        template <typename>
        friend class Evptr;

        template <typename>
        friend class Transfer;

        mutable X const* p_;
        mutable X const* cp_;
        mutable Counter* c_;
      };
    }

    namespace Bits
    {
      template <typename X>
      class Transfer : protected EvptrBase<X>
      {
      public:
        Transfer (Transfer<X> const& ct)
            : EvptrBase<X> (ct.p_, ct.cp_, ct.c_, false)
        {
          Transfer<X>& t (const_cast<Transfer<X>&> (ct));

          t.c_ = 0;
          t.p_ = 0;
          t.cp_ = 0;
        }

      private:
        Transfer (X* p, X const* cp, Counter* c)
            : EvptrBase<X> (p, cp, c, false)
        {
        }

        template <typename>
        friend class Evptr;

      private:
        Transfer<X>&
        operator= (Transfer<X> const&);
      };
    }
  }
}

#endif  // CULT_MM_BITS_EVPTR_HXX
