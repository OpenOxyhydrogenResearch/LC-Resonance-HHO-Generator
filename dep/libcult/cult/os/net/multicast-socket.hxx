// file      : cult/os/net/multicast-socket.hxx
// author    : Boris Kolpackov <boris@kolpackov.Net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_OS_NET_MULTICAST_SOCKET_HXX
#define CULT_OS_NET_MULTICAST_SOCKET_HXX

#include <cult/types.hxx>

#include <cult/os/net/address.hxx>
#include <cult/os/net/datagram-socket.hxx>

namespace Cult
{
  namespace OS
  {
    namespace Net
    {
      class MulticastSocket : public virtual DatagramSocket
      {
      protected:
        MulticastSocket ();

        virtual
        ~MulticastSocket ();

      public:
        virtual Void
        join (Address const& addr) = 0;

        virtual Void
        leave () = 0;
      };
    }
  }
}


#endif  // CULT_OS_NET_MULTICAST_SOCKET_HXX
