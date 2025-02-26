#include "RobotClientLibs/adicional/librerias.h"
#include "RobotClientLibs/adicional/argumentos.cpp"
#include "RobotClientLibs/adicional/tiempo.cpp"
#include "RobotClientLibs/adicional/Robot_player.h"
#include "RobotClientLibs/cerebot/librerias/cerebot.h"
#include "RobotClientLibs/adicional/ecuaciones.cpp"
#include "RobotClientLibs/adicional/teclado.cpp"

//Radio 20, radio 4.5

using namespace PlayerCc;
void ImprimirMenu ();

int main (int argc, char** argv){
	//Revisamos los argumentos, en caso de desear cambiar de plataforma.
	revisarArgumentos(argc, argv);
	
	//Establecemos conexion con el Robot.
	PlayerClient Robot (Robot_Host, Robot_Puerto);
	//Establecemos conexion con los Proxies del Robot.
	OpaqueProxy			Robot_OpaqueSensor	(&Robot, 0);
	OpaqueProxy			Robot_OpaqueMotor	(&Robot, 1);
	Position2dProxy			Robot_Motores		(&Robot, 0);
	
	//Inicio de Variables de Datos de los Sensores de Pillar Of Autumn.
	SensorAcelerometro	*Acelerometro;
	Calc_cin		*Calculos;
	//Variable que contendra la direccion de Inicio del Paquete de datos.
	uint8_t 	*DatosOpaque;
	uint8_t 	*DatosCalculos;

	while(1)
	{
		Robot.Read();
		DatosOpaque  = (uint8_t *) calloc (Robot_OpaqueSensor.GetCount(), sizeof(Acelerometro));
		Robot_OpaqueSensor.GetData(DatosOpaque);
		Acelerometro= (SensorAcelerometro *) DatosOpaque;
		printf ("Sensor: %f  %f  %f  %f\n", Acelerometro->Xaccel.Dato, Acelerometro->Yaccel.Dato,Acelerometro->Rate.Dato,Acelerometro->Temp.Dato);
		usleep(100000);
	}

	return 0;
}


