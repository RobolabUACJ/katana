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
#include "packet.h"
#include <unistd.h>
#include <stdlib.h> /* for exit() */

int SCOSPacket::Receive( int fd, bool ignore_checksum )
{
  memset(packet,0,sizeof(packet));
  read(fd, &packet, 20);

  return(0);
}

int SCOSPacket::Send(int fd, unsigned char datos[3])
{
  int cnt=0;
  int sizeofpacket;

  //sizeofpacket=sizeof(datos);

   if((cnt += write(fd, datos, 3)) < 0)
  {
      perror("Send");
      return(1);
  }
  return(0);
}
