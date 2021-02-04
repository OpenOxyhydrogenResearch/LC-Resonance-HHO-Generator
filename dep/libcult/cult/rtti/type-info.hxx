// file      : cult/rtti/type-info.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_RTTI_TYPE_INFO_HXX
#define CULT_RTTI_TYPE_INFO_HXX

#include <cult/types/fundamental.hxx>

#include <cult/rtti/type-id.hxx>

#include <cult/containers/vector.hxx>

#include <typeinfo> // std::type_info

namespace Cult
{
  namespace RTTI
  {
    //
    //
    //
    class Access
    {
    public:
      static Access const private_, protected_, public_;

      friend Boolean
      operator== (Access const& a, Access const& b)
      {
        return a.v_ == b.v_;
      }

      friend Boolean
      operator!= (Access const& a, Access const& b)
      {
        return a.v_ != b.v_;
      }

    private:
      enum Value { private__, protected__, public__ } v_;

      Access (Value v)
          : v_ (v)
      {
      }
    };

    //
    //
    class TypeInfo;


    //
    //
    class BaseInfo
    {
    public:
      BaseInfo (Access access, Boolean virtual_, TypeId const& type_id);

    public:
      TypeInfo const&
      type_info () const;

      Access
      access () const;

      Boolean
      virtual_ () const;

    private:
      Access access_;
      Boolean virtual__;
      TypeId type_id_;
      mutable TypeInfo const* type_info_;
    };


    //
    //
    class TypeInfo
    {
      typedef Containers::Vector<BaseInfo> BaseInfoList;

    public:
      typedef
      BaseInfoList::ConstIterator
      BaseIterator;

    public:
      TypeInfo (TypeId const& type_id);

      TypeId
      type_id () const;

      BaseIterator
      begin_base () const;

      BaseIterator
      end_base () const;

      Void
      add_base (Access access, Boolean virtual_, TypeId const& type_id);

    private:
      TypeId type_id_;
      BaseInfoList base_list_;
    };


    //
    //
    class NoInfo {};

    TypeInfo const&
    lookup (TypeId const& type_id);

    inline
    TypeInfo const&
    lookup (std::type_info const& type_info)
    {
      return lookup (TypeId (type_info));
    }

    template<typename X>
    TypeInfo const&
    lookup (X const& x)
    {
      return lookup (typeid (x));
    }

    template<typename X>
    TypeInfo const&
    lookup ()
    {
      return lookup (typeid (X));
    }

    Void
    insert (TypeInfo const&);
  }
}

#include <cult/rtti/type-info.ixx>

#endif  // CULT_RTTI_TYPE_INFO_HXX
