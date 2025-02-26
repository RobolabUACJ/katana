#ifndef _SCOSDEVICE_H
#define _SCOSDEVICE_H

#include <pthread.h>
#include <sys/time.h>

#include <libplayercore/playercore.h>
#include "replace.h"

#include "packet.h"

/* Argument types */
#define ARGINT		0x3B	// Positive int (LSB, MSB)
#define ARGNINT		0x1B	// Negative int (LSB, MSB)
#define ARGSTR		0x2B	// String (Note: 1st byte is length!!)

/* conection stuff */
#define DEFAULT_SCOS_PORT "/dev/ttyS0"
#define DEFAULT_SCOS_TCP_REMOTE_HOST "localhost"
#define DEFAULT_SCOS_TCP_REMOTE_PORT 8101

#define SCOS_CYCLETIME_USEC 200000

typedef struct player_scos_data
{
  player_position2d_data_t position;

} __attribute__ ((packed)) player_scos_data_t;

//Union para definir el formato de los datos del Cerebot.
typedef union{
	float Dato;
	unsigned char byte[4];
}DatoSensor;

//Estructura que contiene los datos mandados por el Acelermetro.
struct SensorIMU{
	DatoSensor Xaccel;
	DatoSensor Yaccel;
	DatoSensor Gyro;
	DatoSensor Temp;
	//DatoSensor Sonar;
	DatoSensor Compass;
};

class SCOS : public ThreadedDriver
{
  private:
    player_scos_data_t scos_data;
    player_opaque_data_t sensor_data;

    player_devaddr_t position_id;
    player_devaddr_t opaque_id;

    SensorIMU IMU;

    int position_subscriptions;

    void PutData();

    //Funcion para conexion TCP
    int TCPConnect();
    int TCPDisconnect();

    //Funcion para leer el IMU (packet del Cerebot)
    void ReadSensorData();

    //Bandera para Optimizar la funcion PutData;
    bool Client_Connect;

    int M1, M2;
    int psos_fd;               // scos device file descriptor
    const char* psos_serial_port; // name of serial port device
    bool psos_use_tcp;    // use TCP port instead of serial port
    const char* psos_tcp_host;  // hostname to use if using TCP
    int psos_tcp_port;  // remote port to use if using TCP

    bool ignore_checksum;

  public:

    SCOS(ConfigFile* cf, int section);
	~SCOS (void);

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

};
#endif
