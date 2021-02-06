// file      : cult/os/net/socket.hxx
// author    : Boris Kolpackov <boris@kolpackov.Net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_OS_NET_SOCKET_HXX
#define CULT_OS_NET_SOCKET_HXX

#include <cult/types.hxx>
#include <cult/os/exception.hxx>

#include <sys/socket.h> // sa_family_t

namespace Cult
{
  namespace OS
  {
    namespace Net
    {
      class Socket: public NonCopyable
      {
      public:
        struct Exception : virtual OS::Exception {};

        struct InvalidAddress : virtual Exception {};

      protected:
        Socket ();

        virtual
        ~Socket ();

      public:
        // AF_INET, AF_INET6, etc.
        //
        virtual sa_family_t
        familiy () const = 0;

        // SOCK_DGRAM, SOCK_STREAM, etc.
        //
        virtual Int
        type () const = 0;

        // IPPROTO_UDP, IPPROTO_TCP, IPPROTO_SCTP, etc.
        //
        virtual Int
        protocol () const = 0;
      };
    }
  }
}


#endif  // CULT_OS_NET_SOCKET_HXX
