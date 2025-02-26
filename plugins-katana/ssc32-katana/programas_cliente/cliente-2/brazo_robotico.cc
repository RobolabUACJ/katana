/* Laboratorio de Robotica UACJ
   Karen Michel Cangas Ortega
   Descripcion: Programa cliente para manipular el conjunto de eslabones de un 
   brazo robotico por medio de una tarjeta de control Lynxmotion ssc32 */
#include <libplayerc++/playerc++.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <math.h> 

#define  PI		3.1416	// Pi value
#define  S_PORTA	0	// Shoulder port for servo S0A
#define  S_PORTB	1	// Shoulder port for servo S0B
#define  B_PORT		2	// Base port for servo S1
#define  E_PORT		3	// Elbow port for servo S2
#define  W_PORT		4	// Wrist port for servo S4

#define  MAX_ANGLE	90	// Maximum Angle
#define  MIN_ANGLE	-90	// Minimun Angle
#define  MAX_SPEED	300	// Standard Speed
#define  TWIRL		-1	// Clockwise Motion

#define  ERROR_B	50	// 
#define  ERROR_S	-25	//
#define  ERROR_E	50	//
#define  ERROR_W	50	//

#define  S_LENGHT	9.4	// Shoulder lenght in cm
#define  E_LENGHT	9.5	// Elbow lenght in cm
#define  W_LENGHT	13.0	// Wrist lenght in cm

float deg_to_rad (float);		//function to convert degrees to radians

int main()
{
    //================================================================================
    using namespace PlayerCc;
    PlayerClient	lynxmotion		("192.0.1.5", 6665);//Local Server
    Position2dProxy	scc32_control		(&lynxmotion, 0);//DC Motor Interface
    //================================================================================

    unsigned int i, joint, joint_number, b_pulse, s_pulse, e_pulse, w_pulse;
    float b_angle=0, s_angle=0, e_angle=0, w_angle=0;
    int init=0;   
    float angle=0, x, y, z, phi_0, phi_1;

    std::cout << "    Lynxmotion Control   " << std::endl;
    std::cout << "Simple Client Application" << std::endl;
    std::cout << "   Robotics Laboratory   " << std::endl;
    std::cout << "           UACJ          " << std::endl;

    for(;;)
    {
	if (init==0)
	{
	std::cout << "\nInitializing... " << std::endl;
	scc32_control.SetSpeed(S_PORTA, 1500, MAX_SPEED);
	usleep(20000);
	scc32_control.SetSpeed(S_PORTB, 1500, MAX_SPEED);
	usleep(20000);
	scc32_control.SetSpeed(B_PORT, 1500, MAX_SPEED);
	usleep(20000);
	scc32_control.SetSpeed(E_PORT, 1500, MAX_SPEED);
	usleep(20000);
	scc32_control.SetSpeed(W_PORT, 1500, MAX_SPEED);
	usleep(20000);
	init=1;
	std::cout << "Done!" << "\n\n" << std::endl;
	//se inicializan las variables del pulso para evitar datos basura	
	b_pulse=1500;
	s_pulse=1500; 
	e_pulse=1500;
	w_pulse=1500;
	}
	
	std::cout << "Number of joints to move: " << std::endl;
	std::cin >> joint_number;

	if (joint_number > 4)
	std::cout << "\nERROR! " << std::endl;
	else
	{
	   for (i=1; i <= joint_number; i++)
	   {
	    std::cout << "Part to move, select: \n" << std::endl;
	    std::cout << "\t 1: Base      " << std::endl;
    	    std::cout << "\t 2: Shoulder     " << std::endl;
    	    std::cout << "\t 3: Elbow        " << std::endl;
    	    std::cout << "\t 4: Wrist \n --> " << std::endl;
    	    std::cin >> joint;

		if( joint > 4) 
   		std::cout << "ERROR! \n" << std::endl;
	  	else
	   	{
		   std::cout << "\nAngle in degrees: " << std::endl;
	     	   std::cin >> angle;

		   if ( (angle < MIN_ANGLE) || (angle > MAX_ANGLE))
		   std::cout << "\nERROR! " << std::endl;
		   else
		   {
			switch(joint)
		     	{
		     	case 1:	//Base
			b_angle=angle;
			b_pulse = (10*b_angle) + 1500 + ERROR_B;
		     	break;

		     	case 2:	//Shoulder
			s_angle=angle;
		     	s_pulse = (10*s_angle) + 1500 + ERROR_S;
		     	break;

		     	case 3:	//Elbow
			e_angle=angle;
		     	e_pulse = TWIRL*(10*e_angle) + 1500 + ERROR_E;
		     	break;

		     	case 4:	//Wrist
			w_angle=angle;
			w_pulse = (10*w_angle) + 1500 + ERROR_W;
		     	break;
		     	}
		   }
			if (i == joint_number) //Send data to serial port
			{
			std::cout <<"\nCommand: #"<< S_PORTA <<" P"<< s_pulse <<" S"<< MAX_SPEED <<" #"<< S_PORTB <<" P"<< s_pulse <<" S"<< MAX_SPEED<<" #"<< B_PORT <<" P"<< b_pulse <<" S"<< MAX_SPEED <<" #"<< E_PORT <<" P"<< e_pulse <<" S"<< MAX_SPEED <<" #"<< W_PORT <<" P"<< w_pulse <<" S"<< MAX_SPEED<<"\n" << std::endl;
	
		   	scc32_control.SetSpeed(S_PORTA, s_pulse, MAX_SPEED); // Shoulder
		   	usleep(20000);
		   	scc32_control.SetSpeed(S_PORTB, s_pulse, MAX_SPEED); // Shoulder
		   	usleep(20000);
		   	scc32_control.SetSpeed(B_PORT, b_pulse, MAX_SPEED); // Base
		   	usleep(20000);
		   	scc32_control.SetSpeed(E_PORT, e_pulse, MAX_SPEED); // Elbow
		   	usleep(20000);
		   	scc32_control.SetSpeed(W_PORT, w_pulse, MAX_SPEED); // Wrist
		   	usleep(20000);

			phi_0 = deg_to_rad (b_angle);
			phi_1 = deg_to_rad (s_angle);

			x = S_LENGHT*cos(phi_0)*cos(phi_1);
			y = S_LENGHT*sin(phi_1);
			z = S_LENGHT*sin(phi_0)*cos(phi_1);

			std::cout << "Position (x, y, z) = ( " << x << ", " << y << ", " << z << ")" <<"\n" << std::endl;
			}			
		
		}
	   }		
	i=0;
	}	
    }
return 0;
}

float deg_to_rad (float deg)
{
  float radians;
  radians = deg*(PI/180.0);
  return radians;
}




