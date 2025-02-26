#ifndef CEREBOT_H
	#define CEREBOT_H
	#include <stdio.h>
	#include <string.h>
	#include <usb.h>

	/** Argumentos para la descripcion de el dispositivo
	 *  USB. Estos pueden ser comprobados mediante el
	 * comando 'lsusb' en Linux.
	 */
	#define Cerebot_VID 0x04D8
	#define Cerebot_PID 0x0204
	/** Los End Points del dispositivo.
	 *  La verdad, esto aun no entiendo para que sea, pero
	 *  pues ahi estaban.
	 */
	#define Cerebot_EP_IN  0x81
	#define Cerebot_EP_OUT 0x01
	
	usb_dev_handle *Cerebot= NULL;
	
	enum DIRECCION{
		PROA= 		0x01,		//Parte Frontal.
		POPA= 		0x02,		//Parte Trasera.
		BABOR= 		0x04,		//Parte Izquierda.
		ESTRIBOR= 	0x08		//Parte Derecha.
	};
	
	enum LISTA_MOTORES{
		MTD= 0,		//Motor Trasero Derecho
		MTI= 1,		//Motor Trasero Izquierdo
		MFI= 2,		//Motor Frontal Izquierdo
		MFD= 3		//Motor Frontal Derecho
	};
	
	//Union para definir el formato de los datos del Cerebot.
	typedef union{
		float Dato;
		unsigned char byte[4];
	}DatoSensor;

	//Estructura que contiene los datos mandados por el Acelermetro.
	struct SensorAcelerometro{
		DatoSensor Xaccel;
		DatoSensor Yaccel;
		DatoSensor Temp;
		DatoSensor Rate;
	};
#endif