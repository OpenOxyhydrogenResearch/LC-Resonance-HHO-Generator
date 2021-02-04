// file      : examples/os/net/ipv4/multicast/protocol.hxx
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2005-2010 Boris Kolpackov
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef PROTOCOL_HXX
#define PROTOCOL_HXX

#include <cult/types.hxx>

Cult::UnsignedShort const payload_size = 256;
Cult::UnsignedLong const message_count = 100;

struct Message
{
  Cult::UnsignedLong sn;
  Cult::UnsignedShort payload[payload_size];
};

#endif  // PROTOCOL_HXX
