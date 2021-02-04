// file      : examples/os/net/ipv4/datagram/client.cxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cult/types.hxx>

#include <cult/os/net/ipv4/address.hxx>
#include <cult/os/net/ipv4/datagram-socket.hxx>

#include <iostream>
#include <unistd.h> // usleep

#include "protocol.hxx"

using std::cerr;
using std::endl;

using namespace Cult;
using namespace OS::Net::IPv4;

class Args {};

Int
main (Int argc, Char* argv[])
{
  try
  {
    if (argc < 2)
      throw Args ();

    Address addr (argv[1], 10000);

    DatagramSocket socket;

    Message msg;
    msg.sn = 0;

    cerr << "message size : " << sizeof (msg) << " bytes" << endl;
    cerr << "send buffer  : " << socket.send_buffer_size () << " bytes" << endl;

    for (Index i = 0; i < payload_size; i++)
    {
      msg.payload[i] = i;
    }

    for (; msg.sn < message_count; msg.sn++)
    {
      socket.send (&msg, sizeof (msg), addr);

      // ::usleep (10);
    }

    return 0;
  }
  catch (OS::Exception const& e)
  {
    cerr << "errno: " << strerror (e.code ()) << endl;
  }
  catch (Args const&)
  {
    cerr << "usage: client <IPv4 address>" << endl;
  }

  return 1;
}
