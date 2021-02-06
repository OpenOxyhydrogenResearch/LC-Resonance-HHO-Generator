// file      : cult/os/net/address.hxx
// author    : Boris Kolpackov <boris@kolpackov.Net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_OS_NET_ADDRESS_HXX
#define CULT_OS_NET_ADDRESS_HXX

#include <cult/types.hxx>

#include <cult/os/exception.hxx>

#include <sys/socket.h> // sa_family_t, sockaddr

namespace Cult
{
  namespace OS
  {
    namespace Net
    {
      class Address
      {
      public:
        struct Exception: virtual OS::Exception {};

        struct Invalid : virtual Exception {};

      public:
        Address ();

        virtual
        ~Address ();

      public:
        //@@ need to wrap family
        //
        virtual sa_family_t
        familiy () const = 0;

        virtual sockaddr const*
        raw_addr () const = 0;

        virtual Size
        raw_size () const = 0;


        //@@ Should it be Clonable rather?
        //
      protected:
        Address (Address const&);

        Address&
        operator= (Address const&);
      };
    }
  }
}


#endif  // CULT_OS_NET_ADDRESS_HXX
