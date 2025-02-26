#include <math.h>
#include <stdio.h>

#define		MOTORES		3			//Numero de Motores.
#define		Pi			3.1415926	//Valor de Pi.
#define		r 			0.045		//Radio de la llanta de 10cm.
#define		dt			0.01		//Intervalo entre ordenes.
#define 	R			0.2
//#define		w			1

struct CalculosCinematica{
	float	Phi[MOTORES];		//Velocidades angulares de los motores.
	float	Theta;				//Angulo del robot.
	float	Xk;					//Desplazamiento en X.
	float	Yk;					//Desplazamiento en Y.
	int 	Porcentaje[MOTORES];//Avance por llanta en Porcentaje.
};

typedef		CalculosCinematica		Calc_cin;


//Funcion de Calculos
Calc_cin RealizarCalculos (double Vx, double Vy, double w, Calc_cin t0){
	Calc_cin parameters;		//Parametros nuevos.
	
	parameters.Phi[0]= ((-Vx*sin(30*Pi/180))+(Vy*cos(30*Pi/180))+(R*w))/r;
	parameters.Phi[1]= ((-Vx*sin(150*Pi/180))+(Vy*cos(150*Pi/180))+(R*w))/r;
	parameters.Phi[2]= ((-Vx*sin(270*Pi/180))+(Vy*cos(270*Pi/180))+(R*w))/r;
	
	parameters.Theta=	t0.Theta + (w * dt);
	parameters.Xk= 		t0.Xk + (Vx*dt);
	parameters.Yk= 		t0.Yk + (Vy*dt);

	t0.Theta = parameters.Theta;
	t0.Xk = parameters.Xk;
	t0.Yk = parameters.Yk;
	
	//### Convirtiendo las Aceleraciones Phi a Porcentajes. ##################
	float	XA;		//Factor de Conversion.
	float	XB;
	float	XC;
	//Conversion de Motor 1.
	if (parameters.Phi[0]> 0){
		XA= log(abs(parameters.Phi[0]*30/Pi));
		parameters.Porcentaje[0]= (int) ((79.58158232*(abs(XA)))-393.4254724);
		if(parameters.Porcentaje[0]<0) {parameters.Porcentaje[0]=0;}
		else if(parameters.Porcentaje[0]>100) {parameters.Porcentaje[0]=100;}
	}else if (parameters.Phi[0]< 0){
		XA= log(abs(parameters.Phi[0]*30/Pi));
		parameters.Porcentaje[0]= (int) (-(((47.20890007*(abs(XA)))-211.5465809)));
		if(parameters.Porcentaje[0]>0) {parameters.Porcentaje[0]=0;}
		else if(parameters.Porcentaje[0]<-100) {parameters.Porcentaje[0]=-100;}
	}else{
		parameters.Porcentaje[0]= 0;
	}
	//Conversion de Motor 2.
	if (parameters.Phi[1]> 0){
		XB= log(abs(parameters.Phi[1]*30/Pi));
		parameters.Porcentaje[1]= (int) ((113.3424204*(abs(XB)))-590.6668084);
		if(parameters.Porcentaje[1]<0) {parameters.Porcentaje[1]=0;}
		else if(parameters.Porcentaje[1]>100) {parameters.Porcentaje[1]=100;}	
	}else if (parameters.Phi[1]< 0){
		XB= log(abs(parameters.Phi[1]*30/Pi));
		parameters.Porcentaje[1]= (int) (-(((73.98910389*(abs(XB)))-386.9833981)));
		if(parameters.Porcentaje[1]>0) {parameters.Porcentaje[1]=0;}
		else if(parameters.Porcentaje[1]<-100) {parameters.Porcentaje[1]=-100;}
	}else{
		parameters.Porcentaje[1]= 0;
	}
	//Conversion de Motor 3.
	if (parameters.Phi[2]> 0){
		XC= log(abs(parameters.Phi[2]*30/Pi));
		parameters.Porcentaje[2]= (int) ((95.3248895*(abs(XC)))-301.135696);
		if(parameters.Porcentaje[2]<0) {parameters.Porcentaje[2]=0;}
		else if(parameters.Porcentaje[2]>100) {parameters.Porcentaje[2]=100;}
	}else if (parameters.Phi[2]< 0){
		XC= log(abs(parameters.Phi[2]*30/Pi));
		parameters.Porcentaje[2]= (int) (-(((39.01242581*(abs(XC)))-170.4770377)));
		if(parameters.Porcentaje[2]>0) {parameters.Porcentaje[2]=0;}
		else if(parameters.Porcentaje[2]<-100) {parameters.Porcentaje[2]=-100;}
	}else{
		parameters.Porcentaje[2]= 0;
	}

	//########################################################################
	
	return parameters;
}

float Distancia (float x1, float x0, float y1, float y0){
	return sqrt ((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
}
