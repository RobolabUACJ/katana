//===============================================//
//						 //
//	   Lynxmotion SSC-32 Control Driver      //
//	         Marco A. Elizalde	         //
//	           Oct 8th, 2012	         //
//						 //
//===============================================//

//This driver allows to control the servo channel on a Lynxmotion SSC-32
/*Provides

- "Servos" Position2d Interface for motor control.

Configuration File options

- port (string)
  - Default: "/dev/ttyS0"
- ignore_checksum (boolean)
  - Default: False (no effect)
  - If set to True, the checksum will be ignored*/

#include "config.h"

#include "ssc32.h"
#include <libplayerinterface/playerxdr.h>

#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stddef.h>
#include <stdio.h>

#include <iostream>
#include <sstream>

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

std::string chain[11];

//=================================================  INIT  =============================================//
Driver*
SSC32_Init(ConfigFile* cf, int section)
{
  return (Driver*)(new SSC32(cf,section));
}

//===============================================  REGISTER  ===========================================//
void ssc32_Register(DriverTable* table)
{
  table->AddDriver("ssc32", SSC32_Init);
}

//================================================  DRIVER  ============================================//
SSC32::SSC32(ConfigFile* cf, int section)
        : ThreadedDriver(cf,section,true,PLAYER_MSGQUEUE_DEFAULT_MAXLEN)
{
  // zero ids, so that we'll know later which interfaces were requested
  memset(&this->position_id, 0, sizeof(player_devaddr_t));

  this->position_subscriptions = 0;

  // Do we create a robot position interface?
  if(cf->ReadDeviceAddr(&(this->position_id), section, "provides",
                        PLAYER_POSITION2D_CODE, -1, "Servos") == 0)
  {
    if(this->AddInterface(this->position_id) != 0)
    {
      this->SetError(-1);
      return;
    }
  }

  // Read config file options
  this->ignore_checksum = cf->ReadBool(section, "ignore_checksum", false);

  this->psos_serial_port = cf->ReadString(section,"port",DEFAULT_SSC32_PORT);
}

//================================================  MAIN SETUP  ==========================================//
int SSC32::MainSetup()
{

  printf("\nLynxmotion SSC-32 Control Driver");
  printf("\nDriver Ready!!!\n");

 int i;
  // this is the order in which we'll try the possible baud rates.
  int bauds[] = {B9600, B38400, B19200, B115200, B57600};
  int numbauds = sizeof bauds / sizeof(int);
  int currbaud = 0;

  struct termios term;
  unsigned char command;
  int flags=0;
  bool sent_close = false;

  char name[20], type[20], subtype[20];
  int cnt;

    // Serial port:

    printf("SSC32 connection opening serial port %s...",this->psos_serial_port);
    fflush(stdout);

    if((this->psos_fd = open(this->psos_serial_port,
#ifdef __QNXNTO__
                     O_RDWR | O_NONBLOCK, S_IRUSR | S_IWUSR )) < 0 )
#else
                     O_RDWR | O_SYNC | O_NONBLOCK, S_IRUSR | S_IWUSR )) < 0 )
#endif
    {
      perror("SSC32::Setup():open():");
      return(1);
    }

    if(tcgetattr( this->psos_fd, &term ) < 0 )
    {
      perror("SSC32::Setup():tcgetattr():");
      close(this->psos_fd);
      this->psos_fd = -1;
      return(1);
    }

    cfmakeraw( &term );
    cfsetispeed(&term, bauds[currbaud]);
    cfsetospeed(&term, bauds[currbaud]);

    if(tcsetattr(this->psos_fd, TCSAFLUSH, &term ) < 0)
    {
      perror("SSC32::Setup():tcsetattr():");
      close(this->psos_fd);
      this->psos_fd = -1;
      return(1);
    }

    if(tcflush(this->psos_fd, TCIOFLUSH ) < 0)
    {
      perror("SSC32::Setup():tcflush():");
      close(this->psos_fd);
      this->psos_fd = -1;
      return(1);
    }

    if((flags = fcntl(this->psos_fd, F_GETFL)) < 0)
    {
      perror("SSC32::Setup():fcntl()");
      close(this->psos_fd);
      this->psos_fd = -1;
      return(1);
    }
    fflush(stdout);

    init_arm();

  return(0);
}

//====================================================  MAIN QUIT  ======================================================//
void SSC32::MainQuit()
{
  if(this->psos_fd == -1)
    return;

  close(this->psos_fd);
  this->psos_fd = -1;
  puts("SSC32 has been shutdown");
}

