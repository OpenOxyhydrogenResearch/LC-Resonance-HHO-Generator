// file      : cult/types/fundamental.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_TYPES_FUNDAMENTAL_HXX
#define CULT_TYPES_FUNDAMENTAL_HXX

#include <cstddef> // std::size_t, std::ptrdiff_t

namespace Cult
{
  namespace Types
  {
    namespace Fundamental
    {
      // Fundamental types
      //
      typedef void Void;

      typedef bool Boolean;

      typedef char Char;
      typedef wchar_t WideChar;

      typedef short Short;
      typedef unsigned short UnsignedShort;

      typedef int Int;
      typedef unsigned int UnsignedInt;

      typedef long Long;
      typedef unsigned long UnsignedLong;

      //@@ what would be a good name for float, double and long double?
      //   ShortFloat, Float and LongFloat
      //   ShortReal, Real, LongReal

      typedef std::size_t Size;
      typedef std::ptrdiff_t PtrDifference;
      typedef Size Index;

      // Fixed-size types.
      //
      typedef signed char Int8;
      typedef unsigned char UnsignedInt8;

      typedef signed short Int16;
      typedef unsigned short UnsignedInt16;

      typedef signed int Int32;
      typedef unsigned int UnsignedInt32;

      typedef signed long long Int64;
      typedef unsigned long long UnsignedInt64;


      typedef float Float32;
      typedef double Float64;
      typedef long double Float128; // Only 96 on x86-32.
    }


    // Fundamental types
    //
    using Fundamental::Void;

    using Fundamental::Boolean;

    using Fundamental::Char;
    using Fundamental::WideChar;

    using Fundamental::Short;
    using Fundamental::UnsignedShort;

    using Fundamental::Int;
    using Fundamental::UnsignedInt;

    using Fundamental::Long;
    using Fundamental::UnsignedLong;

    using Fundamental::Size;
    using Fundamental::PtrDifference;
    using Fundamental::Index;


    // Fixed-size types.
    //
    using Fundamental::Int8;
    using Fundamental::UnsignedInt8;

    using Fundamental::Int16;
    using Fundamental::UnsignedInt16;

    using Fundamental::Int32;
    using Fundamental::UnsignedInt32;

    using Fundamental::Int64;
    using Fundamental::UnsignedInt64;


    using Fundamental::Float32;
    using Fundamental::Float64;
    using Fundamental::Float128; // Only 96 on x86-32.


    // Note: make sure you inherit publicly from this type for
    // it could be used for metaprogramming.
    //
    class NonCopyable
    {
      NonCopyable (NonCopyable const&);

      NonCopyable&
      operator= (NonCopyable const&);

    protected:
      NonCopyable ()
      {
      }
    };

    // class Clonable ?
    //

  }

  // Fundamental types
  //
  using Types::Void;

  using Types::Boolean;

  using Types::Char;
  using Types::WideChar;

  using Types::Short;
  using Types::UnsignedShort;

  using Types::Int;
  using Types::UnsignedInt;

  using Types::Long;
  using Types::UnsignedLong;

  using Types::Size;
  using Types::PtrDifference;
  using Types::Index;


  // Fixed-size types.
  //
  using Types::Int8;
  using Types::UnsignedInt8;

  using Types::Int16;
  using Types::UnsignedInt16;

  using Types::Int32;
  using Types::UnsignedInt32;

  using Types::Int64;
  using Types::UnsignedInt64;


  using Types::Float32;
  using Types::Float64;
  using Types::Float128; // Only 96 on x86-32.

  //
  //
  using Types::NonCopyable;
}

#endif  // CULT_TYPES_FUNDAMENTAL_HXX
