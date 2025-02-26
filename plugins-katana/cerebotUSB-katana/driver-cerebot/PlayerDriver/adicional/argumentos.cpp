//### Cabeceras estandar. ###
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//### Cabeceras propias. ###
#include "Omnibot_player.h"

void revisarArgumentos (int argc, char **argv){
	int opcion;
	
	/** Parametros leidos:
	 *		Parametros para player.
	 *			h: Host		IP del Robot.
	 *			p: Puerto	Puerto en el que nos conectaremos.
	 *			j: Joystick	Puerto del control de PS2.
	 *		Parametros para el Cerebot:
	 *			De momento ninguno.
	 */
	
	while ((opcion= getopt (argc, argv, "h:p:j:")) != -1){
		switch (opcion){
			case 'h':
				Omnibot_Host= optarg;
				break;
			case 'p':
				Omnibot_Puerto = atoi(optarg);
				break;
			//case 'j':
			//	Cortana_Player_Puerto = optarg;
			//	break;
		}
	}
}
