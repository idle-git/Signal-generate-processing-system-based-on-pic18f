#include "p18F87J11.h"
#include "LCD.h"
#include "switch_poten.h"
#include "Delays.h"
#include "stdio.h"
#include "math.h"
#include "proc.h"


#pragma romdata
const rom char pa_5order[16][3] = {8,1,1,
								8,2,2,
								5,11,7,
								0,12,12,
								-4,10,17,
								-9,8,17,
								-6,-5,20,
								-3,-9,-21,	
	
								-4,-12,-18,
								2,-10,-21,
								4,-8,-20,
								5,-6,-20,
								8,0,-18,
								4,10,-18,
								1,12,-12,
								-8,2,-3};

const rom char pa_7order[8][4] = {-5,-7,0,8,
								 -1,-8,-3,8,						
								3,-6,-6,7,
								6,-3,-8,6,
								5,1,-9,6,
								-1,-8,-4,11,
								2,-7,-7,10,
								3,1,-11,8}; 
const rom unsigned char sin_32[32] = {128,152,176,198,217,233,245,252,
									254,252,245,233,217,198,176,152,
									127,103,79,57,38,22,10,3,
									1,3,10,22,38,57,79,103};


#pragma udata
#pragma idata
//char msg3[16], msg4[16];
enum {GENERATE, PROCESS, SINUSOIDAL, TRIANGLE, SAWTOOTH, SQUARE,
		LOWPASS, HIGHPASS, BANDPASS, MODULATION, ALLPASS};


#pragma code
/*	call function proc_type()------------------------------------------------
 *this function is called when the signal processor
 *is selected, any will return the choice of filter
 *to the caller
 */
unsigned char proc_type(unsigned char* foo)
{

	char msg1[16], msg2[16];
	sprintf(msg1,"-PROCESSOR TYPE-");
	LCD_Line1(msg1);
	do
	{
		/*choice*/
		*foo = (1<<1)+(1<<2)+((poten(5)*5)>>5);
		switch(*foo)
		{
			case LOWPASS:sprintf(msg2,"-----LOWPASS----");break;
			case HIGHPASS:sprintf(msg2,"----HIGHPASS---");break;
			case BANDPASS:sprintf(msg2,"----BANDPASS---");break;
			case MODULATION:sprintf(msg2,"---MODULATION--");break;
			case ALLPASS:sprintf(msg2,"-----ALLPASS----");break;
			default:sprintf(msg2,"------VOID-----");break;
		}//end switch
		LCD_Line2(msg2);

		/*goto previous config*/
		if(SWITCH_1 == 0)
		{
			switch_release();
			return 0377;
		}//end if
	}while(SWITCH_0 == 1);
	switch_release();
	return 0;
}//end proc_type


/*	call function proc_fre()---------------------------------------------------
 *this call function intake the variable contains the type of the frequency 
 *return the corresponding index of filter parameters
 */
