//===============================================//
//                                               //
//       Tools for Building TCP Packets          //
//              Marco A. Elizalde.               //
//               June 26th, 2012.                //
//                                               //
//===============================================//

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include "packet.h"
#include <unistd.h>
#include <stdlib.h> /* for exit() */


int SSC32Packet::Receive( int fd, bool ignore_checksum )
{
  memset(packet,0,sizeof(packet));
  read(fd, &packet, 70);

  return(0);
}

int SSC32Packet::Send(int fd, char datos[70])
{
  int cnt=0;
  int sizeofpacket;

   if((cnt += write(fd, datos, 70)) < 0)
  {
      perror("Send");
      return(1);
  }
  return(0);
}
