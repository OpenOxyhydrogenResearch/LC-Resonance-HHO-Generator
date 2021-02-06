// file      : cult/rtti/type-info.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/rtti/type-info.hxx>

#include <cult/mm/static-ptr.hxx>

#include <cult/containers/map.hxx>

namespace Cult
{
  namespace RTTI
  {
    Access const Access::private_ (Access::private__);
    Access const Access::protected_ (Access::protected__);
    Access const Access::public_ (Access::public__);

    typedef
    Containers::Map<TypeId, TypeInfo>
    TypeInfoMap;

    static MM::StaticPtr<TypeInfoMap> map_;

    TypeInfo const&
    lookup (TypeId const& type_id)
    {
      TypeInfoMap::ConstIterator i (map_->find (type_id));

      if (i == map_->end ()) throw NoInfo ();

      return i->second;
    }

    Void
    insert (TypeInfo const& type_info)
    {
      map_->insert (TypeInfoMap::Pair (type_info.type_id (), type_info));
    }
  }
}
