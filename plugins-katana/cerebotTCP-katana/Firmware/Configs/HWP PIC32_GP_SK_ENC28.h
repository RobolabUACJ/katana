/************************************************************************/
/*                                                                      */
/*		HardwareProfileCerebot32MX4PmodNIC.h			*/
/*                                                                      */
/*                                                                      */
/************************************************************************/
/*	Author: 	Jesse Adams                                     */
/*	Copyright 2011, Digilent Inc.					*/
/************************************************************************/
/*  Module Description: 						*/
/*                                                                      */
/*This file contains hardware descriptions for the Cerebot 32MX4 and    */
/*the PmodNIC.								*/
/*                                                                      */
/************************************************************************/
/*  Revision History:						        */
/*                                                                      */
/*	01/13/2010 (JesseA): created			                */
/*                                                                      */
/************************************************************************/

#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H

#include "../Compiler.h"

// Define a macro describing this hardware set up (used in other files)
#define CEREBOT32MX4

// Set configuration fuses (but only in MainDemo.c where THIS_IS_STACK_APPLICATION is defined)
#if defined(THIS_IS_STACK_APPLICATION)
	#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FPBDIV = DIV_1, POSCMOD = XT, FNOSC = PRIPLL, CP = OFF, FSOSCEN = OFF, IESO = OFF
#endif


// Clock frequency values
// These directly influence timed events using the Tick module.  They also are used for UART and SPI baud rate generation.
#define GetSystemClock()		(80000000L)			// Hz
#define GetInstructionClock()	(GetSystemClock()/1)	// Normally GetSystemClock()/4 for PIC18, GetSystemClock()/2 for PIC24/dsPIC, and GetSystemClock()/1 for PIC32.  Might need changing if using Doze modes.
#define GetPeripheralClock()	(GetSystemClock()/1)	// Normally GetSystemClock()/4 for PIC18, GetSystemClock()/2 for PIC24/dsPIC, and GetSystemClock()/1 for PIC32.  Divisor may be different if using a PIC32 since it's configurable.

// Hardware I/O pin mappings

// CEREBOT 32MX4 + PIC32MX460F512L + PmodNIC (ENC28J60)connected to SPI2 (port JB of the board)

#define LED0_TRIS			(TRISBbits.TRISB10)
#define LED0_IO				(LATBbits.LATB10)
#define LED1_TRIS			(TRISBbits.TRISB11)
#define LED1_IO				(LATBbits.LATB11)
#define LED2_TRIS			(TRISBbits.TRISB12)
#define LED2_IO				(LATBbits.LATB12)
#define LED3_TRIS			(TRISBbits.TRISB13)
#define LED3_IO				(LATBbits.LATB13)
#define LED_GET()			(*((volatile unsigned char*)(&LATB)))
#define LED_PUT(a)			(*((volatile unsigned char*)(&LATB)) = (a))

//Buttons on digilent boards read Logic High when they are pressed and Logic Low when not.  This is opposite of Microchip development boards.
#define BUTTON0_TRIS		(TRISAbits.TRISA6)
#define	BUTTON0_IO			!(PORTAbits.RA6)
#define BUTTON1_TRIS		(TRISAbits.TRISA7)
#define	BUTTON1_IO			!(PORTAbits.RA7)

#define UARTTX_TRIS			(TRISFbits.TRISF5)	// This is connected to pin 4 of JH on the Cerebot 32MX4
#define UARTTX_IO			(PORTFbits.RF5)
#define UARTRX_TRIS			(TRISFbits.TRISF4)	// This is connected to pin 3 of JH on the Cerebot 32MX4
#define UARTRX_IO			(PORTFbits.RF4)

// Encoder
#define ENC_IN_SPI2

// ENC28J60 I/O pins
#define ENC_CS_TRIS			(TRISGbits.TRISG9)	// Pin 1 on the PmodNIC.  Pin JB1 of Cerebot 32MX4.
#define ENC_CS_IO			(PORTGbits.RG9)
#define ENC_RST_TRIS                    (TRISDbits.TRISD4)	// Pin 9 on the PmodNIC.  Pin JB9 of the Cerebot 32MX4.
#define ENC_RST_IO			(PORTDbits.RD4)
// SPI SCK, SDI, SDO pins are automatically controlled by the
//PIC32 SPI module
//SPI2 definitions
#define ENC_SPI_IF			(IFS1bits.SPI2RXIF)
#define ENC_SSPBUF			(SPI2BUF)
#define ENC_SPISTATbits             (SPI2STATbits)
#define ENC_SPICON1			(SPI2CON)
#define ENC_SPICON1bits             (SPI2CONbits)
#define ENC_SPIBRG			(SPI2BRG)

 /** SERVOS *********************************************************/

    #define cntWdtIdle 15100  	//nominal center of travel, 1.5mS
	#define cntWdtMin 10000     //left stop, 1mS (counter-clockwise limit)
	#define cntWdtMax 20000		//right stop, 2mS (clockwise limit)
	#define cntPulseRate 30000  //(1/42.67Hz)/(num_servos) -> 24ms/8  -> Timer Clock @ 10MHz -> 30K clocks


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

#endif