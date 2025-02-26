//======================= Includes ========================================================================================
#include <p32xxxx.h>
#include <plib.h>
#include<math.h>
#include "usb.h"
#include "HardwareProfile.h"
#include "usb_function_generic.h"
#include "adc.h"
#include "sensores.h"
#ifdef PIC32_STARTER_KIT
    #include <stdio.h>
#endif
#define Pi 3.1416
//====================== Palabra de Configuracion =========================================================================

#pragma config UPLLEN   = ON            // USB PLL Enabled
#pragma config FPLLMUL  = MUL_20        // PLL Multiplier
#pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider
#pragma config FPLLODIV = DIV_1         // PLL Output Divider
#pragma config FPBDIV   = DIV_8         // Peripheral Clock divisor
#pragma config FWDTEN   = OFF           // Watchdog Timer
#pragma config WDTPS    = PS1           // Watchdog Timer Postscale
#pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
#pragma config OSCIOFNC = OFF           // CLKO Enable
#pragma config POSCMOD  = HS            // Primary Oscillator
#pragma config IESO     = OFF           // Internal/External Switch-over
#pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable (KLO was off)
#pragma config FNOSC    = PRIPLL        // Oscillator Selection
#pragma config CP       = OFF           // Code Protect
#pragma config BWP      = OFF           // Boot Flash Write Protect
#pragma config PWP      = OFF           // Program Flash Write Protect
#pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
#pragma config DEBUG    = OFF           // Background Debugger Enable
//#pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor

#define SYSTEM_FREQUENCY	80000000L

// Codigo para encoders
#define ENCHA   _RE0        // encoder channel A
#define ENCHB   _RE4       // encoder channel B
#define FPB_DIV 8
#define FPB     (SYSTEM_FREQUENCY/FPB_DIV)
#define TPMS    (FPB/1000)  // PB clock ticks per ms

// state machine definitions
#define R_IDLE      0
#define R_DETECT    1
volatile int RCount;
static char RState;



//====================== Variables Globales =============================================================================

//unsigned char OUTPacket[64];	//User application buffer for receiving and holding OUT packets sent from the host
//unsigned char INPacket[64];		//User application buffer for sending IN packets to the host
BOOL blinkStatusValid;
USB_HANDLE USBGenericOutHandle;
USB_HANDLE USBGenericInHandle;
//datos_sensores sensores;

unsigned short	cntWdt[8];
unsigned char idChanCur;


//====================== Declaracion de Funciones =======================================================================

static void InitializeSystem(void);
void USBDeviceTasks(void);
void UserInit(void);
void ProcessIO(void);
void BlinkUSBStatus(void);
void ServoInit (void);
void StartServoPulse (void);
void EndServoPulse (void);
void UpdateServoPos(void);
void initR(void);
void Wait_ms(WORD delay);
void Wait_10us(WORD delay);

void i2c_wait (unsigned  int cnt);
float Compas(void);

//====================== Rutinas de Interrupcion ===========================================================================

void __ISR(_TIMER_2_VECTOR, ipl7) _Timer2Handler(void) 
{	
    StartServoPulse();

	IFS0CLR	= ( 1 << 8 ); 	// clear interrupt flag for timer 2
}

void __ISR(_OUTPUT_COMPARE_2_VECTOR, ipl7) OC2_IntHandler (void) 
{
	EndServoPulse();

	IFS0CLR	= ( 1 << 10 );	// clear interrupt flag for output compare 2	
}
//====================== Interrupcion para encoders ==========================================================================
void __ISR( _TIMER_4_VECTOR, ipl1) _T4Interrupt( void)
{
     static char d;
    switch ( RState) {
        default:
        case R_IDLE:       // waiting for CHA rise
            if ( ! ENCHA)
            {
                RState  = R_DETECT;
                if ( ! ENCHB)
                    d = -1;
            }
            else
                d = 1;
            break;

        case R_DETECT:      // waitin for CHA fall
            if ( ENCHA)
            {
                RState = R_IDLE;
                RCount += d;
            }
            break;
    } // switch

    mT4ClearIntFlag();
} // T4 Interrupt

//====================== Rutina Principal (Main) ========================================================================

