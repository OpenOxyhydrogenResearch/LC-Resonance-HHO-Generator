// file      : cult/os/exception.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_OS_EXCEPTION_HXX
#define CULT_OS_EXCEPTION_HXX

#include <cult/types/fundamental.hxx>

#include <cult/eh/exception.hxx>

#include <errno.h>

namespace Cult
{
  namespace OS
  {
    class Exception : public virtual EH::Exception
    {
    public:
      Exception (Int code = error_code ()) throw ()
          : code_ (code)
      {
      }

      Int
      code () const throw ()
      {
        return code_;
      }

    private:
      static Int
      error_code () throw ()
      {
        return errno;
      }

    private:
      Int code_;
    };
  }
}

#endif  // CULT_OS_EXCEPTION_HXX
