// file      : examples/sched/cancel/cancel.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/types.hxx>

#include <cult/mm/shptr.hxx>

#include <cult/sched/lock.hxx>
#include <cult/sched/mutex.hxx>
#include <cult/sched/thread.hxx>
#include <cult/sched/condition.hxx>


#include <iostream>
#include <unistd.h> // sleep

using std::cerr;
using std::endl;

using namespace Cult;
using namespace Sched;

Void*
cond_wait_thread_proc (Void*)
{
  try
  {
    Mutex mutex;
    Condition cond (mutex);

    Lock lock (mutex);

    cond.wait ();
  }
  /*
  catch (std::thread_canceled const& e)
  {
    cerr << "caught thread_canceled" << endl;
    throw;
  }
  */
  catch (...)
  {
    cerr << "presumably caught thread_canceled" << endl;
    throw;
  }

  return 0;
}


Int
main ()
{
  Shptr<Thread> thread (new Thread (cond_wait_thread_proc));

  sleep (1);

  thread->cancel ();
  thread->join ();
}
