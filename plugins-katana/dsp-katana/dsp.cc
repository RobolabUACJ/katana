//===============================================//
//						 //
//	   Pandaboard ES Control Driver          //
//	         Marco A. Elizalde	         //
//	          July 12th, 2012	         //
//						 //
//===============================================//

//This driver allows comunication with player clients.

/*Provides

- "navigation" Opaque Interface.
- "localization" Opaque Interface.
- "mapping" Opaque Interface.

Configuration File options

- tcp_remote_host (string)
  - Default: "localhost"
  - Remote hostname or IP address to connect to if using TCP
- tcp_remote_port (integer)
  - Default: 8101
  - Remote port to connect to if using TCP
  - Serial port used to communicate with the robot.*/

#include "config.h"

#include "dsp.h"
#include <libplayerinterface/playerxdr.h>

#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>  /* for abs() */
#include <netinet/in.h>
#include <termios.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netdb.h>

//=================================================  INIT  =============================================//
Driver*
DSP_Init(ConfigFile* cf, int section)
{
  return (Driver*)(new DSP(cf,section));
}

//===============================================  REGISTER  ===========================================//
void dsp_Register(DriverTable* table)
{
  table->AddDriver("dsp", DSP_Init);
}

//================================================  DRIVER  ============================================//
DSP::DSP(ConfigFile* cf, int section)
        : ThreadedDriver(cf,section,true,PLAYER_MSGQUEUE_DEFAULT_MAXLEN)
{
  // Localization Interface
  // Do we create a robot opaque interface?
  if(cf->ReadDeviceAddr(&(this->opaque_id1), section, "provides", 
			PLAYER_OPAQUE_CODE, -1, "navigation") == 0)
  {
    if(this->AddInterface(this->opaque_id1) != 0)
    {
      SetError(-1);
      return;
    }
  }

  // Navigation Interface
  // Do we create a robot opaque interface?
  if(cf->ReadDeviceAddr(&(this->opaque_id2), section, "provides", 
			PLAYER_OPAQUE_CODE, -1, "localization") == 0)
  {
    if(this->AddInterface(this->opaque_id2) != 0)
    {
      SetError(-1);
      return;
    }
  }

  // Mapping Interface
  // Do we create a robot opaque interface?
  if(cf->ReadDeviceAddr(&(this->opaque_id3), section, "provides", 
			PLAYER_OPAQUE_CODE, -1, "mapping") == 0)
  {
    if(this->AddInterface(this->opaque_id3) != 0)
    {
      SetError(-1);
      return;
    }
  }

  // Sensory Data Interface
  // Do we create a robot opaque interface?
  if(cf->ReadDeviceAddr(&(this->opaque_id4), section, "provides", 
			PLAYER_OPAQUE_CODE, -1, "sensing") == 0)
  {
    if(this->AddInterface(this->opaque_id4) != 0)
    {
      SetError(-1);
      return;
    }
  }

  IMU.Xaccel.Dato = 0;
  IMU.Yaccel.Dato = 0;
  IMU.Temp.Dato = 0;
  IMU.Gyro.Dato = 0;
  IMU.Sonar.Dato = 0;
  sensor_data.data_count = sizeof(IMU);
  sensor_data.data = reinterpret_cast<uint8_t*> (&IMU);

  // Read config file options
  this->ignore_checksum = cf->ReadBool(section, "ignore_checksum", false);
  this->psos_serial_port = cf->ReadString(section,"port",DEFAULT_DSP_PORT);
  this->psos_use_tcp = cf->ReadInt(section, "use_tcp", 1);
  this->psos_tcp_host = cf->ReadString(section, "tcp_remote_host", DEFAULT_DSP_TCP_REMOTE_HOST);
  this->psos_tcp_port = cf->ReadInt(section, "tcp_remote_port", DEFAULT_DSP_TCP_REMOTE_PORT);
}

