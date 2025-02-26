#ifndef _SIMPLE_CLIENT_H
#define _SIMPLE_CLIENT_H

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

#endif
