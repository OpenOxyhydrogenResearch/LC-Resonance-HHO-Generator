// file      : cult/mm/static-ptr.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_MM_STATIC_PTR_HXX
#define CULT_MM_STATIC_PTR_HXX

#include <cult/types/fundamental.hxx>

#include <cult/mm/new.hxx> // operator new

namespace Cult
{
  namespace MM
  {
    namespace Bits
    {
      struct Default {};
    }

    template <typename X, typename Id = Bits::Default>
    class StaticPtr: public NonCopyable
    {
    public:
      X&
      operator* () const
      {
        return instance ();
      }

      X*
      operator-> () const
      {
        return &instance ();
      }

    public:
      StaticPtr ()
      {
        if (i_ == 0) i_ = instance_ ();
      }

      ~StaticPtr ()
      {
        // Note that we don't delete the object in order to avoid
        // destruction order problem.
        //
      }

    private:
      static X&
      instance ()
      {
        if (i_ == 0) i_ = instance_ ();

        return *i_;
      }

      static X*
      instance_ ()
      {
        static X* i = new (KeyList ()) X;
        return i;
      }

      static X* i_;
    };

    template <typename X, typename Id>
    X* StaticPtr<X, Id>::i_ = 0;
  }
}

#endif  // CULT_MM_STATIC_PTR_HXX