//================================================  MAIN SETUP  ==========================================//
int DSP::MainSetup()
{
  SCOSPacket packet, sensores;
  unsigned char sensor_init[3]="\xFF";
  sensor_init[1]=0;
  sensor_init[2]=0;
  unsigned char cmdFS[3]="\xFC";
  cmdFS[1]=0;
  cmdFS[2]=0;
  int choice;

  TCPConnect();

  printf("\nDSP Driver (Alpha)");
  printf("\nTCP connection configuration: (%s:%d)\n", this->psos_tcp_host, this->psos_tcp_port);
  printf("\nDriver Ready!!!\n");

  //Sensor buffer initialization
  packet.Send(this->psos_fd, sensor_init);
  usleep(DSP_CYCLETIME_USEC);
  sensores.Receive(this->psos_fd, this->ignore_checksum);

  //Motors buffer initialization
  packet.Send(this->psos_fd, cmdFS);
  usleep(DSP_CYCLETIME_USEC);	

  return(0);
}

//=================================================  TCP CONNECT  ====================================================//
int
DSP::TCPConnect()
{
    int flags=0;

    printf("DSP connecting to remote host (%s:%d)...\n", this->psos_tcp_host, this->psos_tcp_port);
    fflush(stdout);
    if( (this->psos_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
      perror("DSP::Setup():socket():");
      return(1);
    }
    //printf("created socket %d.\nLooking up hostname...\n", this->psos_fd);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(this->psos_tcp_port);
#if HAVE_GETADDRINFO
    struct addrinfo * addr_ptr = NULL;
    if (getaddrinfo(this->psos_tcp_host, NULL, NULL, &addr_ptr))
    {
      PLAYER_ERROR("Error looking up hostname or address");
      return 1;
    }
    assert(addr_ptr);
    assert(addr_ptr->ai_addr);
    assert((addr_ptr->ai_addr->sa_family) == AF_INET);
    addr.sin_addr.s_addr = (reinterpret_cast<struct sockaddr_in *>(addr_ptr->ai_addr))->sin_addr.s_addr;
    freeaddrinfo(addr_ptr);
    addr_ptr = NULL;
#else
    struct hostent* h = gethostbyname(this->psos_tcp_host);
    if(!h)
    {
      perror("Error looking up hostname or address %s:");
      return(1);
    }
    assert(static_cast<size_t> (h->h_length) <= sizeof(addr.sin_addr));
    //printf("gethostbyname returned address %d length %d.\n", * h->h_addr, h->h_length);
    memcpy(&(addr.sin_addr), h->h_addr, h->h_length);
    //printf("copied address to addr.sin_addr.s_addr=%d\n", addr.sin_addr.s_addr);
#endif
    PLAYER_WARN("Found host address, connecting...");
    if(connect(this->psos_fd, reinterpret_cast<struct sockaddr*> (&addr), sizeof(addr)) < 0)
    {
      perror("Error Connecting to remote host (DSP::Setup()::connect()):");
      return(1);
    }
    fcntl(this->psos_fd, F_SETFL, O_SYNC | O_NONBLOCK);
    if((flags = fcntl(this->psos_fd, F_GETFL)) < 0)
    {
      perror("DSP::Setup():fcntl()");
      close(this->psos_fd);
      this->psos_fd = -1;
      return(1);
    }
    assert(flags & O_NONBLOCK);
    PLAYER_WARN("TCP socket connection is OK... ");
    fflush(stdout);
    return(0);	
}

//=================================================  TCP DISCONNECT  ====================================================//
int
DSP::TCPDisconnect()
{
    //printf("\nSCOS closing connecting to remote host (%s:%d)... ", this->psos_tcp_host, this->psos_tcp_port);
    close(this->psos_fd);	
}

//====================================================  MAIN QUIT  ======================================================//
void DSP::MainQuit()
{
  if(this->psos_fd == -1)
    return;

  close(this->psos_fd);
  this->psos_fd = -1;
  puts("DSP has been shutdown");
}

//====================================================  DESTRUCTOR  ======================================================//
DSP::~DSP (void)
{
}

//=====================================================  SUBSCRIBE  ======================================================//
int
DSP::Subscribe(player_devaddr_t id)
{
  int setupResult;

  setupResult = Driver::Subscribe(id);

  Client_Connect = TRUE;

  return(setupResult);
}

//=====================================================  UNSUBSCRIBE  =====================================================//
int
DSP::Unsubscribe(player_devaddr_t id)
{
  int shutdownResult;

  shutdownResult = Driver::Unsubscribe(id);

  Client_Connect = FALSE;

  return(shutdownResult);
}

//====================================================  PUT DATA  ======================================================//
void
DSP::PutData()
{
  ReadSensorData();
  uint32_t IMU_size = sizeof(sensor_data) - sizeof(sensor_data.data) + sensor_data.data_count;

  /*// Put "Navigation" opaque data
  this->Publish(this->opaque_id1, 
		PLAYER_MSGTYPE_DATA, 
		PLAYER_OPAQUE_DATA_STATE, 
		reinterpret_cast<void*>(&some_data), 
		IMU_size, 
		NULL);*/

  /*// Put "Localization" opaque data
  this->Publish(this->opaque_id2, 
		PLAYER_MSGTYPE_DATA, 
		PLAYER_OPAQUE_DATA_STATE, 
		reinterpret_cast<void*>(&some_data), 
		IMU_size, 
		NULL);

  // Put "Mapping" opaque data
  this->Publish(this->opaque_id3, 
		PLAYER_MSGTYPE_DATA, 
		PLAYER_OPAQUE_DATA_STATE, 
		reinterpret_cast<void*>(&some_data), 
		IMU_size, 
		NULL);*/

  // Put "Sensing" opaque data
  this->Publish(this->opaque_id4, 
		PLAYER_MSGTYPE_DATA, 
		PLAYER_OPAQUE_DATA_STATE, 
		reinterpret_cast<void*>(&sensor_data), 
		IMU_size, 
		NULL);
}

//======================================================  MAIN  =======================================================//
void
DSP::Main()
{
  int last_position_subscrcount=0;
  double currentTime;
  struct timeval timeVal;

  for(;;)
  {
    pthread_testcancel();

    //last_position_subscrcount = this->position_subscriptions;

    // handle pending messages
    //if(!this->InQueue->Empty())
    //{
      //ProcessMessages();
    //}

    //If client's subscribed, put data
    if(Client_Connect==TRUE)
    {
      PutData();
    }

    usleep(20000);
  }
}

//==================================================  PROCESS MESSAGE  ==================================================//
int
DSP::ProcessMessage(QueuePointer & resp_queue,
                     player_msghdr * hdr,
                     void * data)
{	
}

//======================================================  ReadData  =======================================================//
void
DSP::ReadSensorData()
{
   SCOSPacket packet;
   SCOSPacket datos_IMU;
   unsigned char sensor_cmd[]="\xFF";
   sensor_cmd[1]=0x00;
   sensor_cmd[2]=0x00;

   packet.Send(this->psos_fd, sensor_cmd);
   usleep(DSP_CYCLETIME_USEC);
   datos_IMU.Receive(this->psos_fd, this->ignore_checksum);

   for(int xa=0;xa<4;xa++)
   {
 	IMU.Xaccel.byte[xa]=datos_IMU.packet[xa];
   }
   for(int ya=4;ya<8;ya++)
   {
 	IMU.Yaccel.byte[ya-4]=datos_IMU.packet[ya];
   }
   for(int g=8;g<12;g++)
   {
   	IMU.Gyro.byte[g-8]=datos_IMU.packet[g];
   }
   for(int t=12;t<16;t++)
   {
   	IMU.Temp.byte[t-12]=datos_IMU.packet[t];
   }
   for(int s=16;s<20;s++)
   {
	IMU.Sonar.byte[s-16]=datos_IMU.packet[s];
   }
}

//===================================================  PLUGIN DRIVER  ===================================================//
extern "C" {
   int player_driver_init(DriverTable* table)
   {
     puts("Initializing DSP");
     dsp_Register(table);
     puts("Done");
     return(0);
   }
}
