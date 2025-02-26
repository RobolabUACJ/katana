#include <iostream>
#include <signal.h>
#include <libplayerc++/playerc++.h>
#include "args.h"
#include "eeg.h"

static bool exit_flag=true;
static bool configuracion=false;
int Tha=0;
int Thi=0;
int Thd=0;
float adelante=0;
float angular=0;
/*
 * Esto para el programa si presionamos Control+C
 */
void intr_hdlr(int sig)
{
	std::cout<<"Ctrl+C Caught!!! ... Closing"<<std::endl;
    exit_flag = true;

}
    using namespace PlayerCc;

int main(int argc, char** argv)
{
	/**** Definicion de objetos ****/
    parse_args(argc, argv);
    signal(SIGINT, intr_hdlr);

	// Creamos el objeto EEG 
	eeg_driver eeg;
	/**** Inicializacion de los objetos ****/
	eeg.init("/dev/ttyUSB0");
	eeg.start();

	/****   Seccion de codigo ****/		


	
	 /**********************************
	 *   Seccion De Autocalibracion    *
	 **********************************/
		

	while(configuracion==false)
	{	
	for(int i=0; i<1500; i++)
	{
	eeg.read_data();		
	if(Tha<eeg.channel_mazinger[3])	
	{
	Tha=eeg.channel_mazinger[3];
	printf("%d Tha", Tha);
	printf("\n");	
	}
	}
	printf("Pienza izquierda");
	printf("\n");	
	for(int x=0; x<1500; x++)
	{
	eeg.read_data();		
	if(Thi<eeg.channel_mazinger[5])	
	{
	Thi=eeg.channel_mazinger[5];
	printf("%d Thi", Thi);
	printf("\n");	
	}
	} 
	printf("Pienza derecha");
	printf("\n");	
	for(int z=0; z<1500; z++)
	{
	eeg.read_data();		
	if(Thd<eeg.channel_mazinger[17])	
	{
	Thd=eeg.channel_mazinger[17];
	printf("%d Thd", Thd);
	printf("\n");	
	}
	} 	
	configuracion=true;
	}
	
	/*************************************************
	*   Seccion del Codigo			         *
	*   Main loop                                    *
	*************************************************/


	PlayerCc::PlayerClient    robot("localhost", gPort);
	PlayerCc::Position2dProxy pp(&robot, gIndex);  
 	exit_flag=false;

while(exit_flag==false)
	{
        eeg.read_data();
		
		 if(eeg.channel_mazinger[3] > (Tha-50))      		{
		   pp.SetMotorEnable(true);
		   pp.SetSpeed(1, 0);
		}

		else if (eeg.channel_mazinger[5] > (Thi-88)) 
		{
		   pp.SetMotorEnable(true);
		   pp.SetSpeed(0, 1);
		}
		
		else if(eeg.channel_mazinger[17] > (Thd-40))

		{
		   pp.SetMotorEnable(true);
		   pp.SetSpeed(0, -1);
                 
		}


		
	}
		
		eeg.stop();	
		return 0;	

}
