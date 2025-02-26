

#ifndef HARDWARE_PROFILE_PIC32MX460F512L_PIM_H
#define HARDWARE_PROFILE_PIC32MX460F512L_PIM_H

    /*******************************************************************/
    /******** USB stack hardware selection options *********************/
    /*******************************************************************/
    //This section is the set of definitions required by the MCHPFSUSB
    //  framework.  These definitions tell the firmware what mode it is
    //  running in, and where it can find the results to some information
    //  that the stack needs.
    //These definitions are required by every application developed with
    //  this revision of the MCHPFSUSB framework.  Please review each
    //  option carefully and determine which options are desired/required
    //  for your application.

    //#define USE_SELF_POWER_SENSE_IO
    #define tris_self_power     TRISAbits.TRISA2    // Input
    #define self_power          1

    //#define USE_USB_BUS_SENSE_IO
    #define tris_usb_bus_sense  TRISBbits.TRISB5    // Input
    #define USB_BUS_SENSE       1 

    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/
    /******** Application specific definitions *************************/
    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/

    /** Board definition ***********************************************/
    //These defintions will tell the main() function which board is
    //  currently selected.  This will allow the application to add
    //  the correct configuration bits as wells use the correct
    //  initialization functions for the board.  These defitions are only
    //  required in the stack provided demos.  They are not required in
    //  final application design.
    #define DEMO_BOARD PIC32_USB_STARTER_KIT




    /** LED ************************************************************/
    #define mInitAllLEDs()      LATB &= 0xC3FF; TRISB &= 0xC3FF;
    
    #define mLED_1              LATBbits.LATB10
    #define mLED_2              LATBbits.LATB11
    #define mLED_3              LATBbits.LATB12
    #define mLED_4              LATBbits.LATB13
    
    #define mGetLED_1()         mLED_1
    #define mGetLED_2()         mLED_2
    #define mGetLED_3()         mLED_3
    #define mGetLED_4()         mLED_4

    #define mLED_1_On()         mLED_1 = 1;
    #define mLED_2_On()         mLED_2 = 1;
    #define mLED_3_On()         mLED_3 = 1;
    #define mLED_4_On()         mLED_4 = 1;
    
    #define mLED_1_Off()        mLED_1 = 0;
    #define mLED_2_Off()        mLED_2 = 0;
    #define mLED_3_Off()        mLED_3 = 0;
    #define mLED_4_Off()        mLED_4 = 0;
    
    #define mLED_1_Toggle()     mLED_1 = !mLED_1;
    #define mLED_2_Toggle()     mLED_2 = !mLED_2;
    #define mLED_3_Toggle()     mLED_3 = !mLED_3;
    #define mLED_4_Toggle()     mLED_4 = !mLED_4;
    
    /** SWITCH *********************************************************/
    #define mInitSwitch2()      TRISAbits.TRISA6=1;
    #define mInitSwitch3()      TRISAbits.TRISA7=1;
    #define mInitAllSwitches()  mInitSwitch2();mInitSwitch3();
    #define sw2                 PORTAbits.RA6
    #define sw3                 PORTAbits.RA7

    /** SERVOS *********************************************************/

    #define cntWdtIdle 15000  	//nominal center of travel, 1.5mS
	#define cntWdtMin 10000     //left stop, 1mS (counter-clockwise limit)
	#define cntWdtMax 20000		//right stop, 2mS (clockwise limit)
	#define cntPulseRate 25000  //(1/50Hz)/(num_servos) -> 20ms/8  -> Timer Clock @ 10MHz -> 25K clocks


    #define	prtServo1		PORTG
    #define	prtServo2		PORTG
    #define	prtServo3		PORTG
    #define	prtServo4		PORTG
	#define	prtServo5		PORTG
	#define	prtServo6		PORTG
	#define	prtServo7		PORTF
	#define	prtServo8		PORTF

	#define	prtServo1_6 	PORTG
	#define	prtServo7_8 	PORTF

	#define	trisServo1		TRISG
	#define	trisServo2		TRISG
	#define	trisServo3		TRISG
	#define	trisServo4		TRISG
	#define	trisServo5		TRISG
	#define	trisServo6		TRISG
	#define	trisServo7		TRISF
	#define	trisServo8		TRISF

	#define	trisServo1_6	TRISG
	#define	trisServo7_8	TRISF

	#define	bnServo1	12
	#define	bnServo2	13
	#define	bnServo3	14
	#define	bnServo4	15
	#define	bnServo5	0
	#define	bnServo6	1
	#define	bnServo7	0
	#define	bnServo8	1

/////////////////////////////////
// Clock Constants
#ifndef SYS_CLOCK
//	#error "Define SYS_CLOCK (ex. -DSYS_CLOCK=80000000) on compiler command line"
#endif
#define GetSystemClock()            (SYS_CLOCK)
#define GetPeripheralClock()        (SYS_CLOCK/2)
#define GetInstructionClock()       (SYS_CLOCK)
#define I2C_CLOCK_FREQ              5000

// EEPROM Constants
#define EEPROM_I2C_BUS              I2C1
#define EEPROM_ADDRESS              0x50        // 0b1010000 Serial EEPROM address
/////////////////////////////	


    /** I/O pin definitions ********************************************/
    #define INPUT_PIN 1
    #define OUTPUT_PIN 0

#endif  //HARDWARE_PROFILE_PIC32MX460F512L_PIM_H
