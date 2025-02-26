/***********************************************************
*							   *
*   Nombre Clase: EEG					   *
*	Descripcion:  Driver para inicializar y leer los   *
*                 datos de un EEG.                         * 
*						           *
\**********************************************************/

#include <iostream>  /*Basic Input Output stream in C++*/
#include <fstream>   /*File stream header for C++*/
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <cstring>

class eeg_driver
{
	int serial_fd;   /* File Descriptor del puerto serial */
private:

public:
	eeg_driver(){}
	~eeg_driver(){}	
	
	int channel_mazinger[36];
	
	void init(const char *serialPort);
	void start();
	void stop();
	void read_data(char *destination);
	void read_data();
	
};
