/*
 * =====================================================================================
 *
 *       Filename:  switch_poten.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  3/31/2014 12:52:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gregory LI (), vieux113@gmail.com
 *        Company:
 *
 * =====================================================================================
 */

/*	config of switches
 *	config of potential meter
 */
#include <p18F87J11.h>
#include <delays.h>
#include "switch_poten.h"

/*Initialization of switches*/
void switch_Init(void)
{


	/*init RB0*/
	INTCON2bits.RBPU = 0; // enable PORTB internal pullups
	TRISBbits.TRISB0 = 1; // PORTB bit 0 (connected to switch) is input (1)

	/*init RA5*/
	WDTCONbits.ADSHR = 1;
	ANCON0 = 0020;
//	WDTCONbits.ADSHR = 0;
	TRISAbits.TRISA5 = 1;

}//end switch_Init

/*pending for switch release*/
void switch_release(void)
{

	char foo = 0, bar = 0;

	while(1)
	{
		if(SWITCH_0 == 1 && SWITCH_1 == 1)
		{
			Delay10TCYx(100);
			foo++;
		}//end if
		else
			foo = 0;

		if(foo >= 5)
			break;

	}//end while

}//end switch_release

/*Initialization of ADC*/
void ADC_Init1(void)
{ // initialize the Analog-To-Digital converter.
    // First, we need to make sure the AN0 pin is enabled as an analog input
    // as the demo board potentiometer is connected to RA0/AN0
    // Don't forget that RB0/AN12 must be digital!
	WDTCONbits.ADSHR = 1; //Enable write/read to the shared SFR
	ANCON0bits.PCFG0 = 0; // Make Channel 0 - AN0 analog
	WDTCONbits.ADSHR = 0; //Disable write/read to the shared SFR

	ADCON0 = 0b00000000;
	// Sets bits VCFG1 and VCFG0 in ADCON1 so the ADC voltage reference is VSS to VDD
	// Select channel 0 - AN0
    // A/D idle
    // AD converter disabled

	/*the first bit of ADCON1 indicates the result is right justified*/
    ADCON1 = 0b10111001;

    // The ADC clock must as short as possible but still greater than the
    // minimum TAD time, datasheet parameter 130.  At the time this lesson was
    // written TAD minimum for the PIC18F87J11 is 1.4us.
    // At 1MHz clock, selecting ADCS = FOSC/8 = 500kHz.  One clock period
    // 1 / 500kHz = 2us, which is greater than the minimum required 1.4us.
    // So ADCON1 bits ADCS2-0 = 000
    //
    // The ACQT aquisition time should take into accound the internal aquisition
    // time TACQ of the ADC, datasheet paramter 130, and the settling time of
    // of the application circuit connected to the ADC pin.  Since the actual
    // settling time of the RC circuit with the demo board potentiometer is very
    // long but accuracy is not very important to this demo, we'll set ACQT2-0 to
    // 20TAD = 111
    //
    // ADFM = 1 so that the MSB is bit number 7 and the LSB is bit number 0
    // Special Function Register
	ADCON0bits.ADON = 1; // Enable A/D module
	ADCON1bits.ADCAL = 1; // Enable Calibration
	ADCON0bits.GO = 1; // Start dummy A/D conversion calibration
	while(ADCON0bits.GO == 1);
	ADCON1bits.ADCAL = 0;
}


void ADC_Init2(void)
{ // initialize the Analog-To-Digital converter.
    // First, we need to make sure the AN0 pin is enabled as an analog input
    // as the demo board potentiometer is connected to RA0/AN0
    // Don't forget that RB0/AN12 must be digital!
	WDTCONbits.ADSHR = 1; //Enable write/read to the shared SFR
	ANCON0bits.PCFG3 = 0; // Make Channel 3 - AN1 analog
	WDTCONbits.ADSHR = 0; //Disable write/read to the shared SFR

	ADCON0 = 0b00001100;
	// Sets bits VCFG1 and VCFG0 in ADCON1 so the ADC voltage reference is VSS to VDD
	// Select channel 3 - AN3
    // A/D idle
    // AD converter disabled
    ADCON1 = 0b10111001;
    // The ADC clock must as short as possible but still greater than the
    // minimum TAD time, datasheet parameter 130.  At the time this lesson was
    // written TAD minimum for the PIC18F87J11 is 1.4us.
    // At 1MHz clock, selecting ADCS = FOSC/8 = 500kHz.  One clock period
    // 1 / 500kHz = 2us, which is greater than the minimum required 1.4us.
    // So ADCON1 bits ADCS2-0 = 000
    //
    // The ACQT aquisition time should take into accound the internal aquisition
    // time TACQ of the ADC, datasheet paramtdeer 130, and the settling time of
    // of the application circuit connected to the ADC pin.  Since the actual
    // settling time of the RC circuit with the demo board potentiometer is very
    // long but accuracy is not very important to this demo, we'll set ACQT2-0 to
    // 20TAD = 111
    //
    // ADFM = 1 so that the MSB is bit number 7 and the LSB is bit number 0
    // Special Function Register
	ADCON0bits.ADON = 1; // Enable A/D module
	ADCON1bits.ADCAL = 1; // Enable Calibration
	ADCON0bits.GO = 1; // Start dummy A/D conversion calibration
	while(ADCON0bits.GO == 1);
	ADCON1bits.ADCAL = 0;
}


/*	return designated number of bits from MSB,
 *right justified
 */
short poten(unsigned char foo)
{
	// start an ADC conversion and return the 8 most-significant bits of the result
    ADCON0bits.GO_DONE = 1;             // start conversion

	/*pending for ADC completion*/
    while (ADCON0bits.GO_DONE == 1)
		;

	if(foo <= 2)
		return ((((short)ADRESH)<<14)>>(16-foo));
	else
  		return ((((((short)ADRESH)<<8)|ADRESL)<<6)>>(16-foo));
}//end poten


/*`call function msg
 *input info into msg1 and msg2
 */
void msg(char* foo, char* bar)
{
	while(*foo++ = *bar++);
}//end msg






