#include <cstdio>
#include <iostream>
#include <limits>
#include <string>

#include <unistd.h>
#include <termios.h>
#include <poll.h>

static bool initialized = false;
static struct termios initial_settings;

class Teclado{

	
	public:
		
	
	Teclado(){
		Inicializar();
		BufferLinea( false );
		MostrarCaracter( false );
	}

	bool Inicializar(){
		if (!initialized){
			initialized = (bool)isatty( STDIN_FILENO );
			if (initialized)
				initialized = (0 == tcgetattr( STDIN_FILENO, &initial_settings ));
			if (initialized)
				std::cin.sync_with_stdio();
		}
		return initialized;
	}

	void Finalizar(){
		if (initialized)
			tcsetattr( STDIN_FILENO, TCSANOW, &initial_settings );
	}

	bool BufferLinea( bool on = true ){
		struct termios settings;

		if (!initialized)
			return false;

		if (tcgetattr( STDIN_FILENO, &settings ))
			return false;

		if (on)
			settings.c_lflag |= ICANON;
		else
			settings.c_lflag &= ~(ICANON);

		if (tcsetattr( STDIN_FILENO, TCSANOW, &settings ))
			return false;
		
		if (on)
			setlinebuf( stdin );
		else
			setbuf( stdin, NULL );

		return true;
	}

	bool MostrarCaracter( bool on = true ){
		struct termios settings;

		if (!initialized) 
			return false;

		if (tcgetattr( STDIN_FILENO, &settings ))
			return false;

		if (on)
			settings.c_lflag |= ECHO;
		else
			settings.c_lflag &= ~(ECHO);

		return 0 == tcsetattr( STDIN_FILENO, TCSANOW, &settings );
	}

	bool TeclaPresionada( unsigned timeout_ms = 0 ){
		if (!initialized) return false;

		struct pollfd pls[ 1 ];
		pls[ 0 ].fd     = STDIN_FILENO;
		pls[ 0 ].events = POLLIN | POLLPRI;
		return poll( pls, 1, timeout_ms ) > 0;
	}
	
	void EsperaDejeDePulsar (){
		while (this->TeclaPresionada()== 1){
		}
	}
};
