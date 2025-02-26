#ifndef _PACKET_H
#define _PACKET_H

#include <string.h>

#include <libplayercore/globals.h>
#include <libplayercore/wallclocktime.h>

#define PACKET_LEN 20


class SSC32Packet 
{
 public:
  unsigned char packet[PACKET_LEN];
  unsigned char size;
  double timestamp;

  int Send( int fd , char datos[70]);
  int Receive( int fd, bool ignore_checksum );

  bool operator!= ( SSC32Packet p ) {
    if ( size != p.size) return(true);

    if ( memcmp( packet, p.packet, size ) != 0 ) return (true);

    return(false);
  }
};

#endif
