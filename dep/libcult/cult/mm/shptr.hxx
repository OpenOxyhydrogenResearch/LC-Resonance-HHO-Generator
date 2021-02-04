// file      : cult/mm/Shptr.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_MM_SHPTR_HXX
#define CULT_MM_SHPTR_HXX

#include <cult/types/fundamental.hxx>

#include <cult/mm/exception.hxx>
#include <cult/mm/bits/shptr.hxx>

namespace Cult
{
  namespace MM
  {
    // Leaks resource should dec_ref fail.
    //
    template <typename X>
    class Shptr : public Bits::Shptr<X>
    {
      typedef Bits::Shptr<X> Base;

    public:
      Shptr (X* p = 0)
          : Base (p, locate (p, *counted), false)
      {
      }

      Shptr (Shptr const& ap)
          : Base (ap.p_, ap.c_)
      {
      }

      template <typename Y>
      Shptr (Shptr<Y> const& ap)
          : Base (ap.p_, ap.c_)
      {
      }

    public:
      // After failure leaves object in destructable state.
      //
      Shptr&
      operator= (Shptr const& ap)
      {
        this->assign (ap);
        return *this;
      }

      template <typename Y>
      Shptr&
      operator= (Shptr<Y> const& ap)
      {
        this->assign (ap);
        return *this;
      }

    public:
      X*
      operator-> () const
      {
        if (p_ == 0)
          throw NullPointer ();

        return p_;
      }

      X&
      operator* () const
      {
        if (p_ == 0)
          throw NullPointer ();

        return *p_;
      }

      // conversion to bool
      //
      typedef X* (Shptr::*BooleanConvertible)() const;

      operator BooleanConvertible () const throw ()
      {
        return p_ ? &Shptr<X>::operator-> : 0;
      }

    public:
      X*
      get () const throw ()
      {
        return p_;
      }

      X*
      release () throw ()
      {
        return release_ ();
      }

      Size
      count () const
      {
        if (p_ == 0)
          throw NullPointer ();

        return c_->count ();
      }

    public:
      template<typename Y>
      Shptr<Y>
      d_cast () const
      {
        Y* p (dynamic_cast<Y*> (p_));
        return Shptr<Y> (p, p ? c_ : 0);
      }

    private:
      Shptr (X* p, Counter* c)
          : Base (p, c)
      {
      }

      template <typename>
      friend class Shptr;

    protected:
      using Base::release_;

      using Base::p_;
      using Base::c_;
    };
  }

  using MM::Shptr;
}

#endif  // CULT_MM_SHPTR_HXX
