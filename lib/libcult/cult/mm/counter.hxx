// file      : cult/mm/counter.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_MM_COUNTER_HXX
#define CULT_MM_COUNTER_HXX

#ifdef CULT_THREADS

// Multi-threaded version is architecture-specific.
//
#include <cult/mm/arch/counter.hxx>

#else

// Single-threaded version.
//

#include <cult/types/fundamental.hxx>

namespace Cult
{
  namespace MM
  {
    class Counter: public NonCopyable
    {
    public:
      Counter ();

      // After failure assume the counter has its old value.
      //
      Void
      inc_ref ();


      // After failure assume the counter has its new value.
      //
      Boolean
      dec_ref ();


      Size
      count () const;

    private:
      Size value_;
    };
  }
}

#include <cult/mm/counter.ixx>

#endif // CULT_THREADS


#include <cult/mm/new.hxx>
#include <cult/mm/static-ptr.hxx>

namespace Cult
{
  namespace MM
  {
    extern StaticPtr<Key<Counter> > counted;


    // Non-member inc_ref. Especially useful for messing with `this'.
    //
    template <typename X>
    X*
    inc_ref (X* p)
    {
      locate (p, *counted)->inc_ref ();
      return p;
    }
  }
}

#endif  // CULT_MM_COUNTER_HXX
