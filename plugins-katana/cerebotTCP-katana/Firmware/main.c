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
#pragma config FPBDIV   = DIV_2         // Peripheral Clock divisor
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

#define SYSTEM_FREQUENCY	80000000L

//====================== Variables Globales =============================================================================

//unsigned char OUTPacket[64];	//User application buffer for receiving and holding OUT packets sent from the host
//unsigned char INPacket[64];		//User application buffer for sending IN packets to the host
BOOL blinkStatusValid;
USB_HANDLE USBGenericOutHandle;
USB_HANDLE USBGenericInHandle;
//datos_sensores sensores;

unsigned short	cntWdt[8];
unsigned char idChanCur;

//TCPIP Stack:
#define THIS_IS_STACK_APPLICATION
// Include all headers for any enabled TCPIP Stack functions
#include "TCPIP Stack/TCPIP.h"
// Include functions specific to this stack application
#include "MainDemo.h"
// Used for Wi-Fi assertions
#define WF_MODULE_NUMBER   WF_MODULE_MAIN_DEMO
// Declare AppConfig structure and some other supporting stack variables
APP_CONFIG AppConfig;
static unsigned short wOriginalAppConfigChecksum;	// Checksum of the ROM defaults for AppConfig
BYTE AN0String[8];

#include "TCPIPConfig.h"
// Defines which port the server will listen on
#define SERVER_PORT	3000
#define SERVER_PORT2	3001

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

void Wait_ms(WORD);
void ReadSensorData(void);

static void InitAppConfig(void);
static void InitializeBoard(void);

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

//TCPIP Stack
void _general_exception_handler(unsigned cause, unsigned status)
{
	Nop();
	Nop();
}

//====================== Rutina Principal (Main) ========================================================================
int main(void)
{

        //Funciones USB
    InitializeSystem();

    //#if defined(USB_INTERRUPT)
    //    USBDeviceAttach();
    //#endif

    //while(1)
    //{
     //#if defined(USB_POLLING)
	    	//USBDeviceTasks();
     //#endif


		 //Application-specific tasks.
		 //Application related code may be added here, or in the ProcessIO() function.
     //ProcessIO();
     //}

    //TCPIP Stack
    static DWORD t = 0;
    static DWORD dwLastIP = 0;

    // Initialize application specific hardware
    InitializeBoard();

    // Initialize stack-related hardware components that may be
    // required by the UART configuration routines
    TickInit();

    // Initialize Stack and application related NV variables into AppConfig.
    InitAppConfig();

    // Initialize core stack layers (MAC, ARP, TCP, UDP) and
    // application modules (HTTP, SNMP, etc.)
    StackInit();

    // Now that all items are initialized, begin the co-operative
    // multitasking loop.
    while(1)
    {
        // Blink LED0 (right most one) every second.
        if(TickGet() - t >= TICK_SECOND/2ul)
        {
            t = TickGet();
            LED0_IO ^= 1;
        }

        // This task performs normal stack task including checking
        // for incoming packet, type of packet and calling
        // appropriate stack entity to process it.
        StackTask();

        // This tasks invokes each of the core stack application tasks
        StackApplications();

	ProcessIO();

        // If the local IP address has changed (ex: due to DHCP lease change)
        // write the new IP address to the LCD display, UART, and Announce
        // service
	if(dwLastIP != AppConfig.MyIPAddr.Val)
	{
		dwLastIP = AppConfig.MyIPAddr.Val;
		DisplayIPValue(AppConfig.MyIPAddr);
	}
    }
}

