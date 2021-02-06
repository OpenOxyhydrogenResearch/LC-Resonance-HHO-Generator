// file      : cult/sched/thread.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/sched/thread.hxx>
#include <cult/sched/lock.hxx>
#include <cult/sched/exception.hxx>

#include <cult/mm/counter.hxx> // MM::inc_ref

#include <cult/trace/stream.hxx>

namespace Cult
{
  namespace Sched
  {
    namespace
    {
      Trace::Stream tout ("Cult::Sched::Thread", 7);
    }

    namespace Bits
    {
      typedef Void* (*Routine) (Void*);

      struct StartData
      {
        StartData (Shptr<Thread> const& thread, Routine routine, void* arg)
            : thread_ (thread), routine_ (routine), arg_ (arg)
        {
        }

        ~StartData ()
        {
          tout << 8 << "start data is being destroyed.";
        }

        Shptr<Thread> thread_;
        Routine routine_;
        Void* arg_;
      };

      static pthread_key_t key;
      static pthread_once_t key_once = PTHREAD_ONCE_INIT;

      extern "C" Void
      cult_thread_dtor (Void* p)
      {
        // Exception in this function will result in the call
        // to std::terminate().
        //

        tout << "cult_thread_dtor is being executed.";

        Shptr<Thread> self (reinterpret_cast<Thread*> (p));
      }

      extern "C" Void
      cult_thread_make_key ()
      {
        if (Int e = pthread_key_create (&key, &cult_thread_dtor))
          throw Implementation (e);
      }

      extern "C" Void*
      cult_thread_trampoline (Void* arg)
      {
        // Any failure in this function will result in the call
        // to std::terminate().
        //

        Routine routine;

        {
          Shptr<StartData> data (reinterpret_cast<StartData*> (arg));

          Thread* p (data->thread_.get ());

          if (Int e = pthread_setspecific (key, p))
            throw Implementation (e);
          else
            MM::inc_ref (p);

          routine = data->routine_;
          arg = data->arg_;
        }

        return routine (arg);
      }
    }

    Thread::
    Thread (Void* (*routine) (Void*), Void* arg)
        : detached_ (false)
    {
      using Bits::StartData;

      tout << "thread is being constructed.";

      pthread_once (&Bits::key_once, &Bits::cult_thread_make_key);

      Shptr<Thread> self (MM::inc_ref (this));

      Shptr<StartData> data (new StartData (self, routine, arg));

      if (Int e = pthread_create (&id_,
                                  0,
                                  &Bits::cult_thread_trampoline,
                                  data.get ()))
      {
        throw Implementation (e);
      }
      else
      {
        // If pthread_create did not fail then thread_trampoline
        // will release the data.
        //
        data.release ();
      }
    }

    Thread::
    Thread ()
        : id_ (pthread_self ()), detached_ (false) //@@ We can't be sure
                                                   //   the it is detached.
    {
      tout << "thread is being adopted.";

      pthread_once (&Bits::key_once, &Bits::cult_thread_make_key);

      if (pthread_getspecific (Bits::key) != 0)
        throw Adopted ();

      Shptr<Thread> self (MM::inc_ref (this));

      if(Int e = pthread_setspecific (Bits::key, this))
      {
        throw Implementation (e);
      }
      else
      {
        // TSD slot has the reference now.
        //
        self.release ();
      }
    }

    Void* Thread::
    join ()
    {
      Lock lock (mutex_);

      if (detached_)
        throw Joined ();

      Void* r;

      if (Int e = pthread_join (id_, &r))
        throw Implementation (e);

      detached_ = true;

      return r;
    }

    Void Thread::
    cancel ()
    {
      if (Int e = pthread_cancel (id_))
        throw Implementation (e);
    }

    Void Thread::
    exit (Void* ret)
    {
      pthread_exit (ret);
    }

    Shptr<Thread> Thread::
    self  ()
    {
      Thread* p (reinterpret_cast<Thread*> (pthread_getspecific (Bits::key)));

      if (p != 0)
        return Shptr<Thread> (MM::inc_ref (p));
      else
        throw Foreign ();
    }

    Void Thread::
    test_cancel ()
    {
      pthread_testcancel ();
    }

    Thread::
    ~Thread ()
    {
      tout << "thread is being destroyed.";

      Lock lock (mutex_);

      if (!detached_)
      {
        if (Int e = pthread_detach (id_))
          throw Implementation (e);
      }
    }
  }
}
