// file      : cult/mm/evptr.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_MM_EVPTR_HXX
#define CULT_MM_EVPTR_HXX

#include <cult/types/fundamental.hxx>

#include <cult/mm/exception.hxx>
#include <cult/mm/bits/evptr.hxx>

#include <typeinfo> //@@ tmp

namespace Cult
{
  namespace MM
  {
    // Leaks resource should dec_ref fail.
    //
    template <typename X>
    class Evptr: public Bits::EvptrBase<X>
    {
      typedef Bits::EvptrBase<X> Base;

    public:
      Evptr (X* p = 0)
          : Base (p, 0, locate (p, *counted))
      {
      }

      Evptr (Evptr const& ep)
          : Base (0, ep.cp_ ? ep.cp_ : ep.p_, ep.c_)
      {
      }

      template <typename Y>
      Evptr (Bits::Transfer<Y> const& ct)
          : Base (ct.p_, ct.cp_, ct.c_, false)
      {
        Bits::Transfer<Y>& t (const_cast<Bits::Transfer<Y>&> (ct));

        t.c_ = 0;
        t.p_ = 0;
        t.cp_ = 0;
      }

      template <typename Y>
      Evptr (Evptr<Y> const& ep)
          : Base (0, ep.cp_ ? ep.cp_ : ep.p_, ep.c_)
      {
        //@@
        //printf ("X : %s\n", typeid (X).name ());
        //printf ("Y : %s\n", typeid (Y).name ());
      }

      template <typename Y>
      Evptr (Evptr<Y const> const& ep)
          : Base (0, ep.cp_ ? ep.cp_ : ep.p_, ep.c_)
      {
        //@@
        //printf ("X : %s\n", typeid (X).name ());
        //printf ("Y : %s const\n", typeid (Y).name ());
      }

    public:
      // After failure leaves object in destructable state.
      //
      Evptr&
      operator= (Evptr const& ep)
      {
        this->assign (ep.cp_ ? ep.cp_ : ep.p_, ep.c_);

        return *this;
      }

      template <typename Y>
      Evptr&
      operator= (Evptr<Y> const& ep)
      {
        this->assign (ep.cp_ ? ep.cp_ : ep.p_, ep.c_);

        return *this;
      }

      template <typename Y>
      Evptr&
      operator= (Bits::Transfer<Y> const& ct)
      {
        Bits::Transfer<Y>& t (const_cast<Bits::Transfer<Y>&> (ct));

        transfer (t.p_, t.cp_, t.c_);

        t.c_ = 0;
        t.p_ = 0;
        t.cp_ = 0;

        return *this;
      }

    protected:
      using Base::get_;

    public:
      X*
      operator-> () const
      {
        if (X* p = get_ ()) return p;

        throw NullPointer ();
      }

      X&
      operator* () const
      {
        if (X* p = get_ ()) return *p;

        throw NullPointer ();
      }

      Bits::Transfer<X>
      operator~ ()
      {
        Counter* c (c_);
        X* p (p_);
        X const* cp (cp_);

        c_ = 0;
        p_ = 0;
        cp_ = 0;

        return Bits::Transfer<X> (p, cp, c);
      }

    public:
      using Base::p_;
      using Base::cp_;
      using Base::c_;

      // Object pointed to by this becomes null.
      //
      template<typename Y>
      Evptr<Y>
      s_cast ()
      {
        if (p_)
        {
          Counter* c (c_);
          Y* p (static_cast<Y*> (p_));


          c_ = 0;
          p_ = 0;
          cp_ = 0;

          return Evptr<Y> (p, 0, c);
        }
        else
        {
          Counter* c (c_);
          Y const* cp (static_cast<Y const*> (cp_));

          c_ = 0;
          p_ = 0;
          cp_ = 0;

          return Evptr<Y> (0, cp, c);
        }
      }

      // Object pointed to by this becomes null if dynamic_cast succeeds.
      //
      template<typename Y>
      Evptr<Y>
      d_cast ()
      {
        if (p_)
        {
          if (Y* p = dynamic_cast<Y*> (p_))
          {
            Counter* c (c_);

            c_ = 0;
            p_ = 0;
            cp_ = 0;

            return Evptr<Y> (p, 0, c);
          }
        }
        else if (Y const* cp = dynamic_cast<Y const*> (cp_))
        {
          Counter* c (c_);

          c_ = 0;
          p_ = 0;
          cp_ = 0;

          return Evptr<Y> (0, cp, c);
        }

        return Evptr<Y> (0);
      }


    private:
      Evptr (X* p, X const* cp, Counter* c) // for *_cast
          : Base (p, cp, c, false)
      {
      }

    private:
      template <typename>
      friend class Evptr;
    };
  }

  using MM::Evptr;
}

#endif  // CULT_MM_EVPTR_HXX
