// file      : cult/mm/new.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_MM_NEW_HXX
#define CULT_MM_NEW_HXX

#include <cult/config.hxx>

#include <cult/types/fundamental.hxx>

#include <cult/mm/exception.hxx>

#include <cult/meta/polymorphic-p.hxx>

namespace Cult
{
  namespace MM
  {
    class KeyBase
    {
    public:
      // Returned size should be a multiple of a "perfect" size,
      // sizeof (size_t) * 2.
      //
      virtual Size
      size () const = 0;

      virtual Void
      construct (Void* p) const = 0;

      virtual Void
      destroy (Void* p) const = 0;

      virtual
      ~KeyBase ()
      {
      }
    };


    template <typename X>
    class Key: public KeyBase, public NonCopyable
    {
    public:
      Key ()
      {
      }

      virtual Size
      size () const
      {
        //@@ I can do this transparently in allocate().
        //
        Size align (sizeof (Size) * 2);
        Size size (sizeof (X));

        return align * (size / align + ((size % align) ? 1 : 0));
      }

      virtual Void
      construct (Void* p) const
      {
        new (p) X;
      }

      virtual Void
      destroy (Void* p) const
      {
        reinterpret_cast<X*> (p)->~X ();
      }
    };


    struct Absent : virtual Exception {};


    namespace Bits
    {
      Void*
      locate (Void const* p, KeyBase const& k) throw (Absent);

      template <typename X, Boolean poly = Meta::polymorphic_p<X>::r>
      struct Locator;

      template <typename X>
      struct Locator<X, false>
      {
        static Void*
        locate (X* p, KeyBase const& k) throw (Absent)
        {
          return Bits::locate (p, k);
        }
      };

      template <typename X>
      struct Locator<X, true>
      {
        static Void*
        locate (X* p, KeyBase const& k) throw (Absent)
        {
          return Bits::locate (dynamic_cast<Void const*> (p), k);
        }
      };

      // Note that this structure has a "perfect" size: sizeof (size_t) * 2.
      // If its size is added to the properly-aligned pointer the result will
      // still be a properly-aligned pointer.
      //
      struct Offset //@@ better name would be OffsetMap
      {
        KeyBase const* key;
        Size offset;
      };
    }


    template <typename X, typename Y>
    inline
    Y*
    locate (X* p, Key<Y> const& k) throw (Absent)
    {
      return p ? reinterpret_cast<Y*> (Bits::Locator<X>::locate (p, k)) : 0;
    }

    class KeyList
    {
    public:
      KeyList ()
          : size_ (0)
      {
      }

      KeyList (KeyBase const& k)
          : size_ (1)
      {
        keys_[0] = &k;
      }

      friend KeyList
      operator| (KeyList const& list, KeyBase const& key);

    public:
      typedef KeyBase const* const* Iterator;

      Iterator
      begin () const
      {
        return keys_;
      }

      Iterator
      end () const
      {
        return &(keys_[size_]);
      }

      Size
      size () const
      {
        return size_;
      }

    private:
      KeyBase const* keys_[8];
      Size size_;
    };

    inline KeyList
    operator| (KeyList const& list, KeyBase const& key)
    {
      //@@ Need to throw on overflow.
      //
      KeyList r (list);
      r.keys_[r.size_++] = &key;
      return r;
    }

    inline KeyList
    operator| (KeyBase const& a, KeyBase const& b)
    {
      return KeyList (a) | b;
    }
  }
}

namespace Cult
{
  namespace MM
  {
    namespace Bits
    {
      class Block;

#ifdef CULT_THREADS
      extern __thread
      Block* first_ __attribute__ ((tls_model ("initial-exec")));
#else
      extern
      Block* first_;
#endif

      class Block
      {
      public:
        Block ()
        {
        }

        ~Block ()
        {
          //@@ assert (first_ == this);
          first_ = next_;
        }

        Void
        set (Void* p, Size size)
        {
          p_ = reinterpret_cast<Char*> (p);
          size_ = size;

          next_ = first_;
          first_ = this;
        }

      public:
        static Void*
        locate (Void const* p)
        {
          return locate (p, first_);
        }

      private:
        static Void*
        locate (Void const* p, Block* b)
        {
          if (b)
          {
            if (p >= b->p_ && p < b->p_ + b->size_) return b->p_;
            else return locate (p, b->next_);
          }

          return 0;
        }

      private:
        Char* p_;
        Size size_;

        Block* next_;
      };
    }
  }
}

Cult::Void*
operator new (Cult::Size) throw (Cult::MM::StdBadAlloc);

Cult::Void*
operator new (Cult::Size,
              Cult::MM::KeyList const&,
              Cult::MM::Bits::Block const& = Cult::MM::Bits::Block ())
  throw (Cult::MM::StdBadAlloc);

//@@ Need a special operator new that just allocates memory (to use in
//   static_ptr for instance).
//

Cult::Void
operator delete (Cult::Void*) throw ();

Cult::Void
operator delete (Cult::Void*, Cult::Size) throw ();


namespace Cult
{
  namespace MM
  {
    // Inherit from this class if you plan to access service objects
    // from a ctor.
    //
    struct ServiceAwareObject
    {
      static Void*
      operator new (Size s, Bits::Block const& b = Bits::Block ());

      static Void
      operator delete (Void* p, Size s);
    };
  }
}

#include <cult/mm/new.ixx>

#endif  // CULT_MM_NEW_HXX
