// file      : cult/os/net/ipv4/multicast-socket.hxx
// author    : Boris Kolpackov <boris@kolpackov.Net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_OS_NET_IPV4_MULTICAST_SOCKET_HXX
#define CULT_OS_NET_IPV4_MULTICAST_SOCKET_HXX

#include <cult/types.hxx>

#include <cult/os/net/address.hxx>
#include <cult/os/net/multicast-socket.hxx>
#include <cult/os/net/ipv4/address.hxx>
#include <cult/os/net/ipv4/datagram-socket.hxx>

#include <cstring>      // memcpy
#include <sys/socket.h> // bind, setsockopt
#include <arpa/inet.h>  // htonl

namespace Cult
{
  namespace OS
  {
    namespace Net
    {
      namespace IPv4
      {
        //@@ Add MulticastAddress (with proper checks)?
	//

        class MulticastSocket : public virtual Net::MulticastSocket,
                                public virtual DatagramSocket
        {
        public:
          virtual
          ~MulticastSocket ()
          {
          }

        public:
          MulticastSocket (Boolean loop = true, UnsignedShort ttl = 1)
          {
            unsigned char ttl_ (static_cast<unsigned char> (ttl));

            {
              Int flag (1);

              if (::setsockopt (sock_,
                                SOL_SOCKET,
                                SO_REUSEADDR,
                                &flag,
                                sizeof (flag)) == -1)
              {
                throw Exception ();
              }
            }

            if (ttl != 1)
            {
              if (::setsockopt (sock_,
                                IPPROTO_IP,
                                IP_MULTICAST_TTL,
                                &ttl_,
                                sizeof (ttl_)) == -1)
              {
                throw Exception ();
              }
            }

            if (!loop)
            {
              unsigned char flag (0);

              if (::setsockopt (sock_,
                                IPPROTO_IP,
                                IP_MULTICAST_LOOP,
                                &flag,
                                sizeof (flag)) == -1)
              {
                throw Exception ();
              }
            }

          }

        public:
          virtual Void
          join (Net::Address const& addr)
          {
            if (addr.familiy () != familiy ())
              throw InvalidAddress ();

            join (dynamic_cast<Address const&> (addr));
          }

          virtual Void
          join (Address const& addr)
          {
            ip_mreq mreq;

            std::memcpy (&mreq.imr_multiaddr,
                         &addr.addr ().sin_addr,
                         sizeof (in_addr));

            mreq.imr_interface.s_addr = htonl (INADDR_ANY);

            if (::setsockopt (sock_,
                              IPPROTO_IP,
                              IP_ADD_MEMBERSHIP,
                              &mreq,
                              sizeof (mreq)) == -1)
            {
              throw Exception ();
            }

            if (::bind (sock_, addr.raw_addr (), addr.raw_size ()) == -1)
              throw Exception ();
          }

          virtual Void
          leave ()
          {
            //@@ TODO
            abort ();
          }
        };
      }
    }
  }
}


#endif  // CULT_OS_NET_IPV4_MULTICAST_SOCKET_HXX