unsigned char proc_fre(unsigned char type, unsigned short* para_choice)
{
	unsigned short reading = 0;
	unsigned int temp;
	char msg1[16], msg2[16];

	switch(type)	
	{
		/*LP*/
		case LOWPASS:
			sprintf(msg1,"----PASSBAND?---");
			LCD_Line1(msg1);	
			do
			{
				reading = poten(3);
				switch(reading)
				{
					case 0:sprintf(msg2,"-----0~500Hz----");break;				
					case 1:sprintf(msg2,"-----0~1kHz-----");break;
					case 2:sprintf(msg2,"-----0~2kHz-----");break;
					case 3:sprintf(msg2,"-----0~3kHz-----");break;
					case 4:sprintf(msg2,"-----0~4kHz-----");break;				
					case 5:sprintf(msg2,"-----0~5kHz-----");break;
					case 6:sprintf(msg2,"-----0~6kHz-----");break;
					case 7:sprintf(msg2,"-----0~7kHz-----");break;
					default:break;
				}//end switch
				*para_choice = reading;
				LCD_Line2(msg2);
						
				/*goto previous config*/
				if(SWITCH_1 == 0)
				{
					switch_release();
					return 0377;
				}//end if
			}while(SWITCH_0 == 1);
			switch_release();
			return 0;
		
		/*HP*/
		case HIGHPASS:
			sprintf(msg1,"----STOPBAND?---");
			LCD_Line1(msg1);	
			do
			{
				reading = poten(3);
				switch(reading)
				{
					case 0:sprintf(msg2,"-----0~500Hz----");break;				
					case 1:sprintf(msg2,"-----0~1kHz-----");break;
					case 2:sprintf(msg2,"-----0~1.5kHz---");break;
					case 3:sprintf(msg2,"-----0~2kHz-----");break;
					case 4:sprintf(msg2,"-----0~3kHz-----");break;				
					case 5:sprintf(msg2,"-----0~4kHz-----");break;
					case 6:sprintf(msg2,"-----0~5kHz-----");break;
					case 7:sprintf(msg2,"-----0~7kHz-----");break;
					default:break;
				}//end switch
				*para_choice = reading;
				LCD_Line2(msg2);
				
				/*goto previous config*/
				if(SWITCH_1 == 0)
				{
					switch_release();
					return 0377;
				}//end if
			}while(SWITCH_0 == 1);
			switch_release();
			return 0;

		/*BP*/
		case BANDPASS:
			sprintf(msg1,"----PASSBAND?---");
			LCD_Line1(msg1);	
			do
			{
				reading = poten(3);
				switch(reading)
				{
					case 0:sprintf(msg2,"-1.5kHz~3.5kHz--");break;				
					case 1:sprintf(msg2,"---2kHz~4kHz----");break;
					case 2:sprintf(msg2,"--2.5kHz~4.5kHz-");break;
					case 3:sprintf(msg2,"----3kHz~5kHz---");break;
					case 4:sprintf(msg2,"-3.5kHz~5.5kHz--");break;				
					case 5:sprintf(msg2,"--1.5kHz~4.5kHz-");break;
					case 6:sprintf(msg2,"---2kHz~5kHz----");break;
					case 7:sprintf(msg2,"---3kHz~6kHz----");break;
					default:break;
				}//end switch
				*para_choice = reading;
				LCD_Line2(msg2);
				
				/*goto previous config*/
				if(SWITCH_1 == 0)
				{
					switch_release();
					return 0377;
				}//end if
			}while(SWITCH_0 == 1);
			switch_release();
			return 0;

		/*MO*/
		case MODULATION:
			sprintf(msg1,"--CARRIER_FRE?--");
			LCD_Line1(msg1);	
			do
			{
				reading = poten(10);
				*para_choice = reading;	
				temp = reading/1023.0*850+10;
				sprintf(msg2,"------%3dHz------",(int)temp);
				LCD_Line2(msg2);

				/*goto previous config*/
				if(SWITCH_1 == 0)
				{
					switch_release();
					return 0377;
				}//end if
			}while(SWITCH_0 == 1);
			switch_release();
			return 0;

		/*AP*/
		case ALLPASS:
			sprintf(msg1,"RB0->CONTINUE---");
			sprintf(msg2,"RA5->RETURN-----");
			LCD_Line1(msg1);
			LCD_Line2(msg2);
			do
			{
				if(SWITCH_1 == 0)
				{
					switch_release();
					return 0377;
				}//end if
			}while(SWITCH_0 == 1);
			switch_release();
			return 0;

		/*ER*/
		default:
			/*err msg*/
			sprintf(msg1,"ERROR");
			LCD_Line1(msg1);
			break;

	}//end switch
}//end proc_fre





/*	processor execution function
 *this call function intake the type of processor
 *this call function intake the frequency of processor
 *this function output the processed signal in unsigned char LATD
 */
