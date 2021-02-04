// file      : cult/os/net/ipv4/address.cxx
// author    : Boris Kolpackov <boris@kolpackov.Net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/os/net/ipv4/address.hxx>

#include <ostream>

namespace Cult
{
  namespace OS
  {
    namespace Net
    {
      namespace IPv4
      {
        std::ostream&
        operator<< (std::ostream& os, Address const& addr)
        {
          char str[INET_ADDRSTRLEN];

          if (inet_ntop (AF_INET,
                         &addr.addr_.sin_addr,
                         str,
                         INET_ADDRSTRLEN) == 0)
          {
            throw Address::Invalid ();
          }

          return os << str << ":" << addr.port ();
        }
      }
    }
  }
}

