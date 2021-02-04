// file      : cult/rtti/type-id.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_RTTI_TYPE_ID_HXX
#define CULT_RTTI_TYPE_ID_HXX

#include <cult/types/fundamental.hxx>

#include <typeinfo> // std::type_info

namespace Cult
{
  namespace RTTI
  {
    class TypeId
    {
    public:
      template<typename X>
      TypeId (X const volatile&);

      TypeId (std::type_info const&);

    public:
      Char const*
      name () const;

      friend Boolean
      operator== (TypeId const&, TypeId const&);

      friend Boolean
      operator!= (TypeId const&, TypeId const&);

      friend Boolean
      operator< (TypeId const&, TypeId const&);

      /*
        friend std::ostream&
        operator << (std::ostream& os, TypeId const& t);
      */

    private:
      std::type_info const* ti_;
    };
  }
}

#include <cult/rtti/type-id.ixx>
#include <cult/rtti/type-id.txx>

#endif  // CULT_RTTI_TYPE_ID_HXX
