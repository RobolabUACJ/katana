//===============================================//
//						 //
//	   Cerebot 32MX4 Control Driver          //
//	         Marco A. Elizalde	         //
//	          June 26th, 2012	         //
//						 //
//===============================================//

//This driver allows to control the DC motors of the robot and read sensory data from a IMU connected to de
//analog port on the Cerebot32MX4.This is done through an IP network using TCP communication protocol.

/*Provides

- "Motors" Position2d Interface for motor control.
- "IMU" Opaque interface for sensor data read.

Configuration File options

- port (string)
  - Default: "/dev/ttyS0"
- use_tcp (boolean)
  - Defaut: 0
  - Set to 1 if a TCP connection should be used instead of serial port (e.g. Amigobot
    with ethernet-serial bridge device attached)
- tcp_remote_host (string)
  - Default: "localhost"
  - Remote hostname or IP address to connect to if using TCP
- tcp_remote_port (integer)
  - Default: 8101
  - Remote port to connect to if using TCP
  - Serial port used to communicate with the robot.
- ignore_checksum (boolean)
  - Default: False (no effect)
  - If set to True, the checksum will be ignored*/

#include "config.h"

#include "scos.h"
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
SCOS_Init(ConfigFile* cf, int section)
{
  return (Driver*)(new SCOS(cf,section));
}

//===============================================  REGISTER  ===========================================//
void scos_Register(DriverTable* table)
{
  table->AddDriver("scos", SCOS_Init);
}

//================================================  DRIVER  ============================================//
SCOS::SCOS(ConfigFile* cf, int section)
        : ThreadedDriver(cf,section,true,PLAYER_MSGQUEUE_DEFAULT_MAXLEN)
{
  // zero ids, so that we'll know later which interfaces were requested
  memset(&this->position_id, 0, sizeof(player_devaddr_t));

  this->position_subscriptions = 0;

  // Do we create a robot position interface?
  if(cf->ReadDeviceAddr(&(this->position_id), section, "provides",
                        PLAYER_POSITION2D_CODE, -1, "Motors") == 0)
  {
    if(this->AddInterface(this->position_id) != 0)
    {
      this->SetError(-1);
      return;
    }
  }

  // Do we create a robot opaque interface?
  if(cf->ReadDeviceAddr(&(this->opaque_id), section, "provides", 
			PLAYER_OPAQUE_CODE, -1, "IMU") == 0)
  {
    if(this->AddInterface(this->opaque_id) != 0)
    {
      SetError(-1);
      return;
    }
  }

  IMU.Xaccel.Dato = 0;
  IMU.Yaccel.Dato = 0;
  IMU.Temp.Dato = 0;
  IMU.Gyro.Dato = 0;
  //IMU.Sonar.Dato = 0;
  IMU.Compass.Dato = 0;
  sensor_data.data_count = sizeof(IMU);
  sensor_data.data = reinterpret_cast<uint8_t*> (&IMU);

  // Read config file options
  this->ignore_checksum = cf->ReadBool(section, "ignore_checksum", false);

  this->psos_serial_port = cf->ReadString(section,"port",DEFAULT_SCOS_PORT);
  this->psos_use_tcp = cf->ReadInt(section, "use_tcp", 0);
  this->psos_tcp_host = cf->ReadString(section, "tcp_remote_host", DEFAULT_SCOS_TCP_REMOTE_HOST);
  this->psos_tcp_port = cf->ReadInt(section, "tcp_remote_port", DEFAULT_SCOS_TCP_REMOTE_PORT);
}

//================================================  MAIN SETUP  ==========================================//
int SCOS::MainSetup()
{
  SCOSPacket packet, sensores;
  unsigned char sensor_init[3]="\xFF";
  sensor_init[1]=0;
  sensor_init[2]=0;
  unsigned char cmdFS[3]="\xFC";
  cmdFS[1]=0;
  cmdFS[2]=0;
  int choice;

  //TCP socket Conection. The IP and PORT are defined in the config file
  TCPConnect();

  printf("\nDriver Samurai (Alpha)");
  printf("\nTCP connection configuration: (%s:%d)\n", this->psos_tcp_host, this->psos_tcp_port);
  printf("\nDriver Ready!!!\n");

  //Sensor buffer initialization
  packet.Send(this->psos_fd, sensor_init);
  usleep(SCOS_CYCLETIME_USEC);
  sensores.Receive(this->psos_fd, this->ignore_checksum);

  //Motors buffer initialization
  packet.Send(this->psos_fd, cmdFS);
  usleep(SCOS_CYCLETIME_USEC);	

  return(0);
}

