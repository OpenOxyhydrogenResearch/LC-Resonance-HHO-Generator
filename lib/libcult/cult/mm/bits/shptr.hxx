// file      : cult/mm/bits/shptr.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_MM_BITS_SHPTR_HXX
#define CULT_MM_BITS_SHPTR_HXX

#include <cult/types/fundamental.hxx>

#include <cult/mm/counter.hxx>
#include <cult/mm/exception.hxx>

namespace Cult
{
  namespace MM
  {
    namespace Bits
    {
      template <typename X>
      class Shptr
      {
      protected:
        ~Shptr ()
        {
          if (c_ && c_->dec_ref ()) delete p_;
        }

        Shptr (X* p, Counter* c, Boolean inc = true)
            : p_ (p), c_ (c)
        {
          if (c_ && inc) c_->inc_ref ();
        }

      protected:
        X*
        release_ () throw ()
        {
          X* tmp (p_);

          c_ = 0;
          p_ = 0;

          return tmp;
        }

      protected:
        template<typename y>
        Void
        assign (Shptr<y> const& bp, Boolean inc = true)
        {
          assign (bp.p_, bp.c_, inc);
        }

        Void
        assign (X* p, Counter* c, Boolean inc)
        {
          if (c_ && c_ == c) throw SelfAssignment ();

          if (c_)
          {
            Counter* t (c_);
            c_ = 0;
            p_ = 0;
            t->dec_ref ();
          }

          if (c && inc) c->inc_ref ();

          p_ = p;
          c_ = c;
        }

      protected:
        template <typename>
        friend class Shptr;

        X* p_;
        Counter* c_;
      };
    }
  }
}

#endif  // CULT_MM_BITS_SHPTR_HXX
