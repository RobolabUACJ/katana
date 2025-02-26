//============================================//
//                                            //        
//         Simple client Source Code          //
//             Marco A. Elizalde              //
//               Oct 8th, 2012                //
//                                            //
//============================================//

#include <libplayerc++/playerc++.h>
#include <iostream>
#include <stdio.h>
#include "args.h"	//esta libreria sirve para que gHostname, gPort, sean detectadas o se les asigne un valor automaticamente, sin tener que definirlo

int main(int argc, char **argv)
{
  parse_args(argc,argv);

  // We throw exceptions on creation if we fail
  try
  {
    using namespace PlayerCc;
    //Cerebot Interfaces
    PlayerClient	lynxmotion		(gHostname, gPort);//Local Server
    Position2dProxy	scc32_control		(&lynxmotion, gIndex);//DC Motor Interface

    std::cout << "    Lynxmotion Control   " << std::endl;
    std::cout << "Simple Client Application" << std::endl;
    std::cout << "   Robotics Laboratory   " << std::endl;
    std::cout << "           UACJ          " << std::endl;

    int port=31; 
    int	pulse=1500; 
    int	speed=0;

    int init=0;

    for(;;) //hace que el programa cliente se ejecute por tiempo indefinido
    {
	// Inicio de la programacion para el demo del brazo robotico	
	if(init==0)
	{
	//Esta parte del codigo hace que todos los servos giren y se situen a 0 grados
		std::cout << "\nInitializing... " << std::endl;
		scc32_control.SetSpeed(0, 1500, 300);
		usleep(20000);
		scc32_control.SetSpeed(1, 1500, 300);
		usleep(20000);
		scc32_control.SetSpeed(2, 1500, 300);
		usleep(20000);
		scc32_control.SetSpeed(3, 1500, 300);
		usleep(20000);
		scc32_control.SetSpeed(4, 1500, 300);
		usleep(20000);
	//En esta parte del codigo los motores varian de un angulo a otro. Fisicamente se ve que el brazo "baila" 
		for(int x=0;x<5;x++)
		{		
			scc32_control.SetSpeed(0, 1800, 900);
			usleep(1000);
			scc32_control.SetSpeed(1, 1800, 900);
			usleep(1000);
			scc32_control.SetSpeed(2, 2000, 900);
			usleep(1000);
			scc32_control.SetSpeed(3, 2000, 900);
			usleep(1000);
			scc32_control.SetSpeed(4, 2000, 900);
			usleep(2000000);

			scc32_control.SetSpeed(0, 1500, 900);
			usleep(1000);
			scc32_control.SetSpeed(1, 1500, 900);
			usleep(1000);
			scc32_control.SetSpeed(2, 1500, 900);
			usleep(1000);
			scc32_control.SetSpeed(3, 1500, 900);
			usleep(1000);
			scc32_control.SetSpeed(4, 1500, 900);
			usleep(2000000);
		}

		init=1;

		std::cout << "Done!!!" << std::endl;
	} //fin del programa demostracion
	
//En esta parte del codigo se interactua con el usuario el cual manipula el angulo, y extremidad a mover.
	std::cout << "Puerto: " << std::endl;
	std::cin >> port;
	std::cout << "Pulso: " << std::endl;
	std::cin >> pulse;
	std::cout << "Velocidad: " << std::endl;
	std::cin >> speed;

	std::cout << "Comando: #" << port << " P" << pulse << " S" << speed << "\n" << std::endl;

	scc32_control.SetSpeed(port, pulse, speed); //este comando envia los datos capturados por el usuario a la tarjeta lynxmotion

    }
  }
  catch (PlayerCc::PlayerError & e)
  {
	
    std::cerr << e << std::endl;
    return -1;
  }
}
