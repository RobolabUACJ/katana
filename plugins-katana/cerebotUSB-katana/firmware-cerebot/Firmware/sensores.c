
#include <plib.h>
#include "adc.h"
#include "sensores.h"

#define FOSC           80E6
#define PB_DIV         8
#define PRESCALE       256
#define MSEC           10E-3
#define T3_TICK       (FOSC)/(PB_DIV * PRESCALE) // (1000 * MSEC* FOSC)/(PB_DIV * PRESCALE)
#define CONVERSION     0.00000658

/////////////////////////////////////////////
////// Define Compas magnetico /////////////
/////////////////////////////////////////////
#define BRG_VAL 0x02F //(FPB/2/Fsck) 0x02F si FPB=10MHz; 0x0C2 si FPB=40MHz
#define Nop() _nop()

void CalibrarAccel(void)
{
    float raccx=0,raccy=0;
    unsigned int vaccx=0, vaccy=0, i=0;

    do{

        vaccx= vaccx + saccx;
        vaccy= vaccy + saccy;
        i++;

    }while(i!=0x0400);

    vaccx= vaccx>>10;
    vaccy= vaccy>>10;

    raccx= (vaccx * 0.003204102 );
    raccy= (vaccy * 0.003204102 );

    ref.raccx= raccx;
    ref.raccy= raccy;



}

void CalibrarGyro(void)
{
    float rgyro=0;
    unsigned int vgyro=0,j=0;

     do{

        vgyro= vgyro + sgyro;

        j++;

    }while(j!=0x0400);

    vgyro= vgyro>>10;

    rgyro= (vgyro * 0.003204102 );

    //0.003204102     3.281/1024
    //0.003222656     3.3/1024

    ref.rgyro= rgyro;
}




float Aceleracion(calibrar ref)
{
    float accx, accy;
    unsigned int filtrox=0,filtroy=0;
    unsigned short k=0;

    do
    {
        filtrox= filtrox + saccx;
        filtroy= filtroy + saccy;
        k++;

    }while(k != 0x40);

        filtrox= filtrox>>6;
        filtroy= filtroy>>6;


    accx= (filtrox * 0.003204102 );
    accy= (filtroy * 0.003204102 );

    accx= accx-ref.raccx;
    accy= accy-ref.raccy;
    
   if((accx <= .007) && (accx >= -.007)) accx=0;
   if((accy <= .007) && (accy >= -.007)) accy=0;

    sensores.accx.vaccx= (accx * 9.81);
    sensores.accy.vaccy= (accy * 9.81);

    // el acelerometro da su salida en gravedades 1g = 9.81 m/s^2

    INPacket[1]= sensores.accx.daccx[0];
    INPacket[2]= sensores.accx.daccx[1];
    INPacket[3]= sensores.accx.daccx[2];
    INPacket[4]= sensores.accx.daccx[3];

    INPacket[5]= sensores.accy.daccy[0];
    INPacket[6]= sensores.accy.daccy[1];
    INPacket[7]= sensores.accy.daccy[2];
    INPacket[8]= sensores.accy.daccy[3]; 


}

float Gyro(float rgyro)
{
    float gyro;
    short i=0;
    unsigned int filtro=0;

    do
    {
         filtro= filtro + sgyro;
         i++;

    }while(i != 0x40);
       
    filtro= filtro>>6;

    gyro= (filtro *0.003204102 );

    gyro= gyro-rgyro;

    gyro= gyro/.015;

    if((gyro <= .7) && (gyro >= -.7)) gyro=0;

    sensores.gyro.vgyro= gyro;


   INPacket[9]= sensores.gyro.dgyro[0];
   INPacket[10]= sensores.gyro.dgyro[1];
   INPacket[11]= sensores.gyro.dgyro[2];
   INPacket[12]= sensores.gyro.dgyro[3]; 


    return gyro;
}

float Temperatura(void)
{
    float temp, tempdif, cgrade;
    unsigned char i;
    int valor=0;

    do
    {
        valor= valor + stemp;
        i++;

    }while(i != 0x40);


    valor= valor>>6;

    temp= valor * 0.0032;
    if(valor>=2.5)
    {
        tempdif= temp-2.5;
        cgrade=tempdif/.0084;
        temp=temp+27;
    }
    else
    {
        tempdif= 2.5-temp;
        cgrade=tempdif/.0084;
        temp=27-temp;
    }

    sensores.temp.vtemp= temp;

    INPacket[13]= sensores.temp.dtemp[0];
    INPacket[14]= sensores.temp.dtemp[1];
    INPacket[15]= sensores.temp.dtemp[2];
    INPacket[16]= sensores.temp.dtemp[3];

    return temp;
}