//=================================================  TCP CONNECT  ====================================================//
int
SCOS::TCPConnect()
{
    int flags=0;

    printf("SCOS connecting to remote host (%s:%d)...\n", this->psos_tcp_host, this->psos_tcp_port);
    fflush(stdout);
    if( (this->psos_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
      perror("SCOS::Setup():socket():");
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
      perror("Error Connecting to remote host (SCOS::Setup()::connect()):");
      return(1);
    }
    fcntl(this->psos_fd, F_SETFL, O_SYNC | O_NONBLOCK);
    if((flags = fcntl(this->psos_fd, F_GETFL)) < 0)
    {
      perror("SCOS::Setup():fcntl()");
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
SCOS::TCPDisconnect()
{
    //printf("\nSCOS closing connecting to remote host (%s:%d)... ", this->psos_tcp_host, this->psos_tcp_port);
    close(this->psos_fd);	
}

//====================================================  MAIN QUIT  ======================================================//
void SCOS::MainQuit()
{
  if(this->psos_fd == -1)
    return;

  close(this->psos_fd);
  this->psos_fd = -1;
  puts("SCOS has been shutdown");
}

//====================================================  DESTRUCTOR  ======================================================//
SCOS::~SCOS (void)
{
  player_position2d_data_t_cleanup(&scos_data.position);
}

//=====================================================  SUBSCRIBE  ======================================================//
int
SCOS::Subscribe(player_devaddr_t id)
{
  int setupResult;

  // do the subscription
  if((setupResult = Driver::Subscribe(id)) == 0)
  {
    // also increment the appropriate subscription counter
    if(Device::MatchDeviceAddress(id, this->position_id))
      this->position_subscriptions++;
  }

  Client_Connect = TRUE;

  return(setupResult);
}

//=====================================================  UNSUBSCRIBE  =====================================================//
int
SCOS::Unsubscribe(player_devaddr_t id)
{
  int shutdownResult;

  // do the unsubscription
  if((shutdownResult = Driver::Unsubscribe(id)) == 0)
  {
    // also decrement the appropriate subscription counter
    if(Device::MatchDeviceAddress(id, this->position_id))
    {
      this->position_subscriptions--;
      assert(this->position_subscriptions >= 0);
    }
  }

  Client_Connect = FALSE;

  return(shutdownResult);
}

//====================================================  PUT DATA  ======================================================//
void
SCOS::PutData()
{
  /*//put odometry data
  this->Publish(this->position_id,
                PLAYER_MSGTYPE_DATA,
                PLAYER_POSITION2D_DATA_STATE,
                (void*)&(this->scos_data.position),
                sizeof(player_position2d_data_t), 
  		NULL);*/

  ReadSensorData();
  uint32_t IMU_size = sizeof(sensor_data) - sizeof(sensor_data.data) + sensor_data.data_count;

  // put opaque data
  this->Publish(this->opaque_id, 
		PLAYER_MSGTYPE_DATA, 
		PLAYER_OPAQUE_DATA_STATE, 
		reinterpret_cast<void*>(&sensor_data), 
		IMU_size, 
		NULL);
}

//======================================================  MAIN  =======================================================//
void
SCOS::Main()
{
  int last_position_subscrcount=0;
  double currentTime;
  struct timeval timeVal;

  for(;;)
  {
    pthread_testcancel();

    last_position_subscrcount = this->position_subscriptions;

    // handle pending messages
    if(!this->InQueue->Empty())
    {
      ProcessMessages();
    }

    //If client's subscribed, put data
    if(Client_Connect==TRUE)
    {
      PutData();
    }

    usleep(2000);
  }
}

//==================================================  PROCESS MESSAGE  ==================================================//
int
SCOS::ProcessMessage(QueuePointer & resp_queue,
                     player_msghdr * hdr,
                     void * data)
{
  	SCOSPacket packet, receivedpacket;
	int choice;
	SCOSPacket sensores;

        unsigned char cmdM1[3]="\xFA";
        unsigned char cmdM2[3]="\xFB";
        unsigned char cmdFS[3]="\xFC";
	
	assert(hdr);

	if(Message::MatchMessage(hdr, PLAYER_POSITION3D_REQ_MOTOR_POWER, PLAYER_POSITION2D_CMD_VEL, position_id))
	{
		assert(hdr->size == sizeof(player_position2d_cmd_vel_t));
		player_position2d_cmd_vel_t & command= *reinterpret_cast<player_position2d_cmd_vel_t *> (data);

		M1=command.vel.px;
		M2=command.vel.pa;

		if(M1 > 100)
			M1=100;
		if(M1 < -100)
			M1=-100;

		if(M2 > 100)
			M2=100;
		if(M2 <- 100)
			M2=-100;

                if(M1>0)
		{
			cmdM1[1]=0x00;
			cmdM1[2]=M1;
			packet.Send(this->psos_fd, cmdM1);
			usleep(SCOS_CYCLETIME_USEC);	
		}
		if(M1<0)
		{
			cmdM1[1]=0x01;
			cmdM1[2]=(-1*M1);
			packet.Send(this->psos_fd, cmdM1);
			usleep(SCOS_CYCLETIME_USEC);	
		}

		if(M2>0)
		{
			cmdM2[1]=0x00;
			cmdM2[2]=M2;
			packet.Send(this->psos_fd, cmdM2);
			usleep(SCOS_CYCLETIME_USEC);	
		}
		if(M2<0)
		{
			cmdM2[1]=0x01;
			cmdM2[2]=(-1*M2);
			packet.Send(this->psos_fd, cmdM2);
			usleep(SCOS_CYCLETIME_USEC);	
		}
	
		if(M1 == 0 && M2 == 0)
		{
			cmdFS[1]=0;
			cmdFS[2]=0;
			packet.Send(this->psos_fd, cmdFS);
			usleep(SCOS_CYCLETIME_USEC);	
		}	
	}	
}

//======================================================  ReadData  =======================================================//
void
SCOS::ReadSensorData()
{
   SCOSPacket packet;
   SCOSPacket datos_IMU;
   unsigned char sensor_cmd[]="\xFF";
   sensor_cmd[1]=0x00;
   sensor_cmd[2]=0x00;

   packet.Send(this->psos_fd, sensor_cmd);
   usleep(SCOS_CYCLETIME_USEC);
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
	IMU.Compass.byte[s-16]=datos_IMU.packet[s];
   }
   /*for(int c=20;c<24;c++)
   {
	IMU.Compass.byte[c-20]=datos_IMU.packet[c];
   }*/
}

//===================================================  PLUGIN DRIVER  ===================================================//
extern "C" {
   int player_driver_init(DriverTable* table)
   {
     puts("Initializing SCOS");
     scos_Register(table);
     puts("Done");
     return(0);
   }
}
