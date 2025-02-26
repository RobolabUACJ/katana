//### Libreria para incluir librerias estandar de C/C++. ###
#ifndef LIBRERIAS_H
	#define LIBRERIAS_H
	
	#include <iostream>
	#include <sys/time.h>
	#include <stdlib.h>  	//for atexit(3),atoi(3)
	//#include <phidget21.h>
	#include <fstream>
	#include <pthread.h>	//for pthread stuff
	#include <sys/ioctl.h>
	#include <stdio.h>
	#include <curses.h>
	#include <math.h>
	#include <time.h>
	#include <assert.h>
	#include <termios.h>
	#include <unistd.h> 	//close(2),fcntl(2),getpid(2),usleep(3),execvp(3),fork(2)
	#include <netdb.h> 		//for gethostbyname(3)
	#include <netinet/in.h> //for struct sockaddr_in, htons(3)
	#include <sys/types.h> 	//for socket(2)
	#include <sys/socket.h>	//for socket(2)
	#include <signal.h>		//for kill(2)
	#include <fcntl.h>		//for fcntl(2)
	#include <string.h> 	//for strncpy(3),memcpy(3)
	#include <libplayercore/playercore.h>
	#include <libplayerc++/playerc++.h>
#endif