//==================== Funciones ========================================================================================
static void InitializeSystem(void)
{
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
void DisplayIPValue(IP_ADDR IPVal)
{
    BYTE IPDigit[4];
    BYTE i;

#ifdef USE_LCD
	BYTE j;
	BYTE LCDPos=16;
#endif
	for(i = 0; i < sizeof(IP_ADDR); i++)
	{
	    uitoa((WORD)IPVal.v[i], IPDigit);

		#if defined(STACK_USE_UART)
			putsUART((char *) IPDigit);
		#endif

		#ifdef USE_LCD
			for(j = 0; j < strlen((char*)IPDigit); j++)
			{
				LCDText[LCDPos++] = IPDigit[j];
			}
			if(i == sizeof(IP_ADDR)-1)
				break;
			LCDText[LCDPos++] = '.';
		#else
			if(i == sizeof(IP_ADDR)-1)
				break;
		#endif

		#if defined(STACK_USE_UART)
			while(BusyUART());
			WriteUART('.');
		#endif
	}
	#ifdef USE_LCD
		if(LCDPos < 32u)
			LCDText[LCDPos] = 0;
		LCDUpdate();
	#endif
}

//-----------------------------------------------------------------------------------------------------------
void UserInit(void)
{
    //mInitAllLEDs();
    mInitAllSwitches();
    initADC(0xFFF0);
    ServoInit();
    CalibrarAccel();
    CalibrarGyro();
    //blinkStatusValid = TRUE;	//Blink the normal USB state on the LEDs.
}

//------------------------------------------------------------------------------------------------------------
void ProcessIO(void)
{
    //cntWdt[0]= 16000;
    //TCPIP Stack
    //#if defined(__C30__) || defined(__C32__)
    // Convert potentiometer result into ASCII string
   // uitoa((WORD)ADC1BUF0, AN0String);
    //#endif

    //USB:
    //if(blinkStatusValid)
    //{
    //    BlinkUSBStatus();
    //}
/*----------------------------------------------------------------------------------------------------------------*/
/*------------INICIO-RUTINAS-TCP-SERVER---------------------------------------------------------------------------*/
	WORD w, w2;
	BYTE AppBuffer[3];
        BYTE AppBuffer2[3];
	WORD wMaxGet, wMaxPut, wCurrentChunk;
        WORD wMaxGet2, wMaxPut2, wCurrentChunk2;
	static TCP_SOCKET Socket, Socket2;
        unsigned short M1vel, M2vel, M1dir, M2dir, M1pwm, M2pwm;
        unsigned short ClientState = 0; //Posibles clientes conectados: 0=Cliente1; 1=Cliente2; 2=Cliente1+Cliente2

	static enum _TCPServerState
	{
		SM_HOME = 0,
		SM_LISTENING,
                SM_CLOSING,
	} TCPServerState = SM_HOME;

	switch(TCPServerState)
	{
		case SM_HOME:
			// Allocate a socket for this server to listen and accept connections on
			Socket = TCPOpen(0, TCP_OPEN_SERVER, SERVER_PORT, TCP_PURPOSE_GENERIC_TCP_SERVER);
                        Socket2 = TCPOpen(0, TCP_OPEN_SERVER, SERVER_PORT2, TCP_PURPOSE_GENERIC_TCP_SERVER);
                        if(Socket == INVALID_SOCKET)
				return;
                        if(Socket2 == INVALID_SOCKET)
				return;
                   
			TCPServerState = SM_LISTENING;
			break;

		case SM_LISTENING:
			// See if anyone is connected to us
			if(TCPIsConnected(Socket))
                        {
                            ClientState = 0;
                            LED1_IO = 1;
                        }
                        if(TCPIsConnected(Socket2))
                        {
                            ClientState = 1;
                            LED2_IO = 1;
                        }
                        if(TCPIsConnected(Socket) && TCPIsConnected(Socket2))
                        {
                            ClientState = 2;
                        }

			// Figure out how many bytes have been received and how many we can transmit.
			wMaxGet = TCPIsGetReady(Socket);	// Get TCP RX FIFO byte count
			wMaxPut = TCPIsPutReady(Socket);	// Get TCP TX FIFO free space
                        wMaxGet2 = TCPIsGetReady(Socket2);	// Get TCP RX FIFO byte count
			wMaxPut2 = TCPIsPutReady(Socket2);	// Get TCP TX FIFO free space

			// Make sure we don't take more bytes out of the RX FIFO than we can put into the TX FIFO
			if(wMaxPut < wMaxGet)
				wMaxGet = wMaxPut;

                        if(wMaxPut2 < wMaxGet2)
				wMaxGet2 = wMaxPut2;

			// Process all bytes that we can
			// This is implemented as a loop, processing up to sizeof(AppBuffer) bytes at a time.
			// This limits memory usage while maximizing performance.  Single byte Gets and Puts are a lot slower than multibyte GetArrays and PutArrays.
			wCurrentChunk = sizeof(AppBuffer);
                        wCurrentChunk2 = sizeof(AppBuffer2);
                        if(ClientState == 0 || ClientState == 2)
                        {
                            for(w = 0; w < wMaxGet; w += sizeof(AppBuffer))
                            {
                                    // Make sure the last chunk, which will likely be smaller than sizeof(AppBuffer), is treated correctly.
                                    if(w + sizeof(AppBuffer) > wMaxGet)
                                            wCurrentChunk = wMaxGet - w;

                                    // Transfer the data out of the TCP RX FIFO and into our local processing buffer.
                                    TCPGetArray(Socket, AppBuffer, wCurrentChunk);
                                    switch(AppBuffer[0])
                                    {
                                        case 0xFA:
                                            M1dir= AppBuffer[1];
                                            M1vel= (unsigned short) AppBuffer[2];
                                            if(M1dir==0)
                                            {
                                                M1pwm=15000+(5000/(100/M1vel));
                                                //M1pwm=15000+1000;  
                                                cntWdt[0]=M1pwm;
                                            }
                                            else
                                            {
                                                M1pwm=15000-(5000/(100/M1vel));
                                                //M1pwm=15000-1000;
                                                cntWdt[0]=M1pwm;
                                            }
                                            //TCPServerState = SM_CLOSING;
                                        break;
                                        case 0xFB:
                                            M2dir= AppBuffer[1];
                                            M2vel= (unsigned short) AppBuffer[2];
                                            if(M2dir==0)
                                            {
                                                M2pwm=15000+(5000/(100/M2vel));
                                                cntWdt[1]=M2pwm;
                                            }
                                            else
                                            {
                                                M2pwm=15000-(5000/(100/M2vel));
                                                cntWdt[1]=M2pwm;
                                            }
                                            //TCPServerState = SM_CLOSING;
                                        break;
                                        case 0xFC:
                                            cntWdt[0]=15100;
                                            cntWdt[1]=15100;
                                            //TCPServerState = SM_CLOSING;
                                        break;
                                        case 0xFF:
                                            ReadSensorData();
                                            TCPPutArray(Socket, sdata, 20);
                                            TCPFlush(Socket);
                                            //TCPServerState = SM_CLOSING;
                                            break;
                                    }
                            }
                        }

                        if(ClientState == 1 || ClientState == 2)
                        {
                            for(w2 = 0; w2 < wMaxGet2; w2 += sizeof(AppBuffer2))
                            {
                                    // Make sure the last chunk, which will likely be smaller than sizeof(AppBuffer), is treated correctly.
                                    if(w2 + sizeof(AppBuffer2) > wMaxGet2)
                                            wCurrentChunk2 = wMaxGet2 - w2;

                                    // Transfer the data out of the TCP RX FIFO and into our local processing buffer.
                                    TCPGetArray(Socket2, AppBuffer2, wCurrentChunk2);
                                    switch(AppBuffer2[0])
                                    {
                                        case 0xFA:
                                            M1dir= AppBuffer2[1];
                                            M1vel= (unsigned short) AppBuffer2[2];
                                            if(M1dir==0)
                                            {
                                                M1pwm=15000+(5000/(100/M1vel));
                                                //M1pwm=15000+1000;
                                                cntWdt[0]=M1pwm;
                                            }
                                            else
                                            {
                                                M1pwm=15000-(5000/(100/M1vel));
                                                //M1pwm=15000-1000;
                                                cntWdt[0]=M1pwm;
                                            }
                                            //TCPServerState = SM_CLOSING;
                                        break;
                                        case 0xFB:
                                            M2dir= AppBuffer2[1];
                                            M2vel= (unsigned short) AppBuffer2[2];
                                            if(M2dir==0)
                                            {
                                                M2pwm=15000+(5000/(100/M2vel));
                                                cntWdt[1]=M2pwm;
                                            }
                                            else
                                            {
                                                M2pwm=15000-(5000/(100/M2vel));
                                                cntWdt[1]=M2pwm;
                                            }
                                            //TCPServerState = SM_CLOSING;
                                        break;
                                        case 0xFC:
                                            cntWdt[0]=15100;
                                            cntWdt[1]=15100;
                                            //TCPServerState = SM_CLOSING;
                                        break;
                                        case 0xFF:
                                            ReadSensorData();
                                            TCPPutArray(Socket2, sdata, 20);
                                            //TCPServerState = SM_CLOSING;
                                            break;
                                    }
                            }
                        }
                        TCPFlush(Socket2);
			break;

		case SM_CLOSING:
			// Close the socket connection.
                        TCPClose(Socket);
			TCPServerState = SM_HOME;
			break;
	}

/*------------FIN-RUTINAS-TCP-SERVER------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------*/

    /*if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;
   
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
    }*/
}

//-------------------------------------------------------------------------------------------------------------------
/****************************************************************************
  Function:
    static void InitializeBoard(void)

  Description:
    This routine initializes the hardware.  It is a generic initialization
    routine for many of the Microchip development boards, using definitions
    in HardwareProfile.h to determine specific initialization.

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
static void InitializeBoard(void)
{
	// LEDs
	LED0_TRIS = 0;
	LED1_TRIS = 0;
	LED2_TRIS = 0;
	LED3_TRIS = 0;
	//LED_PUT(0x00);
        LED1_IO = 0;
        LED2_IO = 0;
        LED3_IO = 0;

#if defined(__PIC32MX__) // 16-bit C30 and and 32-bit C32

	#if defined(__PIC32MX__)
	{
		// Enable multi-vectored interrupts
		INTEnableSystemMultiVectoredInt();

		// Enable optimal performance
		SYSTEMConfigPerformance(GetSystemClock());
		mOSCSetPBDIV(OSC_PB_DIV_1);				// Use 1:1 CPU Core:Peripheral clocks

		// Disable JTAG port so we get our I/O pins back, but first
		// wait 50ms so if you want to reprogram the part with
		// JTAG, you'll still have a tiny window before JTAG goes away.
		// The PIC32 Starter Kit debuggers use JTAG and therefore must not
		// disable JTAG.
		DelayMs(50);
		#if !defined(__MPLAB_DEBUGGER_PIC32MXSK) && !defined(__MPLAB_DEBUGGER_FS2)
			DDPCONbits.JTAGEN = 0;
		#endif
		LED_PUT(0x00);				// Turn the LEDs off

		//CNPUESET = 0x00098000;	// Turn on weak pull ups on CN15, CN16, CN19 (RD5, RD7, RD13), which is connected to buttons on PIC32 Starter Kit boards

                //AD1CHS = 0;					// Input to AN0 (potentiometer)
			/*AD1PCFGbits.PCFG4 = 0;		// Disable digital input on AN4 (TC1047A temp sensor)
			#if defined(__32MX460F512L__) || defined(__32MX795F512L__)	// PIC32MX460F512L and PIC32MX795F512L PIMs has different pinout to accomodate USB module
				AD1PCFGbits.PCFG2 = 0;		// Disable digital input on AN2 (potentiometer)
			#else
				AD1PCFGbits.PCFG5 = 0;		// Disable digital input on AN5 (potentiometer)
			#endif*/
	}
	#endif

	// ADC
	/*AD1CON1 = 0x84E4;			// Turn on, auto sample start, auto-convert, 12 bit mode (on parts with a 12bit A/D)
	AD1CON2 = 0x0404;			// AVdd, AVss, int every 2 conversions, MUXA only, scan
	AD1CON3 = 0x1003;			// 16 Tad auto-sample, Tad = 3*Tcy
	#if defined(__32MX460F512L__) || defined(__32MX795F512L__)	// PIC32MX460F512L and PIC32MX795F512L PIMs has different pinout to accomodate USB module
		AD1CSSL = 1<<2;				// Scan pot
	#else
		AD1CSSL = 1<<5;				// Scan pot
	#endif*/
