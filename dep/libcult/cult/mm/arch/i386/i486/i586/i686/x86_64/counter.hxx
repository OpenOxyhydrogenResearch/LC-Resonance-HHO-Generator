// file      : cult/mm/arch/i386/i486/i586/i686/x86_64/counter.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_MM_ARCH_I386_I486_I586_I686_X86_64_COUNTER_HXX
#define CULT_MM_ARCH_I386_I486_I586_I686_X86_64_COUNTER_HXX

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

#include <cult/mm/arch/i386/i486/i586/i686/x86_64/counter.ixx>

#endif  // CULT_MM_ARCH_I386_I486_I586_I686_X86_64_COUNTER_HXX
