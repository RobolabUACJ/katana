//Funciones de Sensado
#include "../librerias/cerebot.h"

class analogo{
	protected:
		//Datos del Sensor.
		SensorAcelerometro Acelerometro;
	public:
		//Funcion para adquirir datos del Acelerometro.
		SensorAcelerometro LeerAcelerometro();
		//Funcion para desplegar datos del Acelerometro.
		void ImprimirDatosAcelerometro();
};


//############################################################
//### DEFINICION DE FUNCIONES PUBLIC #########################
//############################################################

SensorAcelerometro analogo::LeerAcelerometro(){
	char O[64];		//Buffer de Salida de Datos hacia el USB.
	char I[64];		//Buffer de Entrada de Datos desde el USB.
	
	O[0] = 0x37;		//Codigo que indica la utilizacion del puerto analogo.
	
	//Mandamos la orden de leer Sensor Analogo.
	//Si no se escribieron 64 bytes, hubo un error.
	if (usb_bulk_write (Cerebot, Cerebot_EP_OUT, &O[0], 64, 5000)!= 64){
		printf("Error de Escritura del Sensor Analogo.\n");
		exit(1);
	}
	//Recibimos los datos del Sensor Analogo.
	//De nuevo, si no recibimos 64 bytes, hubo un error de transmision.
	if (usb_bulk_read(Cerebot, Cerebot_EP_IN, &I[0], 64, 5000)!= 64){
		printf("Error de Lectura del Sensor Analogo.\n");
		exit(1);
	}
	
	//Adquirimos la parte alta y la desplazamos 8 bits a la izquierda.
	//Y le sumamos la parte baja, para obtener el dato completo.
	//Hacemos esto para los cuatro datos a ser adquiridos.
	Acelerometro.Xaccel.byte[0]= I[1];
	Acelerometro.Xaccel.byte[1]= I[2];
	Acelerometro.Xaccel.byte[2]= I[3];
	Acelerometro.Xaccel.byte[3]= I[4];
	
	Acelerometro.Yaccel.byte[0]= I[5];
	Acelerometro.Yaccel.byte[1]= I[6];
	Acelerometro.Yaccel.byte[2]= I[7];
	Acelerometro.Yaccel.byte[3]= I[8];
	
	Acelerometro.Rate.byte[0]= I[9];
	Acelerometro.Rate.byte[1]= I[10];
	Acelerometro.Rate.byte[2]= I[11];
	Acelerometro.Rate.byte[3]= I[12];
	
	Acelerometro.Temp.byte[0]= I[13];
	Acelerometro.Temp.byte[1]= I[14];
	Acelerometro.Temp.byte[2]= I[15];
	Acelerometro.Temp.byte[3]= I[16];
	
	return Acelerometro;
}

void analogo::ImprimirDatosAcelerometro (){
	printf("X: %f m/s^2 \t Y: %f m/s^2 \t Temp: %f C \t Giro: %f\n\r", 
		Acelerometro.Xaccel.Dato, 
		Acelerometro.Yaccel.Dato, 
		Acelerometro.Temp.Dato, 
		Acelerometro.Rate.Dato
	);
}
