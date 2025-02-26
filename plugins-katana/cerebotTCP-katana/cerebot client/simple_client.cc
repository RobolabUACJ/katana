//============================================//
//                                            //        
//         Simple client Source Code          //
//             Marco A. Elizalde              //
//              July 10th, 2012               //
//                                            //
//============================================//

//==============================================================================================//
//												//
//	Simple Client Example									//
//	For use with Cerebot32MX4 TCP Firmware & "cerebotII_samurai" Player Driver		//
//												//
//	Usage:											//
//												//
//	There is two basic commands: 1)motor control & 2)read sensory data (from IMU).		//
//	The Position2d function "SetSpeed()" is used as followed:				//
//												//
//	pp.SetSpeed(LeftMotorRatio, RightMotorRatio);						//
//												//
//	Where the "MotorRatio" is a percentage of the speed capacity of the motor & can 	//
//	varies from 100 to -100 (full forward, full backward).					//
//												//
//	The opaque function "GetData ()" is used to read the sense data. The sensor data 	//
//	is arranged in a data structure for correct reading and processing.			//
//												//
//==============================================================================================//

#include <libplayerc++/playerc++.h>
#include <iostream>
#include <stdio.h>
#include "simple_client.h"

#include "args.h"

int main(int argc, char **argv)
{
  int choice;
  int M1vel=0;
  int M2vel=0;

  parse_args(argc,argv);

  // We throw exceptions on creation if we fail
  try
  {
    using namespace PlayerCc;
    //Cerebot Interfaces
    PlayerClient	cerebot			(gHostname, gPort);//Local Server
    Position2dProxy	cerebot_motor		(&cerebot, gIndex);//DC Motor Interface
    OpaqueProxy		cerebot_IMU 		(&cerebot, gIndex);//Sensory Data
    //DSP Interfaces
    /*PlayerClient	dsp			("192.0.0.61", 6666);//Remote Server
    OpaqueProxy		dsp_navigation		(&dsp, 0);//Navigation Lib Interface
    OpaqueProxy		dsp_localization	(&dsp, 1);//Localization Lib Interface
    OpaqueProxy		dsp_mapping		(&dsp, 2);//Mapping Lib Interface
    OpaqueProxy		dsp_sensing		(&dsp, 3);//Sensing Lib Interface*/


    SensorIMU	*IMU;
    SensorIMU	*IMU2;
    uint8_t 	*OpaqueData;
    uint8_t 	*NavigationData;
    uint8_t 	*LocalizationData;
    uint8_t 	*MappingData;
    uint8_t 	*SensingData;

    std::cout << "     Cerebot-Samurai     " << std::endl;
    std::cout << "Simple Client Application" << std::endl;
    std::cout << "   Robotics Laboratory   " << std::endl;
    std::cout << "           UACJ          " << std::endl;

    for(;;)
    {
        cerebot.Read();
	//dsp.Read();

	printf("\nCommand:");
	printf("\n1=M1 FWD - M2 FWD");
	printf("\n2=M1 FWD - M2 BWD");
	printf("\n3=M1 BWD - M2 FWD");
	printf("\n4=M1 BWD - M2 BWD");
	printf("\n5=Full Motor Stop");
	printf("\n6=Read IMU");
	printf("\n7=Sensing (DSP)\n");
	scanf("%d", &choice);
	
	switch(choice)
	{
		M1vel=0;
		M2vel=0;
		case 1:
			M1vel=20;
			M2vel=20;
		break;
		case 2:
			M1vel=20;
			M2vel=-20;
		break;
		case 3:
			M1vel=-20;
			M2vel=20;
		break;
		case 4:
			M1vel=-20;
			M2vel=-20;
		break;
		case 5:
			M1vel=0;
			M2vel=0;
		break;
		case 6:
			OpaqueData = (uint8_t *) calloc (cerebot_IMU.GetCount(), sizeof(IMU));
			cerebot_IMU.GetData(OpaqueData);
			IMU = (SensorIMU *) OpaqueData;
			printf("\nDato de Aceleracion en X: %2.4f\n",IMU->Xaccel.Dato);
			printf("Dato de Aceleracion en y: %2.4f\n",IMU->Yaccel.Dato);
			printf("Dato de Giroscopio: %2.4f\n",IMU->Gyro.Dato);
			printf("Dato de Temperatura: %2.4f\n",IMU->Temp.Dato);
			//printf("Dato de Sonar: %2.4f\n",IMU->Sonar.Dato);
			printf("Dato de Compas: %2.4f\n",IMU->Compass.Dato);
		//break;
		/*case 7:
			SensingData = (uint8_t *) calloc (dsp_sensing.GetCount(), sizeof(IMU2));
			dsp_sensing.GetData(SensingData);
			IMU2 = (SensorIMU *) SensingData;
			printf("\nDato de Aceleracion en X: %2.4f\n",IMU2->Xaccel.Dato);
			printf("Dato de Aceleracion en y: %2.4f\n",IMU2->Yaccel.Dato);
			printf("Dato de Giroscopio: %2.4f\n",IMU2->Gyro.Dato);
			printf("Dato de Temperatura: %2.4f\n",IMU2->Temp.Dato);
			//printf("Dato de Sonar: %2.4f\n",IMU2->Sonar.Dato);
		break;*/
	}
      	cerebot_motor.SetSpeed(M1vel, M2vel);
	usleep(2000);
    }
  }
  catch (PlayerCc::PlayerError & e)
  {
    std::cerr << e << std::endl;
    return -1;
  }
}
