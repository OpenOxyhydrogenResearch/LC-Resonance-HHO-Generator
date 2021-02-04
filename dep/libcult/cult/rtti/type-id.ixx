// file      : cult/rtti/type-id.ixx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace Cult
{
  namespace RTTI
  {
    inline
    TypeId::
    TypeId (std::type_info const& ti)
        : ti_ (&ti)
    {
    }

    inline
    Char const* TypeId::
    name () const
    {
      return ti_->name ();
    }

    inline
    Boolean
    operator== (TypeId const& x, TypeId const& y)
    {
      return *x.ti_ == *y.ti_;
    }

    inline
    Boolean
    operator!= (TypeId const& x, TypeId const& y)
    {
      return *x.ti_ != *y.ti_;
    }

    inline
    Boolean
    operator< (TypeId const& x, TypeId const& y)
    {
      return x.ti_->before (*y.ti_);
    }
  }
}
