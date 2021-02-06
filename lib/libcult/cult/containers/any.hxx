// file      : cult/containers/any.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_CONTAINERS_ANY_HXX
#define CULT_CONTAINERS_ANY_HXX

#include <cult/types.hxx>

#include <cult/rtti/type-id.hxx>

namespace Cult
{
  namespace Containers
  {
    //@@ eager clonning: do I need it?
    //
    //
    class Any
    {
    public:
      struct Typing {};

    public:
      template <typename X>
      Any (X const& x)
          : holder_ (new HolderTemplate<X> (x))
      {
      }

      Any (Any const& any)
          : holder_ (any.holder_->clone ())
      {
      }

    public:
      template <typename X>
      Any&
      operator= (X const& x)
      {
        holder_ = Evptr<Holder> (new HolderTemplate<X> (x));
        return *this;
      }

      Any&
      operator= (Any const& any)
      {
        holder_ = any.holder_->clone ();
        return *this;
      }

    public:
      /*
      template <typename X>
      operator X& ()
      {
        return value<X> ();
      }

      template <typename X>
      operator X const& () const
      {
        return value<X> ();
      }
      */

    public:
      template <typename X>
      X&
      value ()
      {
        //@@ too strict
        //
        if (holder_->type_id () == typeid (X))
        {
          return dynamic_cast<HolderTemplate<X>*>(holder_.get ())->value ();
        }
        else
        {
          throw Typing ();
        }
      }

      template <typename X>
      X const&
      value () const
      {
        if (holder_->type_id () == typeid (X))
        {
          return dynamic_cast<HolderTemplate<X>*>(holder_.get ())->value ();
        }
        else
        {
          throw Typing ();
        }
      }

    public:
      RTTI::TypeId
      type_id () const
      {
        return holder_->type_id ();
      }

    public:
      /*
        template <typename x>
        friend x
        operator+ (any const& a, x const& b)
        {
        return a.value<x> () + b;
        }

        template <typename x>
        friend x
        operator+ (x const& a, any const& b)
        {
        return a + b.value<x> ();
        }
      */

    private:
      class Holder
      {
      public:
        virtual
        ~Holder ()
        {
        }

        Evptr<Holder>
        clone () const
        {
          return clone_ ();
        }

        virtual RTTI::TypeId
        type_id () const = 0;

      protected:
        virtual Evptr<Holder>
        clone_ () const = 0;
      };

      template <typename X>
      class HolderTemplate : public Holder
      {
      public:
        HolderTemplate (X const& value)
            : value_ (value)
        {
        }

        virtual RTTI::TypeId
        type_id () const
        {
          return RTTI::TypeId (typeid (value_));
        }

        X const&
        value () const
        {
          return value_;
        }

        X&
        value ()
        {
          return value_;
        }

      protected:
        virtual Evptr<Holder>
        clone_ () const
        {
          return new HolderTemplate<X> (value_);
        }

      private:
        X value_;
      };

    private:
      Evptr<Holder> holder_;
    };
  }
}

#include <cult/containers/any.txx>

#endif  // CULT_CONTAINERS_ANY_HXX
