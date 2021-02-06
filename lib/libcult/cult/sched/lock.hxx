// file      : cult/sched/lock.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_SCHED_LOCK_HXX
#define CULT_SCHED_LOCK_HXX

#include <cult/types/fundamental.hxx>

namespace Cult
{
  namespace Sched
  {
    class Lock: public NonCopyable
    {
    public:
      ~Lock ()
      {
        unlock ();
      }

      template <typename X>
      Lock (X& x)
          : x_ (reinterpret_cast<Void*>(&x)),
            unlock_ (&unlock<X>),
            locked_ (true)
      {
        x.lock ();
      }

      Void
      unlock ()
      {
        if (locked_)
        {
          unlock_ (x_);
          locked_ = false;
        }
      }

    private:
      template <typename X>
      static Void
      unlock (Void* p)
      {
        reinterpret_cast<X*> (p)->unlock ();
      }

    private:
      Void* x_;
      Void (*unlock_) (Void*);
      Boolean locked_;
    };
  }
}

#endif  // CULT_SCHED_LOCK_HXX