void Posicion(void)
{

    Aceleracion(ref);

    velx[1]= velx[0]+ paccx+ ((sensores.accx.vaccx - paccx)/2);
    posx[1]= posx[0] + velx[0] + ((velx[1] - velx[0])/2);
    
    vely[1]= vely[0]+ paccy+ ((sensores.accy.vaccy - paccx)/2);
    posy[1]= posy[0] + vely[0] + ((vely[1] - vely[0])/2);

    paccx= sensores.accx.vaccx;
    paccy= sensores.accy.vaccy;

    velx[0]=velx[1];
    vely[0]=vely[1];

    posicion.posx.posx= posx[1];
    posicion.posy.posy= posy[1];

    
    INPacket[17]= posicion.posx.dposx[0];
    INPacket[18]= posicion.posx.dposx[1];
    INPacket[19]= posicion.posx.dposx[2];
    INPacket[20]= posicion.posx.dposx[3];

    INPacket[21]= posicion.posy.dposy[0];
    INPacket[22]= posicion.posy.dposy[1];
    INPacket[23]= posicion.posy.dposy[2];
    INPacket[24]= posicion.posy.dposy[3];

    if (sensores.accx.vaccx==0)   //we count the number of acceleration samples that equals cero
     { countx++;}
    else { countx =0;}
    if (countx>=25)          //if this number exceeds 25, we can assume that velocity is cero
    {
      velx[1]=0;
      velx[0]=0;
    }
    if (sensores.accy.vaccy==0)   //we do the same for the Y axis
    { county++;}
    else { county =0;}
    if (county>=25)
     {
       vely[1]=0;
       vely[0]=0;
     }

    posx[1]=posx[0];
    posy[1]=posy[0];

}


float Ultrasonico(int Identificador)
{
    float CaptureTime1,CaptureTime2;
    float RAWDistancia;
    float Distancia;
    unsigned int i;
    //Espera de 20 mseg para estabilidad de sensor 
    Wait_ms(20);
    if(Identificador==1)    // Sensor Izquierdo Conector JH
    {
// Sensor Ultrasonico 1
// Disparo - RE8
// ECO - RD8
	//Clear interrupt flag
	mIC1ClearIntFlag();
        _RE8=0;
        _TRISD8=1;
        _TRISE8=0;
        _RE8=1;
        // Espera de 10 useg para disparo
        Wait_10us(1);
//        T3CON=0x8000;TMR3=0;
//        do{}while(TMR3<150);
//        TMR3=0;
        _RE8=0;



        // Setup Timer 3
        OpenTimer3(T3_ON | T3_PS_1_256, T3_TICK);

	// Enable Input Capture Module 1
	// - Capture Every edge
	// - Enable capture interrupts
	// - Use Timer 3 source
	// - Capture rising edge first
	OpenCapture1( IC_EVERY_EDGE | IC_INT_1CAPTURE | IC_TIMER3_SRC | IC_FEDGE_RISE | IC_ON );

	// Wait for Capture events
	while( !mIC1CaptureReady() ) ;
        
	//Now Read the captured timer value
	while( mIC1CaptureReady() )
	{
		CaptureTime1 = mIC1ReadCapture();
		//process data
		// ...
	}

	while( !mIC1CaptureReady() ) ;

	//Now Read the captured timer value
	while( mIC1CaptureReady() )
	{
		CaptureTime2 = mIC1ReadCapture();
		//process data
		// ...
	}
        RAWDistancia=(CaptureTime2-CaptureTime1);
        Distancia=RAWDistancia*CONVERSION;
	CloseCapture1();
	CloseTimer3();


    }else if(Identificador==2)  // Sensor Izquierdo Conector JK
    {
        // Sensor Ultrasonico 2
        // Disparo - RA9
        // ECO - RD12
 	//Clear interrupt flag
	mIC5ClearIntFlag();
        _RA9=0;
        _TRISD12=1;
        _TRISA9=0;
        _RA9=1;
        // Espera de 10 useg para disparo
        Wait_10us(1);
//        T3CON=0x8000;TMR3=0;
//        do{}while(TMR3<150);
        TMR3=0;
        _RA9=0;


        // Setup Timer 3
    OpenTimer3(T3_ON | T3_PS_1_256, T3_TICK);

	// Enable Input Capture Module 1
	// - Capture Every edge
	// - Enable capture interrupts
	// - Use Timer 3 source
	// - Capture rising edge first
	OpenCapture5( IC_EVERY_EDGE | IC_INT_1CAPTURE | IC_TIMER3_SRC | IC_FEDGE_RISE | IC_ON );

	// Wait for Capture events
	while( !mIC5CaptureReady() ) ;
        
	//Now Read the captured timer value
	while( mIC5CaptureReady() )
	{
		CaptureTime1 = mIC5ReadCapture();
		//process data
		// ...
	}

	while( !mIC5CaptureReady() ) ;

	//Now Read the captursensoresed timer value
	while( mIC5CaptureReady() )
	{
		CaptureTime2 = mIC5ReadCapture();
		//process data
		// ...
	}
        RAWDistancia=CaptureTime2-CaptureTime1;
        Distancia=RAWDistancia*CONVERSION;
	CloseCapture5();
	CloseTimer3();

    }else // Sensor No valido
    {


    }

    return Distancia;
}

