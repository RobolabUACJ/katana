El programa esta comentado lo mejor que pude, el programa en si esta en "main.cpp", se compila solo
con el make file que le agrege para evitar problemas, solo una instruccion que aplica para todos los programas


El codigo no podra hacer nada si no te das permisos sobre el puerto serial, en mi caso era con

sudo chmod 777 /dev/ttyUSB0

es un comando que corres en la terminal donde vas a estar trabajando para que no te ponga peros en los permisos
el driver tiene un error leve, necesitas conectarlo una vez correr ese comando y luego desconectarlo y volverlo
a conectar, no se porque, debe de ser que el driver necesita algun tipo de re-inicio, pero como si jalaba
si lo desconectaba y lo volvia a conectar nunca lo investigue, asi que antes de empezar a trabajar:

Conectar EEG
Abrir una terminal y escribir comando "sudo chmod 777 /dev/ttyUSB0" (sin comillas)
desconectar EEG
conectar EEG volver a escribir "sudo chmod 777 /dev/ttyUSB0" (sin comillas)

LISTO!!!