#endif

// Deassert all chip select lines so there isn't any problem with
// initialization order.  Ex: When ENC28J60 is on SPI2 with Explorer 16,
// MAX3232 ROUT2 pin will drive RF12/U2CTS ENC28J60 CS line asserted,
// preventing proper 25LC256 EEPROM operation.
#if defined(ENC_CS_TRIS)
	ENC_CS_IO = 1;
	ENC_CS_TRIS = 0;
#endif
#if defined(ENC100_CS_TRIS)
	ENC100_CS_IO = (ENC100_INTERFACE_MODE == 0);
	ENC100_CS_TRIS = 0;
#endif
#if defined(SPIRAM_CS_TRIS)
	SPIRAMInit();
#endif
#if defined(EEPROM_CS_TRIS)
	XEEInit();
#endif
#if defined(SPIFLASH_CS_TRIS)
	SPIFlashInit();
#endif
}

//-------------------------------------------------------------------------------------------------------------------
/*********************************************************************
 * Function:        void InitAppConfig(void)
 *
 * PreCondition:    MPFSInit() is already called.
 *
 * Input:           None
 *
 * Output:          Write/Read non-volatile config variables.
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
// MAC Address Serialization using a MPLAB PM3 Programmer and
// Serialized Quick Turn Programming (SQTP).
static ROM BYTE SerializedMACAddress[6] = {MY_DEFAULT_MAC_BYTE1, MY_DEFAULT_MAC_BYTE2, MY_DEFAULT_MAC_BYTE3, MY_DEFAULT_MAC_BYTE4, MY_DEFAULT_MAC_BYTE5, MY_DEFAULT_MAC_BYTE6};
//#pragma romdata
static void InitAppConfig(void)
{
	while(1)
	{
		// Start out zeroing all AppConfig bytes to ensure all fields are
		// deterministic for checksum generation
		memset((void*)&AppConfig, 0x00, sizeof(AppConfig));

		AppConfig.Flags.bIsDHCPEnabled = TRUE;
		AppConfig.Flags.bInConfigMode = TRUE;
		memcpypgm2ram((void*)&AppConfig.MyMACAddr, (ROM void*)SerializedMACAddress, sizeof(AppConfig.MyMACAddr));

		AppConfig.MyIPAddr.Val = MY_DEFAULT_IP_ADDR_BYTE1 | MY_DEFAULT_IP_ADDR_BYTE2<<8ul | MY_DEFAULT_IP_ADDR_BYTE3<<16ul | MY_DEFAULT_IP_ADDR_BYTE4<<24ul;
		AppConfig.DefaultIPAddr.Val = AppConfig.MyIPAddr.Val;
		AppConfig.MyMask.Val = MY_DEFAULT_MASK_BYTE1 | MY_DEFAULT_MASK_BYTE2<<8ul | MY_DEFAULT_MASK_BYTE3<<16ul | MY_DEFAULT_MASK_BYTE4<<24ul;
		AppConfig.DefaultMask.Val = AppConfig.MyMask.Val;
		AppConfig.MyGateway.Val = MY_DEFAULT_GATE_BYTE1 | MY_DEFAULT_GATE_BYTE2<<8ul | MY_DEFAULT_GATE_BYTE3<<16ul | MY_DEFAULT_GATE_BYTE4<<24ul;
		AppConfig.PrimaryDNSServer.Val = MY_DEFAULT_PRIMARY_DNS_BYTE1 | MY_DEFAULT_PRIMARY_DNS_BYTE2<<8ul  | MY_DEFAULT_PRIMARY_DNS_BYTE3<<16ul  | MY_DEFAULT_PRIMARY_DNS_BYTE4<<24ul;
		AppConfig.SecondaryDNSServer.Val = MY_DEFAULT_SECONDARY_DNS_BYTE1 | MY_DEFAULT_SECONDARY_DNS_BYTE2<<8ul  | MY_DEFAULT_SECONDARY_DNS_BYTE3<<16ul  | MY_DEFAULT_SECONDARY_DNS_BYTE4<<24ul;

		// Load the default NetBIOS Host Name
		memcpypgm2ram(AppConfig.NetBIOSName, (ROM void*)MY_DEFAULT_HOST_NAME, 16);
		FormatNetBIOSName(AppConfig.NetBIOSName);

		// Compute the checksum of the AppConfig defaults as loaded from ROM
		wOriginalAppConfigChecksum = CalcIPChecksum((BYTE*)&AppConfig, sizeof(AppConfig));
		break;
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

//-------------------------------------------------------------------------------------------------------------------
void ReadSensorData(void)
{
    unsigned short x;
    //Leer informacion de los sensores (ADC) y ordenarla en el arreglo sdata[].
    Aceleracion(ref);
    Gyro(ref.rgyro);
    Temperatura();
    //Ultrasonico(1);
    //Compass();

    //for (x=0; x<24; x++)
    for (x=0; x<20; x++)
    {
        sdata[x]=INPacket[x+1];
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

	T2CON		= ( 1 << 15 ) | ( 1 << 5 ) | ( 1 << 4 );
	OC2CONSET	= ( 1 << 15 );

	//Start the first servo pulse, interrupts will take over from there
	prtServo1 |= (1 << bnServo1);  //start beginning pulse of first servo.

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

//----------------------------------------------------------------------------------------------------------
void EndServoPulse(void)
{
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

//======================== USB Callback Functions ===================================================================================================
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