//====================================================  DESTRUCTOR  ======================================================//
SSC32::~SSC32 (void)
{
  player_position2d_data_t_cleanup(&ssc32_data.position);
}

//=====================================================  SUBSCRIBE  ======================================================//
int
SSC32::Subscribe(player_devaddr_t id)
{
  int setupResult;

  // do the subscription
  if((setupResult = Driver::Subscribe(id)) == 0)
  {
    // also increment the appropriate subscription counter
    if(Device::MatchDeviceAddress(id, this->position_id))
      this->position_subscriptions++;
  }

  return(setupResult);
}

//=====================================================  UNSUBSCRIBE  =====================================================//
int
SSC32::Unsubscribe(player_devaddr_t id)
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

  return(shutdownResult);
}

//======================================================  MAIN  =======================================================//
void
SSC32::Main()
{
  int last_position_subscrcount=0;
  double currentTime;

  for(;;)
  {
    pthread_testcancel();

    last_position_subscrcount = this->position_subscriptions;

    // handle pending messages
    if(!this->InQueue->Empty())
    {
      ProcessMessages();
    }
  }
}

//==================================================  PROCESS MESSAGE  ==================================================//
int
SSC32::ProcessMessage(QueuePointer & resp_queue,
                     player_msghdr * hdr,
                     void * data)
{
  	SSC32Packet packet;

	chain[0] = "#0 P"; 
	chain[1] = " S";
	chain[2] = " #1 P";
	chain[3] = " S";
	chain[4] = " #2 P";
	chain[5] = " S";
	chain[6] = " #3 P";
	chain[7] = " S";
	chain[8] = " #4 P";
	chain[9] = " S";
	chain[10] = "\r";

	int pselect;
	int dselect;
	int sselect;

	std::string stream;
	std::stringstream sstm;

	assert(hdr);

	if(Message::MatchMessage(hdr, PLAYER_POSITION3D_REQ_MOTOR_POWER, PLAYER_POSITION2D_CMD_VEL, position_id))
	{
		assert(hdr->size == sizeof(player_position2d_cmd_vel_t));
		player_position2d_cmd_vel_t & command= *reinterpret_cast<player_position2d_cmd_vel_t *> (data);

		pselect=command.vel.px;

		switch (pselect)
		{
			case 0:
				arm.ddata[0]=command.vel.py;
				arm.ddata[1]=command.vel.py;
				arm.speed[0]=command.vel.pa;
				arm.speed[1]=command.vel.pa;
			break;
			case 1:
				arm.ddata[0]=command.vel.py;
				arm.ddata[1]=command.vel.py;
				arm.speed[0]=command.vel.pa;
				arm.speed[1]=command.vel.pa;
			break;
			case 2:
				arm.ddata[2]=command.vel.py;
				arm.speed[2]=command.vel.pa;
			break;
			case 3:
				arm.ddata[3]=command.vel.py;
				arm.speed[3]=command.vel.pa;
			break;
			case 4:
				arm.ddata[4]=command.vel.py;
				arm.speed[4]=command.vel.pa;
			break;
		}

		sstm << chain[0] << arm.ddata[0] << chain[1] << arm.speed[0] 
		     << chain[2] << arm.ddata[1] << chain[3] << arm.speed[1] 
		     << chain[4] << arm.ddata[2] << chain[5] << arm.speed[2] 
		     << chain[6] << arm.ddata[3] << chain[7] << arm.speed[3] 
		     << chain[8] << arm.ddata[4] << chain[9] << arm.speed[4] << chain[10];
		stream = sstm.str();

		char *cmd=new char[stream.size()+1];
		cmd[stream.size()]=0;
		memcpy(cmd,stream.c_str(),stream.size());

		packet.Send(this->psos_fd, cmd);
		usleep(SSC32_CYCLETIME_USEC);

		//std::cout << cmd << "\n" <<std::endl;
	}	
}

//====================================================  MAIN QUIT  ======================================================//
void SSC32::init_arm()
{
	for(int x=0;x<5;x++)
	{
		arm.ddata[x]=1500;
		arm.speed[x]=300;
	}
}

//===================================================  PLUGIN DRIVER  ===================================================//
extern "C" {
   int player_driver_init(DriverTable* table)
   {
     puts("Initializing SSC32");
     ssc32_Register(table);
     puts("Done");
     return(0);
   }
}
