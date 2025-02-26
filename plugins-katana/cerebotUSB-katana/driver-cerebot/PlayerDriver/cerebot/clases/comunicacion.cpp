//Funciones de Conexion
#include "../librerias/cerebot.h"

/** Clase para realizar la conexion al Cerebot.
 *
 *	public:
 *		usb_dev_handle* Buscar()
 *		char Conectar()
 *		void Desconectar()
 *		Conectar()
 *		Desconectar()
 */
class comunicacion{


	public:


	/** Funcion para inicializar el dispositivo USB.
	 *  En este caso, se utiliza esta funcion para inicializar
	 *  el Cerebot, basandonos en el PID y VID del dispositivo
	 *  conectado en el puerto.
	 *
	 *  Argumentos de entrada:
	 * 	Ninguno.
	 *
	 *  Tipo de Dato devuelto:
	 *	Apuntador a dispositivo (usb_dev_handle*)
	 */
	usb_dev_handle* Buscar(){
		struct usb_bus *bus;
		struct usb_device *dev;
	    
		usb_init();		//Inicializamos la libreria USB.
		usb_find_busses();	//Buscamos todos los puertos.
		usb_find_devices();	//Buscamos los dispositivos conectados.

		//Por cada Puerto USB encontrado,
		for (bus = usb_get_busses(); bus; bus = bus->next){
			//Por cada dispositivo conectado en la PC,
			for (dev = bus->devices; dev; dev = dev->next){
				//Si el VID y el PID del dispositivo encontrado coinciden con los declarados,
				//el Cerebot se encuentra conectado.
				if ( (dev->descriptor.idVendor == Cerebot_VID) && (dev->descriptor.idProduct == Cerebot_PID) ){
					printf("Cerebot32MX4 en 04d8:0204 conectado.\n");
					//Regresamos el controlador del Dispositivo.
					return usb_open(dev);
				}
			}
		}
		//En caso de terminar de recorrer todos los puertos y todos los dispositivos
		//y no encontrar nada, regresar un valor nulo.
		return NULL;
	}

	char Conectar(){
		//Buscamos el Cerebot. Si no es encontrado, salimos.
		if ( !(Cerebot = Buscar()) ){
			printf ("Cerebot no encontrado.\n");
			return 0;
		}
		//Actualizando la configuracion del Cerebot.
		//En caso de error, 
		if (usb_set_configuration(Cerebot, 1) < 0){
			printf ("Error de Configuracion. Verifique Permisos.\n");
			usb_close(Cerebot);
			return 0;
		}
		//Peticion de interfaz Cerebot. Debe ser llamada antes de realizar
		//cualquier operacion con la interfaz.
		if (usb_claim_interface(Cerebot, 0) < 0){
			printf("No se pudo completar la peticion de la interfaz del Cerebot.\n");
			usb_close(Cerebot);
			return 0;
		}
		//Si no se presento ningun error, regresamos 1.
		return 1;
	}

	void Desconectar(){
		usb_release_interface(Cerebot, 0);
		usb_close(Cerebot);
	}
};