int main(void)
{
    float USIzq[100], USDer[100], SonDer,SonIzq,SonDerMax, SonDerMin, SonIzqMax, SonIzqMin;
    float AngCompas;
    unsigned int i,k;

	//============= Inicialización de encoders
    int contaencoder;
    _TRISE0=1;_TRISE4=1;
    mLED_4=0;
    // init state machine
    initR();


    InitializeSystem();

    #if defined(USB_INTERRUPT)
        USBDeviceAttach();
    #endif

    while(1)
    {
        #if defined(USB_POLLING)
	    	USBDeviceTasks(); 
        #endif
    				  

		// Application-specific tasks.
		// Application related code may be added here, or in the ProcessIO() function.
        ProcessIO();
        AngCompas=Compas(); // Lee compas y guarda valor en la variable AngCompas

        // Procedimiento AntiMarco de Calibracion
//        EnterCalCompass();
//        mLED_3_On();
//        Nop();
//        ExitCalCompass();
//        mLED_4_On();
//        while(1)
//        {}

//        // Test encoders
//        if(RCount<-90)
//        {
//            mLED_3_On();
//        }
//        else
//        {
//            mLED_3_Off();
//        }
//
//        if(RCount>90)
//        {
//            mLED_4_On();
//        }
//        else
//        {
//            mLED_4_Off();
//        }
//        _nop();   
    }
}

//==================== Funciones ========================================================================================

static void InitializeSystem(void)
{
//	int pbFreq;
	
  //  pbFreq = SYSTEMConfigPerformance(SYSTEM_FREQUENCY); 

	AD1PCFG = 0xFFFF;
   
    #if defined(USE_USB_BUS_SENSE_IO)
    tris_usb_bus_sense = INPUT_PIN; // See HardwareProfile.h
    #endif
    

    #if defined(USE_SELF_POWER_SENSE_IO)
    tris_self_power = INPUT_PIN;	// See HardwareProfile.h
    #endif
    
	USBGenericOutHandle = 0;	
	USBGenericInHandle = 0;		

    UserInit();			//Application related initialization.  See user.c

    USBDeviceInit();	//usb_device.c.  Initializes USB module SFRs and firmware variables to known states.
}

//-----------------------------------------------------------------------------------------------------------

void UserInit(void)
{
    mInitAllLEDs();
    mInitAllSwitches();
    initADC(0xFFF0);
    ServoInit();
    CalibrarAccel();
    CalibrarGyro();
   

    blinkStatusValid = TRUE;	//Blink the normal USB state on the LEDs.
}

//------------------------------------------------------------------------------------------------------------

