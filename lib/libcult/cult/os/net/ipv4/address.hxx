// file      : cult/os/net/ipv4/address.hxx
// author    : Boris Kolpackov <boris@kolpackov.Net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CULT_OS_NET_IPV4_ADDRESS_HXX
#define CULT_OS_NET_IPV4_ADDRESS_HXX

#include <cult/types.hxx>

#include <cult/os/net/address.hxx>

#include <netinet/in.h> // IPv4 types (sockaddr_in, etc)
#include <arpa/inet.h>  // hto{n,h}{s,l}, iNet_pton

#include <iosfwd>
#include <cstring> // memset

namespace Cult
{
  namespace OS
  {
    namespace Net
    {
      namespace IPv4
      {
        class Address: public Net::Address
        {
        public:
          Address ()
          {
            std::memset (&addr_, 0, sizeof (addr_));
          }

          Address (sockaddr_in const& addr)
          {
            if (addr.sin_family != AF_INET)
              throw Invalid ();

            std::memset (&addr_, 0, sizeof (addr_));

            addr_.sin_family = AF_INET;
            addr_.sin_addr.s_addr = addr.sin_addr.s_addr;
            addr_.sin_port = addr.sin_port;
          }

          Address (in_addr_t host_addr, in_port_t host_port)
          {
            std::memset (&addr_, 0, sizeof (addr_));

            addr_.sin_family = AF_INET;
            addr_.sin_addr.s_addr = htonl (host_addr);
            addr_.sin_port = htons (host_port);
          }

          Address (String const& host_addr, in_port_t host_port)
          {
            std::memset (&addr_, 0, sizeof (addr_));

            addr_.sin_family = AF_INET;
            addr_.sin_port = htons (host_port);

            if (inet_pton (AF_INET, host_addr.c_str (), &addr_.sin_addr) <= 0)
              throw Invalid ();
          }

        public:
          virtual sa_family_t
          familiy () const
          {
            return AF_INET;
          }

          virtual sockaddr const*
          raw_addr () const
          {
            return reinterpret_cast<sockaddr const*> (&addr_);
          }

          virtual Size
          raw_size () const
          {
            return sizeof (addr_);
          }

        public:
          sockaddr_in const&
          addr () const
          {
            return addr_;
          }

	  in_addr_t
	  ip () const
	  {
	    return ntohl (addr_.sin_addr.s_addr);
	  }

	  in_port_t
	  port () const
	  {
	    return ntohs (addr_.sin_port);
	  }

        public:
          friend
          Boolean
          operator< (Address const& x, Address const& y)
          {
            return (x.addr_.sin_addr.s_addr < y.addr_.sin_addr.s_addr) ||
              ((x.addr_.sin_addr.s_addr == y.addr_.sin_addr.s_addr) &&
               (x.addr_.sin_port < y.addr_.sin_port));
          }

          friend
          Boolean
          operator== (Address const& x, Address const& y)
          {
            return (x.addr_.sin_addr.s_addr == y.addr_.sin_addr.s_addr) &&
              (x.addr_.sin_port == y.addr_.sin_port);
          }

          friend
          Boolean
          operator!= (Address const& x, Address const& y)
          {
            return !(x == y);
          }

          friend
          std::ostream&
          operator<< (std::ostream&, Address const&);

        private:
          sockaddr_in addr_;
        };
      }
    }
  }
}


#endif  // CULT_OS_NET_IPV4_ADDRESS_HXX
