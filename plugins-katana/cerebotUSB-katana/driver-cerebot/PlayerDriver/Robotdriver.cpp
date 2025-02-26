#include "adicional/librerias.h"
#include "adicional/ecuaciones.cpp"
#include "cerebot/librerias/cerebot.h"
#include "cerebot/superclase.cpp"

//### Clase base para cualquier driver de Player. ###
class Robotdriver : public ThreadedDriver{
	public:
		//Constructor del Driver.
		Robotdriver(ConfigFile* cf, int section);
		// This method will be invoked on each incoming message
		virtual int ProcessMessage(QueuePointer &resp_queue, player_msghdr * hdr, void * data);
	private:
		//Direcciones de los Drivers a utilizar.
		player_devaddr_t position2dID;
		player_devaddr_t opaqueID;
		player_devaddr_t opaqueID1;	
		//cerebot
		superclase cerebot;
	
		//Funcion principal de ejecucion del Driver.
		virtual void Main();
		virtual int MainSetup();
		virtual void MainQuit();
	
		//Valores del Acelerometro a ser mandados.
		SensorAcelerometro Acelerometro;
		//Paquete de Valores a ser mandados.
		player_opaque_data_t Datos;
	
		//Valores Calculados.
		Calc_cin ValCalc;
		//Paquete de Datos de Valores Calculados.
		player_opaque_data_t DatosCalculos;
		
		void LeerAcelerometro ();
};

// A factory creation function, declared outside of the class so that it
// can be invoked without any object context (alternatively, you can
// declare it static in the class).  In this function, we create and return
// (as a generic Driver*) a pointer to a new instance of this driver.
Driver* Robotdriver_Init(ConfigFile* cf, int section){
	// Create and return a new instance of this driver
	return((Driver*)(new Robotdriver(cf, section)));
}

// A driver registration function, again declared outside of the class so
// that it can be invoked without object context.  In this function, we add
// the driver into the given driver table, indicating which interface the
// driver can support and how to create a driver instance.
void Robotdriver_Register(DriverTable* table){
	table->AddDriver("Robotdriver", Robotdriver_Init);
}

//Constructor del Driver.
Robotdriver::Robotdriver(ConfigFile* cf, int section): ThreadedDriver(cf, section){
	//Verificar si el archivo de configuracion nos pide la interfaz de position2d
	if (cf->ReadDeviceAddr(&(this->position2dID), section, "provides", PLAYER_POSITION2D_CODE, -1, NULL) == 0){
		//Si la interfaz no se registro correctamente,
        if (this->AddInterface(this->position2dID)!= 0){
			//Mandamos un mensaje de error,
            PLAYER_ERROR("Error al agregar la interfaz de position2d.\n");
			//Y establecemos una bandera de deteccion de errores.
            SetError(-1);
            return;
        }
    }
	
	//Verificar si el archivo de configuracion nos pide la interfaz de opaque
	if (cf->ReadDeviceAddr(&(this->opaqueID), section, "provides", PLAYER_OPAQUE_CODE, -1, "sensores") == 0){
		//Si la interfaz no se registro correctamente,
        if (this->AddInterface(this->opaqueID) != 0){
            //Mandamos un mensaje de error,
            PLAYER_ERROR("Error al agregar la interfaz de opaque para sensores.\n");
			//Y establecemos una bandera de deteccion de errores.
            SetError(-1);
            return;
        }
		
		//Al terminar de activar la interfaz, definimos el tamanio de los datos a mandar.
		Acelerometro.Xaccel.Dato=	0;
		Acelerometro.Yaccel.Dato=	0;
		Acelerometro.Temp.Dato=		0;
		Acelerometro.Rate.Dato=		0;
		Datos.data_count = sizeof(SensorAcelerometro);
		Datos.data = reinterpret_cast<uint8_t*> (&Acelerometro);
    }
	
	if (cf->ReadDeviceAddr(&(this->opaqueID1), section, "provides", PLAYER_OPAQUE_CODE, -1, "motores") == 0){
		//Si la interfaz no se registro correctamente,
        if (this->AddInterface(this->opaqueID1) != 0){
            //Mandamos un mensaje de error,
            PLAYER_ERROR("Error al agregar la interfaz de opaque para motores.\n");
			//Y establecemos una bandera de deteccion de errores.
            SetError(-1);
            return;
        }
		
		//Al terminar de activar la interfaz, definimos el tamanio de los datos a mandar.
		ValCalc.Theta=	0;
		ValCalc.Xk= 	0;
		ValCalc.Yk= 	0;
		for (char i= 0; i< MOTORES; i++){
			ValCalc.Porcentaje[i]= 0;
			ValCalc.Phi[i]=	0;
		}
		DatosCalculos.data_count = sizeof (Calc_cin);
		DatosCalculos.data= reinterpret_cast<uint8_t*> (&ValCalc);
    }
}


