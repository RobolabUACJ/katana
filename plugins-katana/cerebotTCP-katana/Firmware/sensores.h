//==== sensores.h  Funciones para leer sensores, con salida analogica.

#define saccx readADC(0)
#define saccy readADC(1)
#define stemp readADC(2)
#define sgyro readADC(3)
//#define shum  readADC(5)
//#define sPH   readADC(6)

//Ultrasonic Sensor Definitions
#define FOSC           80E6
#define PB_DIV         2
#define PRESCALE       256
#define MSEC           10E-3
#define T3_TICK        (FOSC)/(PB_DIV * PRESCALE) // (1000 * MSEC* FOSC)/(PB_DIV * PRESCALE)
#define CONVERSION     0.00000658

//Magentic Compass Definition
#define BRG_VAL 0x186 //(FPB/2/Fsck) 0x02F si FPB=10MHz; 0x0C2 si FPB=40MHz: 0x186 FPB=80MHz
#define Nop() _nop()

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

        /*union
        {
            float vph;
            unsigned char dph[4];
        }ph;*/

         union
        {
            float vtemp;
            unsigned char dtemp[4];
        }temp;

        /*union
        {
            float vhum;
            unsigned char dhum[4];
        }hum;

        union
        {
            float vpres;
            unsigned char dpres[4];
        }pres;*/

        union
        {
            float vsonar1;
            unsigned char dsonar1[4];
        }sonar1;

        union
        {
            float vcompass;
            unsigned char dcompass[4];
        }compass;
        
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
unsigned char sdata[20];  //Arreglo para enviar datos sensoriales a traves de TCP.

void CalibrarAccel(void);
void CalibrarGyro(void);
float Aceleracion(calibrar ref);
float Gyro(float);
float Temperatura(void);
void Posicion(void);



