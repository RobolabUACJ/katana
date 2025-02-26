#Makefile para compilar el Cliente
#Creado por: Marco Elizalde
#Fecha: 4 de mayo del 2012

all: 
	echo Compilando el Programa Cliente...
	g++ -o RobotClient `pkg-config --cflags playerc++` RobotClient.cpp `pkg-config --libs playerc++`

clean: 
	echo Borrando el Programa Cliente...
	rm RobotClient
