#include "clases/comunicacion.cpp"
#include "clases/analogo.cpp"
#include "clases/motores.cpp"
 
class superclase:	public comunicacion, 
					public analogo, 
					public motores{
};


