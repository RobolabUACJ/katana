//Original Obtenido de 
//http://www.gnu.org/s/libc/manual/html_node/Elapsed-Time.html
//###################################################################################

//### Funciones para calcular tiempos. ###

//Redefiniendo la "struct timeval" como "tiempo", solo para ahorrarnos escribir mas.
typedef		struct timeval		tiempo;

char diferenciaTiempo(tiempo inicio, tiempo fin, tiempo *diferencia){
	//Si los microsegundos en el tiempo inicial son mas que en el tiempo final,
	if (inicio.tv_usec> fin.tv_usec){
		//Vemos cuantos segundos se forman de la diferencia de microsegundos,
		//y le sumamos +1 a esa diferencia.
		int numSegundos= (inicio.tv_usec - fin.tv_usec) / 1000000 + 1;
		//Le restaremos a el tiempo inicial los microsegundos correspondientes a numSegundos,
		inicio.tv_usec-= (numSegundos * 1000000);
		//Y le sumaremos los numSegundos a los segundos del tiempo inicial.
		inicio.tv_sec+= numSegundos;
		//De esta forma, los microsegundos son menores que en el tiempo final, y ya se
		//puede calcular la diferencia de los microsegundos.
	}
	
	//Verificamos que el tiempo entre los microsegundos final e inicial sea inferior 
	//a 1,000,000 us. Si es mayor a 1,000,000, ya son segundos, por lo cual convertimos
	//esos microsegundos a segundos.
	if ( (fin.tv_usec - inicio.tv_usec) > 1000000){
		//El numero de segundos esta definido por la diferencia entre el valor de
		//los microsegundos del tiempo final e inicial.
		int numSegundos= (fin.tv_usec - inicio.tv_usec) / 1000000;
		//Le sumamos al tiempo inicial los microsegundos necesarios,
		inicio.tv_usec+= (numSegundos * 1000000);
		//Y le restamos los segundos equivalentes.
		inicio.tv_sec-= numSegundos;
	}
	
	//Obtenemos la diferencia entre el tiempo final y el tiempo inicial.
	diferencia->tv_sec= fin.tv_sec - inicio.tv_sec;
	diferencia->tv_usec= fin.tv_usec - inicio.tv_usec;
	
	//Si el tiempo inicial es mayor al final,
	if (inicio.tv_sec > fin.tv_sec){
		//mandamos un mensaje de error.
		return -1;
	}else{
		//En caso contrario, mandamos un cero de terminacion normal.
		return 0;
	}
}

void obtenerHora (timeval *tiempo){
	gettimeofday (tiempo, NULL);
}