#ifndef _SSC32DEVICE_H
#define _SSC32DEVICE_H

#include <pthread.h>
#include <sys/time.h>

#include <libplayercore/playercore.h>
#include "replace.h"

#include "packet.h"

//Conection Definitions:
#define DEFAULT_SSC32_PORT "/dev/ttyS0"
#define SSC32_CYCLETIME_USEC 1000


typedef struct player_ssc32_data
{
  player_position2d_data_t position;

} __attribute__ ((packed)) player_ssc32_data_t;

struct lynxmotion{
	int port[5];
	int ddata[5];
	int speed[5];
};

class SSC32 : public ThreadedDriver
{
  private:
    player_ssc32_data_t ssc32_data;

    player_devaddr_t position_id;

    lynxmotion arm;

    int position_subscriptions;

    void PutData();

    int psos_fd;               // ssc32 device file descriptor
    const char* psos_serial_port; // name of serial port device

    bool ignore_checksum;

  public:

    SSC32(ConfigFile* cf, int section);
	~SSC32 (void);

    virtual int Subscribe(player_devaddr_t id);
    virtual int Unsubscribe(player_devaddr_t id);

    /* the main thread */
    virtual void Main();

    virtual int MainSetup();
    virtual void MainQuit();

    // MessageHandler
    virtual int ProcessMessage(QueuePointer & resp_queue,
                               player_msghdr * hdr,
                               void * data);

    virtual void init_arm();
};
#endif
