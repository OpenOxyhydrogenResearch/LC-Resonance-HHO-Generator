// file      : cult/mm/new.ixx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace Cult
{
  namespace MM
  {
    namespace Bits
    {
      inline
      Void*
      locate (Void const* p, KeyBase const& k) throw (Absent)
      {
        if (Void* bp  = Block::locate (p)) p = bp;

        Char* base (reinterpret_cast<Char*> (const_cast<Void*> (p)));

        Offset* map (reinterpret_cast<Offset*> (base) - 1); // Map bottom.

        while (map->key != 0)
        {
          if (map->key == &k)
          {
            return base - map->offset;
          }

          --map;
        }

        throw Absent ();
      }
    }
  }
}
