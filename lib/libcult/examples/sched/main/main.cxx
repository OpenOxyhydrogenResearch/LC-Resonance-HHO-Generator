// file      : examples/sched/main/main.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/types.hxx>

#include <cult/mm/shptr.hxx>
#include <cult/sched/thread.hxx>

#include <iostream>
#include <unistd.h> // sleep

using namespace Cult;
using namespace Sched;

using std::cerr;
using std::endl;

Void*
thread_func (Void*)
{
  cerr << "second thread: going to sleep for a few seconds" << endl;

  sleep (2);

  cerr << "second thread: woke up, now exiting" << endl;

  return 0;
}


Int
main ()
{
  Shptr<Thread> self (new Thread);

  Shptr<Thread> other (new Thread (thread_func));

  cerr << "initial thread: exiting" << endl;

  Thread::exit (0);
}