void ProcessIO(void)
{   
    
    if(blinkStatusValid)
    {
        BlinkUSBStatus();
    }

    if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;
   
    if(!USBHandleBusy(USBGenericOutHandle))		//Check if the endpoint has received any data from the host.
    {
        switch(OUTPacket[0])					//Data arrived, check what kind of command might be in the packet of data.
        {
            case 0x80:                          //Toggle LED(s) command from PC application.
		        blinkStatusValid = FALSE;		//Disable the regular LED blink pattern indicating USB state, PC application is controlling the LEDs.
                if(mGetLED_1() == mGetLED_2())
                {
                    mLED_1_Toggle();
                    mLED_2_Toggle();
                }
                else
                {
                    mLED_1_On();
                    mLED_2_On();
                }

                

                
                  
                break;

            case 0x81:  //Get push button state command from PC application.
               
                INPacket[0] = 0x81;				//Echo back to the host PC the command we are fulfilling in the first byte.  In this case, the Get Pushbutton State command.
				

                if(sw2 == 1)					//pushbutton not pressed, pull up resistor on circuit board is pulling the PORT pin high
				{
					INPacket[1] = 0x01;			
				}
				else							//sw2 must be == 0, pushbutton is pressed and overpowering the pull up resistor
				{
					INPacket[1] = 0x00;
				}				
			   
                if(!USBHandleBusy(USBGenericInHandle))		
	            {	
		            
					USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM,(BYTE*)&INPacket,USBGEN_EP_SIZE);	
                }
                break;

                case 0x37:	//Read POT command.  Uses ADC to measure an analog voltage on one of the ANxx I/O pins, and returns the result to the host
                {
                  
                    Aceleracion(ref);


                    //Posicion();

                    Gyro(ref.rgyro);
                    Temperatura();
                    //Ultrasonico(1);Ultrasonico(2);







	                if(!USBHandleBusy(USBGenericInHandle))
	                {
	                  USBGenericInHandle = USBGenWrite(USBGEN_EP_NUM,(BYTE*)&INPacket,USBGEN_EP_SIZE);
	                }					
                }
                break;

                case 0x38:  // Controlar servos
                {
                    char servo;
                    short velocidad1;
                    unsigned char v1,v2;

                    servo= OUTPacket[1];
                    v1= OUTPacket[2];
                    v2= OUTPacket[3];
                    velocidad1= ((v2<<8) + v1)*10;

                    if(servo<1) servo=1;
                    if(servo>8) servo=8;
                    if(velocidad1<10000) velocidad1=10000;
                    if(velocidad1>20000) velocidad1=20000;

                    cntWdt[servo-1]= velocidad1;
                 }
                 break;

                 case 0x39:  // Controlar servos
                {
	            char servo,vel;
                    short velocidad2;
                     
                    servo= OUTPacket[1];
                    vel= OUTPacket[2];

                    if(servo<1) servo=1;
                    if(servo>8) servo=8;
                    if(vel< -100) vel= -100;
                    if(vel> 100) vel= 100;

                    velocidad2= 15000+(vel*50);
                    cntWdt[servo-1]= velocidad2;
                 }
                 break;

                        case 0x40:  // Controlar servos Omnibot
                {
	            char velx, vely, velang;
                    char servo,vel, phi1, phi2, phi3;
                    short velocidad2;
                    char r=0.45;
                    char R=0.2;


                    velx= OUTPacket[1];
                    vely= OUTPacket[2];
                    velang= OUTPacket[3];
                    phi1= ((-velx*sin(30*Pi/180))+(vely*cos(30*Pi/180))+(R*velang))/r;
                    phi2= ((-velx*sin(150*Pi/180))+(vely*cos(150*Pi/180))+(R*velang))/r;
                    phi3= ((-velx*sin(270*Pi/180))+(vely*cos(270*Pi/180))+(R*velang))/r;
                    INPacket[25]=phi1;
                    INPacket[26]=phi2;
                    INPacket[27]=phi3;

                    if(servo<1) servo=1;
                    if(servo>8) servo=8;
                    if(vel< -100) vel= -100;
                    if(vel> 100) vel= 100;

                    velocidad2= 15000+(vel*50);
                    cntWdt[servo-1]= velocidad2;
                 }
                 break;

                
        }

        USBGenericOutHandle = USBGenRead(USBGEN_EP_NUM,(BYTE*)&OUTPacket,USBGEN_EP_SIZE);
    }
}

//-------------------------------------------------------------------------------------------------------------------

void BlinkUSBStatus(void)  //Dependiendo del estado del usb, parpadean los leds en el cerebot.
{
    static WORD led_count=0;
    
    if(led_count == 0)led_count = 10000U;
    led_count--;

    #define mLED_Both_Off()         {mLED_1_Off();mLED_2_Off();}
    #define mLED_Both_On()          {mLED_1_On();mLED_2_On();}
    #define mLED_Only_1_On()        {mLED_1_On();mLED_2_Off();}
    #define mLED_Only_2_On()        {mLED_1_Off();mLED_2_On();}

   if(USBSuspendControl == 1)
    {
        if(led_count==0)
        {
            mLED_1_Toggle();
            if(mGetLED_1())
            {
                mLED_2_On();
            }
            else
            {
                mLED_2_Off();
            }
        }//end if
    }
    else
    {
        if(USBDeviceState == DETACHED_STATE)
        {
            mLED_Both_Off();
        }
        else if(USBDeviceState == ATTACHED_STATE)
        {
            mLED_Both_On();
        }
        else if(USBDeviceState == POWERED_STATE)
        {
            mLED_Only_1_On();
        }
        else if(USBDeviceState == DEFAULT_STATE)
        {
            mLED_Only_2_On();
        }
        else if(USBDeviceState == ADDRESS_STATE)
        {
            if(led_count == 0)
            {
                mLED_1_Toggle();
                mLED_2_Off();
            }//end if
        }
        else if(USBDeviceState == CONFIGURED_STATE)
        {
            if(led_count==0)
            {
                mLED_1_Toggle();
                if(mGetLED_1())
                {
                    mLED_2_Off();
                }
                else
                {
                    mLED_2_On();
                }
            }
        }
    }

}

