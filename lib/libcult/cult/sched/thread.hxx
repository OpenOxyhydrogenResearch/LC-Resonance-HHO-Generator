// file      : cult/sched/thread.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_SCHED_THREAD_HXX
#define CULT_SCHED_THREAD_HXX

#include <cult/types/fundamental.hxx>
#include <cult/types/shptr.hxx>

#include <cult/sched/mutex.hxx>
#include <cult/sched/exception.hxx>

#include <cult/mm/new.hxx>

#include <pthread.h>

namespace Cult
{
  namespace Sched
  {
    // Instantiating an automatic variable of type Thread results
    // in undefined behavior (read core dump).
    //
    class Thread: public MM::ServiceAwareObject
    {
    public:
      struct Exception: virtual Sched::Exception {};

    public:
      virtual
      ~Thread ();

      Thread (Void* (*StartRoutine) (Void*), Void* arg = 0);

      // Adopt an existing thread. Adoption of a detached thread
      // results in undefined behavior. Adoption of an already
      // adopted thread results in Adopted exception.
      //

      struct Adopted: virtual Exception {};

      Thread ();

    public:
      // Joining an already joined thread results in Joined exception.
      //

      struct Joined: virtual Exception {};

      //@@ Need to work out the cancelled case.
      //
      Void*
      join ();

      Void
      cancel ();

    public:
      static Void
      exit (Void* ret);

      // self() may not be called in TSD destructors. Call to self() from
      // a foreign thread (i.e., one that is neither native nor adopted)
      // results in Foreign exception.
      //

      struct Foreign: virtual Exception {};

      static Shptr<Thread>
      self  ();

      static Void
      test_cancel ();

    private:
      pthread_t id_;

      Boolean detached_;
      Mutex mutex_;
    };
  }
}

#endif  // CULT_SCHED_THREAD_HXX
