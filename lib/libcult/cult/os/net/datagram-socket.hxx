// file      : cult/os/net/datagram-socket.hxx
// author    : Boris Kolpackov <boris@kolpackov.Net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_OS_NET_DATAGRAM_SOCKET_HXX
#define CULT_OS_NET_DATAGRAM_SOCKET_HXX

#include <cult/types.hxx>

#include <cult/os/net/address.hxx>
#include <cult/os/net/socket.hxx>

#include <sys/socket.h> // SOCK_DGRAM

namespace Cult
{
  namespace OS
  {
    namespace Net
    {
      class DatagramSocket: public virtual Socket
      {
      protected:
        DatagramSocket ();

        virtual
        ~DatagramSocket ();

      public:
        virtual Int
        type () const
        {
          return SOCK_DGRAM;
        }

      public:
        virtual Size
        send (Void const* buf, Size size, Address const& addr) = 0;

        virtual Size
        recv (Void* buf, Size size) = 0;

        /*
        virtual Boolean
        recv (Void* buf,
              Size size,
              Size& received,
              OS::Time const& timeout) = 0;
        */
      };
    }
  }
}


#endif  // CULT_OS_NET_DATAGRAM_SOCKET_HXX