//---------------------------------------------------------------------------------------------------------------

void ServoInit(void) 
{
    //Set up the i/o pins we are using for the servo channels as outputs.
	prtServo1_6 &= ~((1 << bnServo1)|(1 << bnServo2)|(1 << bnServo2)|(1 << bnServo3)|\
					(1 << bnServo4)|(1 << bnServo5)|(1 << bnServo6));
	prtServo7_8 &= ~((1 << bnServo7)|(1 << bnServo8));

	trisServo1_6 &= ~((1 << bnServo1)|(1 << bnServo2)|(1 << bnServo2)|(1 << bnServo3)|\
					 (1 << bnServo4)|(1 << bnServo5)|(1 << bnServo6));
	trisServo7_8 &= ~((1 << bnServo7)|(1 << bnServo8));

	//init globals
	cntWdt[0] = cntWdtIdle;
	cntWdt[1] = cntWdtIdle;
	cntWdt[2] = cntWdtIdle;
	cntWdt[3] = cntWdtIdle;
	cntWdt[4] = cntWdtIdle;
	cntWdt[5] = cntWdtIdle;
	cntWdt[6] = cntWdtIdle;
	cntWdt[7] = cntWdtIdle;

	idChanCur = 1;


	// Set up the output compare module
	OC2CON	= ( 1 << 1 ) | ( 1 << 0 ); //Timer2 selected as clock source, events toggle OC2 pin
	OC2R	= cntWdtIdle; //OC2R sets the pulse duration for the currently selected servo
	//Set up output compare interrupt
	IPC2SET = ( 1 << 20 ) | ( 1 << 19 ) | ( 1 << 18 ) | ( 1 << 17 ); //Priority level: 7, sub: 2
	IFS0CLR = ( 1 << 10 ); //clear output compare 2 interrupt flag
	IEC0SET = ( 1 << 10 ); //enable output compare 2 interrupt

	//Set up timer 2
	TMR2 	= 0; //
	PR2		= cntPulseRate; //set the rate of the timer interrupt
	//Set up timer interrupt
	IPC2SET	= ( 1 << 4 ) | ( 1 << 3 ) | ( 1 << 2 ) | ( 1 << 0 );
	IFS0CLR	= ( 1 << 8 );
	IEC0SET	= ( 1 << 8 );

	T2CON		= ( 1 << 15 );
	OC2CONSET	= ( 1 << 15 );

	//Start the first servo pulse, interrupts will take over from there
	prtServo1 |= (1 << bnServo1);  //start beginning pulse of first servo.

	// Enable multi-vector interrupts.
	INTEnableSystemMultiVectoredInt();

}//end AppInit()

//--------------------------------------------------------------------------------------------------------------

void StartServoPulse(void) {

	switch (idChanCur) { 
		case 1: 
			prtServo1 |= (1 << bnServo1);
			OC2R = cntWdt[0];  //load defined pulse width into compare register
		break; 	
	  
		case 2: 
			prtServo2 |= (1 << bnServo2);
			OC2R = cntWdt[1];
		break; 

		case 3: 
			prtServo3 |= (1 << bnServo3);
			OC2R = cntWdt[2];
		break; 

		case 4: 
			prtServo4 |= (1 << bnServo4);
			OC2R = cntWdt[3];
		break; 

		case 5: 
			prtServo5 |= (1 << bnServo5);
			OC2R = cntWdt[4];
		break; 

		case 6: 
			prtServo6 |= (1 << bnServo6);
			OC2R = cntWdt[5];
		break; 

		case 7: 
			prtServo7 |= (1 << bnServo7);
			OC2R = cntWdt[6];
		break; 

		case 8: 
			prtServo8 |= (1 << bnServo8);
			OC2R = cntWdt[7];
		break;  

		default: 
		break; 
   	}//end switch
}//end StartServoPulse function