/////////////////////////////////////////////
///////////// Compas magnetico //////////////
/////////////////////////////////////////////
void i2c_wait(unsigned int cnt)
{
    while(--cnt)
    {
        _nop();
        _nop();
    }
}


float Compas(void)
{
    unsigned char SlaveAddress;
    char i2cData[10];
    float ANGULO,ANGDECI;
    int DataSz;
    // Set Periph Bus Divider 60MHz / 8 = 9MHz Fpb
    mOSCSetPBDIV( OSC_PB_DIV_8 );
    //Enable channel
    OpenI2C2( I2C_EN, BRG_VAL );
    SlaveAddress = 0x42;// Compass address
    unsigned char lectura[10];
    unsigned char *rdptr;
    unsigned int longitud, i2c_data_wait;

    // Send Data to eeprom to program one location
    i2cData[0] = SlaveAddress;//EEPROM Device Address and WR Command
    i2cData[1] = 'A';//eeprom location to program (high address byte)
    DataSz = 2;
    StartI2C2();//Send the Start Bit
    IdleI2C2();//Wait to complete
    int Index = 0;
    while( DataSz )
    {
        MasterWriteI2C2( i2cData[Index++] );
        IdleI2C2();//Wait to complete
        DataSz--;
        //ACKSTAT is 0 when slave acknowledge. if 1 then slave has not acknowledge the data.
        if( I2C2STATbits.ACKSTAT )
            break;
    }
    StopI2C2();//Send the Stop condition
    IdleI2C2();//Wait to complete

    Wait_ms(7);
    //now send a start sequence again
    StartI2C2();//Send the Stop condition
    IdleI2C2();//Wait to complete
    MasterWriteI2C2(0x43); //transmit read command
    IdleI2C2();//Wait to complete

    longitud=2;
    rdptr=lectura;
    i2c_data_wait=150;
    MastergetsI2C2(longitud,rdptr,200);
    IdleI2C2();//Wait to complete

    StopI2C2();//Send the Stop condition
    IdleI2C2();//Wait to complete
    ANGDECI=((lectura[0] << 8)+lectura[1]);
    ANGULO=ANGDECI/10;
    return ANGULO;
}

void EnterCalCompass(void)
{
    unsigned char SlaveAddress;
    char i2cData[10];
    float ANGULO,ANGDECI;
    int DataSz;
    // Set Periph Bus Divider 60MHz / 8 = 9MHz Fpb
    mOSCSetPBDIV( OSC_PB_DIV_8 );
    //Enable channel
    OpenI2C2( I2C_EN, BRG_VAL );
    SlaveAddress = 0x42;// Compass address
    unsigned char lectura[10];
    unsigned char *rdptr;
    unsigned int longitud, i2c_data_wait;

    // Send Data to eeprom to program one location
    i2cData[0] = SlaveAddress;//EEPROM Device Address and WR Command
    i2cData[1] = 'C';//eeprom location to program (high address byte)
    DataSz = 2;
    StartI2C2();//Send the Start Bit
    IdleI2C2();//Wait to complete
    int Index = 0;
    while( DataSz )
    {
        MasterWriteI2C2( i2cData[Index++] );
        IdleI2C2();//Wait to complete
        DataSz--;
        //ACKSTAT is 0 when slave acknowledge. if 1 then slave has not acknowledge the data.
        if( I2C2STATbits.ACKSTAT )
            break;
    }
    StopI2C2();//Send the Stop condition
    IdleI2C2();//Wait to complete

    Wait_ms(1);
}

void ExitCalCompass(void)
{
    unsigned char SlaveAddress;
    char i2cData[10];
    float ANGULO,ANGDECI;
    int DataSz;
    // Set Periph Bus Divider 60MHz / 8 = 9MHz Fpb
    mOSCSetPBDIV( OSC_PB_DIV_8 );
    //Enable channel
    OpenI2C2( I2C_EN, BRG_VAL );
    SlaveAddress = 0x42;// Compass address
    unsigned char lectura[10];
    unsigned char *rdptr;
    unsigned int longitud, i2c_data_wait;

    // Send Data to eeprom to program one location
    i2cData[0] = SlaveAddress;//EEPROM Device Address and WR Command
    i2cData[1] = 'E';//eeprom location to program (high address byte)
    DataSz = 2;
    StartI2C2();//Send the Start Bit
    IdleI2C2();//Wait to complete
    int Index = 0;
    while( DataSz )
    {
        MasterWriteI2C2( i2cData[Index++] );
        IdleI2C2();//Wait to complete
        DataSz--;
        //ACKSTAT is 0 when slave acknowledge. if 1 then slave has not acknowledge the data.
        if( I2C2STATbits.ACKSTAT )
            break;
    }
    StopI2C2();//Send the Stop condition
    IdleI2C2();//Wait to complete

    Wait_ms(14);
}

/////////////////////////////////////////////
/////////////////////////////////////////////
