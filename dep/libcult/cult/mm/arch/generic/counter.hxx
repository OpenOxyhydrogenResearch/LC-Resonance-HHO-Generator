// file      : cult/mm/arch/generic/counter.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_MM_ARCH_GENERIC_COUNTER_HXX
#define CULT_MM_ARCH_GENERIC_COUNTER_HXX

#include <cult/types/fundamental.hxx>
#include <cult/sched/spin.hxx>

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
      mutable Sched::Spin spin_;
    };
  }
}

#include <cult/mm/arch/generic/counter.ixx>

#endif  // CULT_MM_ARCH_GENERIC_COUNTER_HXX
