//==== sensores.h  Funciones para leer sensores, con salida analogica.

#define saccx readADC(0)
#define saccy readADC(1)
#define stemp readADC(2)
#define sgyro readADC(3)
#define shum  readADC(5)
#define sPH   readADC(6)


typedef struct
{
    char  comando;

        union
        {
            float vaccx;
            unsigned char daccx[4];
        }accx;

        union
        {
            float vaccy;
            unsigned char daccy[4];
        }accy;

        union
        {
            float vgyro;
            unsigned char dgyro[4];
        }gyro;

        union
        {
            float vph;
            unsigned char dph[4];
        }ph;

         union
        {
            float vtemp;
            unsigned char dtemp[4];
        }temp;

        union
        {
            float vhum;
            unsigned char dhum[4];
        }hum;

        union
        {
            float vpres;
            unsigned char dpres[4];
        }pres;
  
}datos_sensores;

typedef struct
{
    float raccx;
    float raccy;
    float rgyro;

}calibrar;

typedef struct
{
    union
    {
        float posx;
        unsigned char dposx[4];

    }posx;

    union
    {
        float posy;
        unsigned char dposy[4];

    }posy;

}estado;

calibrar ref;
datos_sensores sensores;
estado posicion;


float paccx, paccy;
float velx[2],vely[2];
float posx[2],posy[2];
char countx,county;

unsigned char OUTPacket[64]; //User application buffer for receiving and holding OUT packets sent from the host
unsigned char INPacket[64];  //User application buffer for sending IN packets to the host

void CalibrarAccel(void);
void CalibrarGyro(void);
float Aceleracion(calibrar ref);
float Gyro(float);
float Temperatura(void);
void Posicion(void);

float Ultrasonico(int Identificador);

