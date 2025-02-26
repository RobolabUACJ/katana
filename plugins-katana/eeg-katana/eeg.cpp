/*******************************************************
*					eeg.cpp							   *
*   Nombre Clase: EEG								   *
*	Descripcion:  Driver para inicializar y leer los   *
*                 datos de un EEG.                     * 
*z													   *
\******************************************************/
#include "eeg.h"

void eeg_driver::init(const char *serialPort)
{
	struct termios options;
	
	serial_fd = open(serialPort, O_RDWR | O_NOCTTY | O_NDELAY);
	
	// Get the current options from the port
	tcgetattr(serial_fd, &options);
	//Set the input/output speed
	cfsetispeed(&options, B921600);
	cfsetospeed(&options, B921600);
	// Enable the receiver and set local mode...
	options.c_cflag |= (CLOCAL | CREAD);

	// Set the default configuration //
	//options.c_cflag &= ~PARENB;
	//options.c_cflag &= ~CSTOPB;
	//options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	options.c_cflag |= CLOCAL;

	options.c_oflag = 0;
	options.c_lflag = 0;
	options.c_cc[VTIME] = 0;
	options.c_cc[VMIN] = 1;

	// Set the new options for the port...
	tcsetattr(serial_fd, TCSANOW, &options);
	tcflush(serial_fd, TCOFLUSH);  
	tcflush(serial_fd, TCIFLUSH);
	fcntl(serial_fd, F_SETFL, FNDELAY); // don't block serial read	
//	result[0] = 0;
}

void eeg_driver::start()
{

	char cmd[3]= {0x08, 0x83, 0x88};
	write(serial_fd, cmd, 3);
}

void eeg_driver::stop()
{
	char cmd[1]={0xFF};
	write(serial_fd, cmd, 1);
	usleep(200*1000);
	close(serial_fd);
}

void eeg_driver::read_data()
{
	unsigned char serialBuffer[36];
	//Contador para todos los datos
	char allDataCnt=0;
	
	bool scanFlag=true;
	// Escaneamos hasta encontrar una cadena valida o escanemos mas de
	// 32 bytes.
	while(scanFlag)
	{
		// Leemos un byte
		read(serial_fd, (void*)serialBuffer, 1); 
		// Verificamos que sea un 0xFF
		if(serialBuffer[0]==0xFF)
		{
			// Leemos otro byte
			read(serial_fd, (void*)serialBuffer, 1);
			if(serialBuffer[0]==0xFF)
			{
//Encontramos las dos 0xFF seguidas, extraemos los 32 bytes restantes
				read(serial_fd, (void*)serialBuffer, 36);
				scanFlag=false;
			}
		}		
	}
//metemos los datos a una variable llamada mazinger y es una matriz	
	for(allDataCnt=0;allDataCnt<18;allDataCnt++) 
	{
		channel_mazinger[allDataCnt] = (serialBuffer[allDataCnt*2]) | ((serialBuffer[(allDataCnt*2)+1] & 0x0F)<<8); 

	}
	//************Seccion de codigo ***********

}