unsigned char proc_exe(unsigned char type, unsigned short index)
{

	short y=0,x_6=0,x_5=0,x_4=0,x_3=0,x_2=0,x_1=0,x_0=1;
	short pa1,pa2,pa3,pa4;	/*filter parameters*/
	unsigned char idx = 0, count = 0;
	
	short temp;
	double delay_sum = 0, freq = 0;
	int delay_index = 0;

	char msg1[16], msg2[16];
	unsigned char sin_320[32];
	LATD = 0377;
	ADC_Init2();

	/*AP*/
	if(type == ALLPASS)
	{
		while(1)
		{		
			LATD = (unsigned char)(poten(10)>>2);
			if(SWITCH_1 == 0)
			{
				switch_release();
				return 0377;
			}//end if
		}//end while
	}//end if


	if(type == LOWPASS)		/*LP*/
	{

		pa1 = pa_5order[index][0];
		pa2 = pa_5order[index][1];
		pa3 = pa_5order[index][2];
		while(1)
		{
			/*exeution*/
			y = pa1*(x_4+y)+pa2*(x_3+x_0)+pa3*(x_2+x_1);
			LATD = (unsigned char)((unsigned short)(y+0100000)>>010);
			y = (short)((((unsigned short)(y+0100000))>>06)-01000);
			x_4 = x_3;x_3 = x_2;x_2 = x_1;x_1 = x_0;
			x_0 = poten(10);x_0 -= 01000;
			/*goto previous*/
			if(SWITCH_1 == 0)
			{
				switch_release();
				return 0377;
			}//end if
		}//end while
	}//end if
	else if(type == HIGHPASS)
	{

		pa1 = pa_5order[index+8][0];
		pa2 = pa_5order[index+8][1];
		pa3 = pa_5order[index+8][2];

		while(1)
		{

			/*exeution*/
			y = pa1*(x_4-y)+pa2*(x_3-x_0)+pa3*(x_2-x_1);
			LATD = (unsigned char)((unsigned short)(y+0100000)>>010);
			y = (short)((((unsigned short)(y+0100000))>>06)-01000);
			x_4 = x_3;x_3 = x_2;x_2 = x_1;x_1 = x_0;
			x_0 = poten(10);x_0 -= 01000;

			/*goto previous*/
			if(SWITCH_1 == 0)
			{
				switch_release();
				return 0377;
			}//end if
		}//end while
	}//end else if		
	else if(type  == BANDPASS)			/*BP*/
	{

		pa1 = pa_7order[index][0];
		pa2 = pa_7order[index][1];
		pa3 = pa_7order[index][2];
		pa4 = pa_7order[index][3];

		while(1)
		{

			/*exeution*/
			y = pa1*(x_6+y)+pa2*(x_5+x_0)+pa3*(x_4+x_1)+pa4*(x_3+x_2);
			LATD = (unsigned char)((unsigned short)(y+0100000)>>010);
			y = (short)((((unsigned short)(y+0100000))>>06)-01000);
			x_6 = x_5;x_5 = x_4;x_4 = x_3;x_3 = x_2;x_2 = x_1;x_1 = x_0;
			x_0 = poten(10);x_0 -= 01000;

			/*goto previous*/
			if(SWITCH_1 == 0)
			{
				switch_release();
				return 0377;
			}//end if
		}//end while
	}//end else if
	else						/*MODULATION*/
	{
		/*determining frequency*/
		freq = (index/1023.0*850+10);
		delay_sum = (1000000.0/freq)-1100;
		for(count=0;count<32;++count)
			sin_320[count] = sin_32[count];

		/*exe*/
		if(index > 108)			/*fre 860Hz ~ 100Hz*/
		{
			delay_index = (int)((delay_sum/40));
			sprintf(msg2,"####%6dHz####",(int)freq);
			LCD_Line2(msg2);
			while(1)
			{
				count = 0;
				do
				{
					/*execution block-------------------------*/
	//				temp = poten(8);
	//				LATD = (unsigned char)((((((short)sin_32[count])-0200)*(temp-0200))+040000)>>7);
					LATD=(unsigned char)(((poten(8)-128)*(((short)sin_320[count])-128)+16384)>>8);
	//				Delay10TCYx(delay_index);
					
					/*calibration*/
	//				Delay10TCYx(1);
				
					/*goto previous*/
					if(SWITCH_1 == 0)
					{
						switch_release();
						return 0377;
					}//end if

				//	LATD = ~LATD;
				}while(++count<32);//end do while
			//	LATD = ~LATD;
			}//end while
		}//end if
		else					/*fre 100Hz ~ 10Hz*/
		{
			delay_index = (int)((delay_sum/3500));
			sprintf(msg2,"####%8d####",delay_index);
			LCD_Line2(msg2);
			while(1)
			{
				count = 0;
				do
				{
					/*execution block-------------------------*/
					temp = poten(8);
					LATD = (unsigned char)(((((sin_32[count])-0200)*(temp-0200))+040000)>>7);
					
					Delay1KTCYx(delay_index);

					/*calibration*/
					Delay10TCYx(50);
					Delay1TCY();
					Delay1TCY();
					Delay1TCY();
					Delay1TCY();
					Delay1TCY();
					
					/*goto previous*/
					if(SWITCH_1 == 0)
					{
						switch_release();
						return 0377;
					}//end if

				}while(++count<32);//end do while
			//	LATD = ~LATD;
			}//end while
		}//end else
	}//end else
}//end proc_exe
