//Inicializacion del Driver del cerebot.
int Robotdriver::MainSetup(){
	puts("Inicializando Player cerebot32MX4.");

	//Verificamos la conexion con el cerebot.
	if (cerebot.Conectar()!= 1){
		PLAYER_ERROR("No se pudo realizar la conexion con el cerebot.");
		return -1;
	}else{
		puts("cerebot32MX4 Listo.");
	}

	return 0;
}


//Termino del Driver del cerebot.
void Robotdriver::MainQuit(){
	puts("Desconectando el vinculo con el cerebot.");
	cerebot.Desconectar();
	puts("El cerebot ha sido desconectado.");
}


int Robotdriver::ProcessMessage(QueuePointer & resp_queue, player_msghdr * hdr, void * data){
	//Procesamos los mensajes aqui. En caso de necesitar abortar, mandamos un -1.
	//En caso de necesitar mandar una respuesta, utilizamos Publish.
	
	//Si no contiene nada el encabezado, abortar.
	assert(hdr);
	
	//Funcion para verificar si el mensaje <hdr> pertenece a una orden para position2dID,
	//con tipo MOTOR_POWER, subtipo CMD_VEL.
	if(Message::MatchMessage(hdr, PLAYER_POSITION2D_REQ_MOTOR_POWER, PLAYER_POSITION2D_CMD_VEL, position2dID)){
		//Verificamos que el tamanio del mensaje sea del tamanio del tipo de dato requerido.
		assert(hdr->size == sizeof(player_position2d_cmd_vel_t));
		//Realizamos la conversion del apuntador a player_position2d_cmd_vel_t, que pertenece
		//a los valores de las velocidades.
        player_position2d_cmd_vel_t &Orden= *reinterpret_cast<player_position2d_cmd_vel_t *> (data);

		//Aqui se activarian los motores.
		ValCalc= RealizarCalculos (Orden.vel.px, Orden.vel.py, Orden.vel.pa, ValCalc);
		//uint32_t Tamanio = sizeof(DatosCalculos) - sizeof(DatosCalculos.data) + DatosCalculos.data_count;
		Publish (opaqueID1, PLAYER_MSGTYPE_DATA, PLAYER_OPAQUE_DATA_STATE, reinterpret_cast<void*>(&DatosCalculos), sizeof(DatosCalculos), NULL);
		/*
		char s1[20];
		char s2[20];
		char s3[20];
		char s4[20];
		
		sprintf(s1, "Velocidad Px: %f", Orden.vel.px);
		sprintf(s2, "Velocidad Py: %f", Orden.vel.py);
		sprintf(s3, "Velocidad Pa: %f", Orden.vel.pa);
		
		puts (s1);
		puts (s2);
		puts (s3);
		
		for (char i= 0; i< MOTORES; i++){
			cerebot.Porcentaje (i, ValCalc.Porcentaje[i]);
			sprintf(s4, "Porcentaje[%d]: %d", i, ValCalc.Porcentaje[i]);
			puts (s4);




		}	*/
	cerebot.Porcentaje(1,ValCalc.Porcentaje[0]);
	cerebot.Porcentaje(2,ValCalc.Porcentaje[1]);
	cerebot.Porcentaje(3,ValCalc.Porcentaje[2]);

	cerebot.ActivarConPorcentaje(1);
	cerebot.ActivarConPorcentaje(2);
	cerebot.ActivarConPorcentaje(3);
    }
	
	return 0;
}



//Funcion principal para el hilo de ejecucion del Driver.
//En esta funcion se realizan las operaciones correspondientes al cerebot.
void Robotdriver::Main() {
	//Ciclo principal del Hilo donde se ejecutara la tarea del Driver.
	while (true){
		//Verificamos por si hay orden de paro o termino de ejecucion.
		pthread_testcancel();
		
		//Llamada a nuestra funcion del Driver para procesar mensajes.
		ProcessMessages();
		
		//Leemos el Acelerometro.
		LeerAcelerometro();
		
		//Para no consumir todos los recursos en este hilo,
		//ponemos el proceso a dormir, acorde a la resolucion deseada.
		usleep(100000);
	}
}

void Robotdriver::LeerAcelerometro(){
	Acelerometro= cerebot.LeerAcelerometro();
	uint32_t TamanioSensor = sizeof(Datos) - sizeof(Datos.data) + Datos.data_count;
	Publish (opaqueID, PLAYER_MSGTYPE_DATA, PLAYER_OPAQUE_DATA_STATE, reinterpret_cast<void*>(&Datos), TamanioSensor, NULL);
}

extern "C" {
	int player_driver_init(DriverTable* table){
		puts("Inicializando Player cerebot32MX4");
		Robotdriver_Register(table);
		puts("Driver Player cerebot32MX4 cargado.");
		return(0);
	}
}
