// file      : examples/os/net/ipv4/datagram/server.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/types.hxx>
#include <cult/containers/vector.hxx>

#include <cult/os/net/ipv4/address.hxx>
#include <cult/os/net/ipv4/multicast-socket.hxx>

#include <iostream>
#include <cstring> // memcmp

#include "protocol.hxx"

using std::cerr;
using std::endl;

using namespace Cult;
using namespace OS::Net::IPv4;

typedef Containers::Vector<Boolean> StatusList;

class Args {};

Int
main (Int argc, Char* argv[])
{
  try
  {
    if (argc < 2)
      throw Args ();

    Address addr (argv[1], 10000);

    MulticastSocket socket;

    socket.join (addr);

    Message expected_msg;
    expected_msg.sn = 0;

    for (UnsignedShort i = 0; i < payload_size; ++i)
    {
      expected_msg.payload[i] = i;
    }

    StatusList received (message_count, 0);
    StatusList damaged (message_count, 0);
    StatusList duplicate (message_count, 0);

    Message msg;

    while (true)
    {
      socket.recv (&msg, sizeof (msg));

      if (received[msg.sn])
      {
        duplicate[msg.sn] = true;
      }
      else
      {
        received[msg.sn] = true;

        if (std::memcmp (expected_msg.payload, msg.payload, payload_size) != 0)
        {
          damaged[msg.sn] = true;
        }
      }

      if (msg.sn + 1 == message_count) break;
    }

    UnsignedLong lost_count (0), damaged_count (0), duplicate_count (0);

    for (StatusList::Iterator i (received.begin ()), end (received.end ());
         i != end;
         ++i)
      if (!*i) ++lost_count;

    for (StatusList::Iterator i (damaged.begin ()), end (damaged.end ());
         i != end;
         ++i)
      if (*i) ++damaged_count;

    for (StatusList::Iterator i (duplicate.begin ()), end (duplicate.end ());
         i != end;
         ++i)
      if (*i) ++duplicate_count;

    cerr << "lost      : " << lost_count << endl
         << "damaged   : " << damaged_count << endl
         << "duplicate : " << duplicate_count << endl << endl;

    if (lost_count != 0)
    {
      cerr << "lost message dump:" << endl;

      UnsignedLong total = 0;

      for (StatusList::Iterator
             begin (received.begin ()), i (begin), end (received.end ());
           i != end;)
      {
        if (!*i)
        {
          UnsignedLong count = 1;

          for (StatusList::Iterator j = i + 1; j < end && !*j; j++, count++) ;

          cerr << '\t' << i - begin << " : " << count << endl;

          i += count;
          total += count;
        }
        else
          ++i;
      }

      if (total != lost_count)
        cerr << "trouble" << endl;
    }
  }
  catch (OS::Exception const& e)
  {
    cerr << "errno: " << e.code () << endl;
  }
  catch (Args const&)
  {
    cerr << "usage: client <IPv4 address>" << endl;
  }
}
