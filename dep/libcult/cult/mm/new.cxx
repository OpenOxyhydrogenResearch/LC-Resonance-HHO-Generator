// file      : cult/mm/new.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/mm/new.hxx>
#include <cult/mm/counter.hxx>

#include <cstdlib> // std::malloc, std::free

#include <cult/trace/stream.hxx>

namespace
{
  Cult::Trace::Stream&
  tout ()
  {
    static Cult::Trace::Stream o ("Cult::MM", 7);
    return o;
  }
}

namespace Cult
{
  namespace MM
  {
    using Bits::Offset;


    namespace
    {
      Void*
      allocate (Size size, KeyList const& l) throw (StdBadAlloc)
      {
        Size zone_size (0);

        for (KeyList::Iterator i (l.begin ()); i != l.end (); ++i)
        {
          zone_size += (*i)->size ();
        }

        Size map_size ((l.size () + 1) * sizeof (Offset));

        //tout () << "allocate: size: " << size
        //        << " map size: " << map_size
        //        << " zone size: " << zone_size;

        Char* block (reinterpret_cast<Char*> (
                       std::malloc (size + zone_size + map_size)));

        Char* base (block + zone_size + map_size);

        Offset* map (reinterpret_cast<Offset*> (base) - 1); // map bottom
        Char* zone (block + zone_size); // zone bottom

        //tout () << 9 << "allocate:" << '\n'
        //        << "  block : " << (Void*) block << '\n'
        //        << "  base  : " << (Void*) base << '\n'
        //        << "  map   : " << (Void*) zone << '\n'
        //        << "  zone  : " << (Void*) block;


        // Initialize zone map and construct services.
        //
        for (KeyList::Iterator i (l.begin ()); i != l.end (); ++i)
        {
          KeyBase const& k (**i);

          zone -= k.size (); // now at the beginning of the block

          try
          {
            k.construct (zone);
          }
          catch (...)
          {
            std::free (block);
            throw StdBadAlloc ();
          }

          map->key = &k;
          map->offset = base - zone;

          --map;
        }

        // Last element.
        //
        map->key = 0;
        map->offset = 0;

        return base;
      }

      Void
      free (Void* p) throw ()
      {
        Char* base (reinterpret_cast<Char*> (p));

        Offset* map (reinterpret_cast<Offset*> (base) - 1); // Map bottom.

        Char* block (reinterpret_cast<Char*> (map));

        while (map->key != 0)
        {
          Char* zone (base - map->offset);

          block = zone; // Last zone is the begining of the block.

          map->key->destroy (zone);

          --map;
        }

        //tout () << 9 << "free:" << '\n'
        //        << "  block : " << (Void*) block;

        std::free (block);
      }
    }
  }
}

namespace Cult
{
  namespace MM
  {
    namespace Bits
    {
#ifdef CULT_THREADS
      __thread
      Block* first_ __attribute__ ((tls_model ("initial-exec"))) = 0;
#else
      Block* first_ = 0;
#endif
    }
  }
}

using namespace Cult;

Void*
operator new (Size s) throw (MM::StdBadAlloc)
{
  return MM::allocate (s, *MM::counted);
}

Void*
operator new (Size size, MM::KeyList const& list, MM::Bits::Block const& b)
  throw (MM::StdBadAlloc)
{
  Void* p (MM::allocate (size, list));

  const_cast<MM::Bits::Block&> (b).set (p, size);

  return p;
}

Void
operator delete (Void* p) throw ()
{
  if (p) MM::free (p);
}

Void
operator delete (Void* p, Size) throw ()
{
  if (p) MM::free (p);
}

namespace Cult
{
  namespace MM
  {

    Void* ServiceAwareObject::
    operator new (Size size, Bits::Block const& block)
    {
      Void* p (allocate (size, *MM::counted));

      const_cast<MM::Bits::Block&> (block).set (p, size);

      return p;
    }

    Void ServiceAwareObject::
    operator delete (Void* p, Size)
    {
      if (p) MM::free (p);
    }
  }
}
