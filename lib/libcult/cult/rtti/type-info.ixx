// file      : cult/rtti/type-info.ixx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace Cult
{
  namespace RTTI
  {
    // BaseInfo
    //

    inline
    BaseInfo::
    BaseInfo (Access access, Boolean virtual_, TypeId const& type_id)
        : access_ (access),
          virtual__ (virtual_),
          type_id_ (type_id),
          type_info_ (0)
    {
    }

    inline
    TypeInfo const& BaseInfo::
    type_info () const
    {
      if (type_info_ == 0) type_info_ = &(lookup (type_id_));

      return *type_info_;
    }


    inline
    Access BaseInfo::
    access () const
    {
      return access_;
    }

    inline
    Boolean BaseInfo::
    virtual_ () const
    {
      return virtual__;
    }


    // TypeInfo
    //

    inline
    TypeInfo::
    TypeInfo (TypeId const& type_id)
        : type_id_ (type_id)
    {
    }

    inline
    TypeId TypeInfo::
    type_id () const
    {
      return type_id_;
    }

    inline
    TypeInfo::BaseIterator TypeInfo::
    begin_base () const
    {
      return base_list_.begin ();
    }


    inline
    TypeInfo::BaseIterator TypeInfo::
    end_base () const
    {
      return base_list_.end ();
    }

    inline
    Void TypeInfo::
    add_base (Access access, Boolean virtual_, TypeId const& type_id)
    {
      base_list_.push_back (BaseInfo (access, virtual_, type_id));
    }
  }
}
