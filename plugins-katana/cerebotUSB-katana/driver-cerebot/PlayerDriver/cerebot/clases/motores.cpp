//Funciones para control de Motores
#include "../librerias/cerebot.h"

class motores{
	protected:
		//Numero de Motores
		static const char NO_MOTORES= 4;
		//Velocidad de cada uno de los NO_MOTORES.
		char Velocidad [NO_MOTORES];
		//Vector de velocidades utilizado para almacenar las velocidades temporalmente.
		char VelocidadT[NO_MOTORES];
		
		//Funcion para checar que el motor este entre 1 y NO_MOTORES.
		char checarMotor (char Motor);
		//Funcion para checar que el Porcentaje este entre -100% y 100%.
		char checarPorcentaje (char Porcentaje);
		//Funcion para guardar las velocidades actuales.
		void GuardarEnTemporal ();
		//Funcion para restablecer de Temporal.
		void RestablecerDesdeTemporal ();
	
	public:
		//Actualiza el Porcentaje de los NO_MOTORES motores por igual.
		char Porcentaje(char Porcentaje);
		//Actualiza individualmente el valor de cada velocidad.
		void Porcentaje(char Motor, char Porcentaje);
		//Activa el motor Motor con la Velocidad[Motor] definida.
		char ActivarConPorcentaje (char Motor);
		//Activa los NO_MOTORES a la vez.
		void ActivarTodos();
		//Detiene los NO_MOTORES a la vez.
		void DetenerTodos ();
		//Realiza una trayectoria recta.
		void TrayectoriaRecta (char direccion);
		//Realiza un giro sobre el eje del robot.
		void RotacionEje (char direccion);
		//Funcion para girar 45 grados en una direccion.
		void Girar (char direccion);
		void Compensacion (char Motor);
};


//############################################################
//### DEFINICION DE FUNCIONES  PROTECTED #####################
//############################################################

char motores::checarMotor (char Motor){
	if (Motor< 1){
		Motor= 1;
	}
	
	if (Motor> NO_MOTORES){
		Motor= NO_MOTORES;
	}
	
	return Motor;
}


char motores::checarPorcentaje (char Porcentaje){
	if (Porcentaje< -100){
		Porcentaje= -100;
	}
	
	if (Porcentaje> 100){
		Porcentaje= 100;
	}
	
	return Porcentaje;
}


void motores::GuardarEnTemporal () {
	for (int i= 0; i< NO_MOTORES; i++){
		VelocidadT[i]= Velocidad[i];
	}
}


void motores::RestablecerDesdeTemporal (){
	for (int i= 0; i< NO_MOTORES; i++){
		Velocidad[i]= VelocidadT[i];
	}
}

//############################################################
//### DEFINICION DE FUNCIONES PUBLIC #########################
//############################################################

char motores::Porcentaje(char Porcentaje){
	Porcentaje= checarPorcentaje (Porcentaje);
	
	Velocidad[MTD]= Velocidad[MTI]= Velocidad[MFI]= Velocidad[MFD]= Porcentaje;
	
	return Porcentaje;
}


void motores::Porcentaje(char Motor, char Porcentaje){
	Motor= checarMotor (Motor);
	Porcentaje= checarPorcentaje (Porcentaje);
	
	Velocidad[Motor - 1]= Porcentaje;
}


char motores::ActivarConPorcentaje (char Motor){
	Motor= checarMotor (Motor);
	
	char O[64];		//Buffer de Salida de Datos hacia el USB.
	 
	O[0]= 0x39;		//Codigo para activar con porcentaje.
	O[1]= Motor;
	Compensacion(Motor);
	O[2]= Velocidad[Motor-1];
	
	if(usb_bulk_write(Cerebot, Cerebot_EP_OUT, &O[0], 64, 5000)!= 64){
		printf("Error de Escritura del Servomotor (Porcentaje).\n");
	}
	return 0;
}


void motores::ActivarTodos(){
	for (int i= 0; i< NO_MOTORES; i++){
		this->ActivarConPorcentaje (i+1);
	}
}


void motores::DetenerTodos (){
	this->Porcentaje (0);
	for (int i= 0; i< NO_MOTORES; i++){
		this->ActivarConPorcentaje (i+1);
	}
}


void motores::Compensacion (char Motor){
	if (Velocidad[Motor]> 0){
		Velocidad[Motor]*= 2;
		Velocidad[Motor-1]= checarPorcentaje( Velocidad[Motor-1] );
	}
}
