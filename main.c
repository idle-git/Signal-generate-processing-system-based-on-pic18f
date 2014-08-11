#include "p18F87J11.h"
#include "LCD.h"
#include "switch_poten.h"
#include "Delays.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "proc.h"
#include "generator.h"
#pragma config DEBUG = ON, XINST = OFF, STVREN = ON, WDTEN = OFF
#pragma config CP0 = ON
#pragma config IESO = ON, FCMEN = ON, FOSC = INTOSCPLL
#pragma config WDTPS = 1
#pragma config WAIT = OFF, BW = 16, MODE = MM, EASHFT = ON
#pragma config MSSPMSK = MSK7,PMPMX = DEFAULT, ECCPMX = DEFAULT, CCP2MX = DEFAULT
#pragma code
enum {GENERATE, PROCESS, SINUSOIDAL, TRIANGLE, SAWTOOTH, SQUARE,
		LOWPASS, HIGHPASS, BANDPASS, MODULATION, ALLPASS};
/*main*/
void main(void){

	/*	choice -> generator or processor GENERATE*PROCESS
	 *	mode   -> further config SINUSOIDAL*TRIANGLE*SAWTOOTH*SQUARE
	 */
	unsigned char choice = 0, mode = 0, error = 0;
	unsigned char count = 0;
	unsigned short freq_index = 0;
	char msg1[16];
	char msg2[16];

	/*oscillator config*/
	OSCCON = 0366;OSCTUNE = 0337;TRISD = 0;
	/*Init*/
	switch_Init();ADC_Init1();LCD_Reset();
/*----------------------------------------------*/
	/*welcome screen on LCD*/
	welcome:LATD = 0177;
	sprintf(msg1,"---START NOW?---");
	sprintf(msg2,"RB0=NextRA5=Back");
	LCD_Line1(msg1);			/*why is this one void ?!*/
	LCD_Line2(msg2);
	LCD_Line1(msg1);
	while(SWITCH_0 == 1);switch_release();
/*----------------------------------------------*/
	/*filter? siggen? (potentialmeter) */
	primary:LATD = 077;error = 0;
	sprintf(msg1,"--DEVICE TYPE?--");LCD_Line1(msg1);
	do
	{
		/*choice*/
		choice = (unsigned char)poten(1)&1;
		if(choice == GENERATE)sprintf(msg2,"----GENERATOR---");
		else if(choice == PROCESS)sprintf(msg2,"----PROCESSOR---");
		LCD_Line2(msg2);

		/*goto to preivous config*/
		if(SWITCH_1 == 0)
		{
			switch_release();error = 0377;break;
		}//end if
	}while(SWITCH_0 == 1);//end do while
	switch_release();
	if(error)goto welcome;	/*goback detection*/
/*-----------------------------------------------*/
	/*further device config*/
	if(choice == GENERATE)
	{
		wave_type: error=0;// initialize error
		error=wavetype();// run wave type function
		if (error==1) goto primary;// back to primay
		frequency_range: error=0;
		error=frequencyrange();// run fequency function
		if (error==2) {LATD=0b01010101;//debug symbol
						goto wave_type;}//back to wavetype
		if (error==3) goto frequency_range;// back to frequencyrange
        /*your code*/
	}//end if
	else if(choice == PROCESS)
	{
		processor_type:LATD = 037;error = 0;
		error = proc_type(&mode);		/*determine processor type*/
		if(error)goto primary;			/*goback detection*/
		processor_detail:LATD = 017;error = 0;
		ADC_Init1();					/*ADC back to AN0 channel*/
		error = proc_fre(mode,&freq_index);
		if(error)goto processor_type;	/*goback detection*/
		error = proc_exe(mode,freq_index);
		if(error)goto processor_detail;	/*goback detection*/
	}//end else if
}//end main

