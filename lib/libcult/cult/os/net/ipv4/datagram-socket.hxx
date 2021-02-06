// file      : cult/os/net/ipv4/datagram-socket.hxx
// author    : Boris Kolpackov <boris@kolpackov.Net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_OS_NET_IPV4_DATAGRAM_SOCKET_HXX
#define CULT_OS_NET_IPV4_DATAGRAM_SOCKET_HXX

#include <cult/types.hxx>

#include <cult/os/net/address.hxx>
#include <cult/os/net/datagram-socket.hxx>
#include <cult/os/net/ipv4/address.hxx>

#include <unistd.h>     // close
#include <sys/socket.h> // socket, bind, sendto, revcfrom

namespace Cult
{
  namespace OS
  {
    namespace Net
    {
      namespace IPv4
      {
        class DatagramSocket: public virtual Net::DatagramSocket
        {
        public:
          virtual
          ~DatagramSocket ()
          {
            ::close (sock_);
          }

          DatagramSocket ()
          {
            sock_ = ::socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);

            if (sock_ == -1)
              throw Exception (); //@@
          }

          DatagramSocket (Address const& addr)
          {
            sock_ = ::socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);

            if (sock_ == -1)
              throw Exception (); //@@

            if (::bind (sock_, addr.raw_addr (), addr.raw_size ()) == -1)
              throw Exception (); //@@
          }

        public:
          virtual sa_family_t
          familiy () const
          {
            return AF_INET;
          }

          virtual Int
          protocol () const
          {
            return IPPROTO_UDP;
          }

          // Options.
          //
        public:
          Size
          recv_buffer_size () const
          {
            Int r;
            socklen_t s (sizeof (r));

            if (::getsockopt (sock_,
                              SOL_SOCKET,
                              SO_RCVBUF,
                              &r,
                              &s) == -1)
              {
                throw Exception (); //@@
              }

            return static_cast<Size> (r);
          }

          Void
          recv_buffer_size (Size size)
          {
            Int r (static_cast<Int> (size));

            if (::setsockopt (sock_,
                              SOL_SOCKET,
                              SO_RCVBUF,
                              &r,
                              sizeof (r)) == -1)
              {
                throw Exception ();
              }
          }

          Size
          send_buffer_size () const
          {
            Int r;
            socklen_t s (sizeof (r));

            if (::getsockopt (sock_,
                              SOL_SOCKET,
                              SO_SNDBUF,
                              &r,
                              &s) == -1)
              {
                throw Exception ();
              }

            return static_cast<Size> (r);
          }

          void
          send_buffer_size (Size size)
          {
            Int r (static_cast<Int> (size));

            if (::setsockopt (sock_,
                              SOL_SOCKET,
                              SO_SNDBUF,
                              &r,
                              sizeof (r)) == -1)
              {
                throw Exception ();
              }
          }

        public:
          Void
          connect (Address const& addr)
          {
            if (::connect (sock_, addr.raw_addr (), addr.raw_size ()) == -1)
              throw Exception ();
          }

          Address
          address () const
          {
            sockaddr_in raw_addr;
            socklen_t raw_size (sizeof (raw_addr));

            if (::getsockname (sock_,
                               reinterpret_cast<sockaddr*> (&raw_addr),
                               &raw_size) == -1)
            {
              throw Exception ();
            }

            return Address (raw_addr);
          }


        public:
          virtual Size
          send (Void const* buf, Size size, Net::Address const& addr)
          {
            if (addr.familiy () != familiy ())
              throw InvalidAddress ();

            return send (buf, size, dynamic_cast<Address const&> (addr));
          }

          virtual Size
          send (Void const* buf, Size size, Address const& addr)
          {
            ssize_t n (::sendto (sock_,
                                 buf,
                                 size,
                                 0,
                                 addr.raw_addr (),
                                 addr.raw_size ()));

            if (n == -1)
              throw Exception ();

            return static_cast<Size> (n);
          }

          virtual Size
          recv (Void* buf, Size size)
          {
            ssize_t n (::recvfrom (sock_, buf, size, 0, 0, 0));

            if (n == -1)
              throw Exception ();

            return static_cast<Size> (n);
          }

          virtual Size
          recv (Void* buf, Size size, Address& addr)
          {
            sockaddr_in raw_addr;
            socklen_t raw_size (sizeof (raw_addr));

            ssize_t n (::recvfrom (sock_,
                                   buf,
                                   size,
                                   0,
                                   reinterpret_cast<sockaddr*> (&raw_addr),
                                   &raw_size));

            if (n == -1)
              throw Exception ();

            addr = Address (raw_addr);

            return static_cast<Size> (n);
          }

          virtual Size
          peek (Void* buf, Size size, Address& addr)
          {
            sockaddr_in raw_addr;
            socklen_t raw_size (sizeof (raw_addr));

            ssize_t n (::recvfrom (sock_,
                                   buf,
                                   size,
                                   MSG_PEEK,
                                   reinterpret_cast<sockaddr*> (&raw_addr),
                                   &raw_size));

            if (n == -1)
              throw Exception ();

            addr = Address (raw_addr);

            return static_cast<Size> (n);
          }

          /*
          virtual Boolean
          recv (Void* buf,
                Size size,
                Size& received,
                OS::Time const& timeout)
          {
            fd_set r,e;

            FD_ZERO (&r);
            FD_ZERO (&e);

            FD_SET (sock_, &r);
            FD_SET (sock_, &e);

            int n = ::pselect (sock_ + 1, &r, 0, &e, &timeout.timespec (), 0);

            if (n > 0)
            {
              recv_size = recv (buf, buf_size);
              return true;
            }
            else if (n == 0) // timeout
            {
              return false;
            }
            else
            {
              throw Failure ("pselect");
            }
          }
          */

        protected:
          Int sock_;
        };
      }
    }
  }
}


#endif  // CULT_OS_NET_IPV4_DATAGRAM_SOCKET_HXX