//-------------------------------------------------------------------------------------------------------------------------------------------------

void EndServoPulse(void) {

	switch (idChanCur) { 
		case 1: 
			prtServo1 &= ~(1 << bnServo1);
		break; 	
	  
		case 2: 
			prtServo2 &= ~(1 << bnServo2);
		break; 

		case 3: 
			prtServo3 &= ~(1 << bnServo3);
		break; 

		case 4: 
			prtServo4 &= ~(1 << bnServo4);
		break; 

		case 5: 
			prtServo5 &= ~(1 << bnServo5);
		break; 

		case 6: 
			prtServo6 &= ~(1 << bnServo6);
		break; 

		case 7: 
			prtServo7 &= ~(1 << bnServo7);
		break; 

		case 8: 
			prtServo8 &= ~(1 << bnServo8);
		break;  

		default: 
		break; 
   	} //end switch

	//The current servo's handling is completed.  Allow interrupt
	//	to address next servo.   
   	if(idChanCur == 8) {
   		idChanCur = 1;
	}
	else {
		idChanCur += 1;
	}
	
}  //end EndServoPulse function

//======================== USB Callback Functions ========================================================================================================================

void USBCBSuspend(void){}          // No se esta declarando, notese los corchetes {}, se debe escribir el codigo que se desee para ese evento del usb
void USBCBWakeFromSuspend(void){}
void USBCB_SOF_Handler(void){}
void USBCBErrorHandler(void){}
void USBCBCheckOtherReq(void){}
void USBCBStdSetDscHandler(void){}

#if 0
void __attribute__ ((interrupt)) _USB1Interrupt(void)
{
    #if !defined(self_powered)
        if(U1OTGIRbits.ACTVIF)
        {
            IEC5bits.USB1IE = 0;
            U1OTGIEbits.ACTVIE = 0;
            IFS5bits.USB1IF = 0;
        
            //USBClearInterruptFlag(USBActivityIFReg,USBActivityIFBitNum);
            USBClearInterruptFlag(USBIdleIFReg,USBIdleIFBitNum);
            //USBSuspendControl = 0;
        }
    #endif
}
#endif

void USBCBInitEP(void)
{
    USBEnableEndpoint(USBGEN_EP_NUM,USB_OUT_ENABLED|USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    USBGenericOutHandle = USBGenRead(USBGEN_EP_NUM,(BYTE*)&OUTPacket,USBGEN_EP_SIZE);
}

void USBCBSendResume(void)
{
    static WORD delay_count;
    
    USBResumeControl = 1;                // Start RESUME signaling
    
    delay_count = 1800U;                // Set RESUME line for 1-13 ms
    do
    {
        delay_count--;
    }while(delay_count);
    USBResumeControl = 0;
}

BOOL USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, WORD size)
{
    switch(event)
    {
        case EVENT_CONFIGURED: 
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_SOF:
            USBCB_SOF_Handler();
            break;
        case EVENT_SUSPEND:
            USBCBSuspend();
            break;
        case EVENT_RESUME:
            USBCBWakeFromSuspend();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        case EVENT_TRANSFER:
            Nop();
            break;
        default:
            break;
    }      
    return TRUE; 
}

void Wait_ms(WORD delay) {

	WORD i;

	while(delay > 0){

		for( i = 0; i < 7270; i ++) {
			_nop(); //Optimization settings can remove empty loops, fill with nops.
		}//end for
		delay -= 1;
	}//end while
}//end Wait_ms()

void Wait_10us(WORD delay) {

	WORD i;

	while(delay > 0){

		for( i = 0; i < 73; i ++) {
			_nop(); //Optimization settings can remove empty loops, fill with nops.
		}//end for
		delay -= 1;
	}//end while
}//end Wait_ms()

//============ 
void initR( void)
{
    // init state machine
    RCount = 0;             // init counter
    RState = 0;             // init state machine

    // init Timer2
    T4CON = 0x8020;         // enable Timer4, Fpb/4
    PR4 = 2*TPMS/4;         // 2 ms period
    mT4SetIntPriority(1);
    mT4ClearIntFlag();
    mT4IntEnable(1);
} // init R
