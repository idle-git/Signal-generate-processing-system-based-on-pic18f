#include <p18F87J11.h>
#include "Delays.h"
#include "switch_poten.h"
#include "stdio.h"
#include "math.h"
#include "generator.h"
#include "LCD.h"


#pragma idata
unsigned char bo;// global var
#pragma code

enum {GENERATE, PROCESS, SINUSOIDAL, TRIANGLE, SAWTOOTH, SQUARE,
		LOWPASS, HIGHPASS, BANDPASS, MODULATION, ALLPASS};// menu of the whole part
unsigned char wavetype(void)
{
char msg1[16] =  "   START NOW?  ";// LCD line 1 message
char msg2[16] =  "  PRESS ANYKEY ";// LCD line 2 message
unsigned char choice = 0;// represents ADC convert value
LCD_Reset();// initiliaze LCD
sprintf(msg1,"----WAVE TYPE?---");// input to LCD line 1
LCD_Line1(msg1);
do{
	choice = (unsigned char)poten(2)+2;	// let adc convert value to choice	
	switch(choice)
	{
		case SINUSOIDAL:	
								sprintf(msg2,"---SINUSOIDAL---");
		                    	LCD_Line2(msg2);

								bo=1;// 1 represent sine wave
	    break;
		case TRIANGLE:
								sprintf(msg2,"----TRIANGLE----");
								LCD_Line2(msg2);

								bo=2;// 2 represents triangle wave
		break;
		case SAWTOOTH:
								sprintf(msg2,"----SAWTOOTH----");
								LCD_Line2(msg2);

								bo=3;// 3 represents sawtooth wave
		break;
		case SQUARE:
								sprintf(msg2,"-----SQUARE-----");
								LCD_Line2(msg2);

								bo=4;// 4 represents square wave
		break;
        default: 
		break;
	}
								

if (SWITCH_1==0)// if RA5 pressed exit wavetype function goto divice type menu 
 {
 while(SWITCH_1 == 0);// wait for RA5 release
	return 1; 
 }
	
}while(SWITCH_0 == 1);//end do  while RB0 pressed.
 switch_release();// wait for RB0 release
}

unsigned char frequencyrange(void)
{
unsigned char m;// represent adc convert value
unsigned int f;// represent frequency 
char msg1[16] =  "   START NOW?  ";//LCD LINE 1 message
char msg2[16] =  "  PRESS ANYKEY ";// LCD line 2 message
LCD_Reset();// initiliaze LCD

sprintf(msg1,"  Please choose  ");// chose frequency message
LCD_Line1(msg1);
sprintf(msg2,"Frequency");
LCD_Line2(msg2);
Delay10KTCYx(250);// delay 0.25s
Delay10KTCYx(250);//delay 0.25s
Delay10KTCYx(250);// delay0.25s
Delay10KTCYx(250);//delay0.25s



LCD_Reset();// initialize lCD
		switch(bo)
	{
		case 1:	
								do
								{
								sprintf(msg1,"Range:11~2277 Hz");
		                    	LCD_Line1(msg1);
								m=poten(8);// ADC convert value
								if (m==0) m=1;// let the least ADC value is 1 
								f=(unsigned int)1/(1/12600+m*0.00035+0.000089);;// caculate sine wave frequency
								if ((m<=60)&&(m>=30))f=f-1;// slightly adjust frequency
								if ((m<=20)&&(m>=10))f=f-4;// slightly adjust frequency
								if ((m>5)&&(m<10) )f=f-5;// slightly adjust frequency
								if(m==5) f=f-6;// slightly adjust frequency
								if(m==4) f=f-7;// slightly adjust frequency
								if(m==3) f=f-7;// slightly adjust frequency
								if (m==2) f=f+13;// slightly adjust frequency 
								sprintf(msg2,"%10d Hz",f);
								LCD_Line2(msg2);// show frequency
if (SWITCH_1==0)
{
switch_release();//wait for RA5 release
	return 2;// if RA5 pressed goto wavetype function
 }
								}
								while(SWITCH_0 == 1);
							    switch_release();//wait for RB0 release
								sinewave(m);//output sine wave
							    switch_release();//wait for RA5 release
								return 3;// if RA5 pressed goto frequency range function
	    break;
		case 2:
								do
								{
									sprintf(msg1,"Range:6~581 Hz");
		                    	LCD_Line1(msg1);
								m=poten(8);// ADC convert value
								if (m==0) m=1;// let the least ADC value is 1 
							 	f=(unsigned int) 1/ (1/847 + m*0.00057+0.001230); //caculate and slightly adjust triangle wave frequency
								if (m==1) f=f+26;//caculate and slightly adjust triangle wave frequency
								if (m==2) f=f+20;//caculate and slightly adjust triangle wave frequency
								if (m==3) f=f+12;//caculate and slightly adjust triangle wave frequency
								if (m==4) f=f+10;//caculate and slightly adjust triangle wave frequency
								if (m==5) f=f+7;//caculate and slightly adjust triangle wave frequency
								if ((m>=6)&&(m<=8)) f=f+5;//caculate and slightly adjust triangle wave frequency
								if (m==9) f=f+4;//caculate and slightly adjust triangle wave frequency
								if ((m>=10)&& (m<=13)) f=f+3;//caculate and slightly adjust triangle wave frequency
								if ((m>=13)&&(m<=17)) f=f+2;//caculate and slightly adjust triangle wave frequency
								if ((m>=18)&&(m<=50)) f=f+1;//caculate and slightly adjust triangle wave frequency
							sprintf(msg2,"%10d Hz",f);
								LCD_Line2(msg2);// show frequency
if (SWITCH_1==0)
{
	switch_release();//wait for RA5 release
	return 2;// if RA5 pressed goto wavetype function
 }
								}
								while(SWITCH_0 == 1);
								switch_release();//wait for RB0 release
								triwave(m);// output triangle wave
								switch_release();//wait for RA5 release
								return 3;// if RA5 pressed goto frequency range function
		break;
		case 3:
								do
								{
								sprintf(msg1,"Range:5~676 Hz");
		                    	LCD_Line1(msg1);
								m=poten(8);// ADC convert value
								if (m<=1) m=2;// let the least ADC value is 2
							 	f=(unsigned int) 1/ (1/15600 + m*0.000709+0.00007);//caculate  sawtooth wave frequency
								if ((m==2)||(m==3)) f=f+4;//caculate and slightly adjust sawtooth wave frequency
								if (m==4) f=f+1;//caculate and slightly adjust sawtooth wave frequency
							sprintf(msg2,"%10d Hz",f);
								LCD_Line2(msg2);// show frequency
							
if (SWITCH_1==0)
{
	switch_release();//wait for RA5 release
	return 2;// if RA5 pressed goto wavetype function
 }								
								}
								while(SWITCH_0 == 1);
								switch_release();//wait for RB0 release
								sawtooth(m);//output sawtooth wave
								switch_release();//wait for RA5 release
								return 3;// if RA5 pressed goto frequency range function
		break;
		case 4:
								do
								{
								sprintf(msg1,"Range:102~7690Hz");
		                    	LCD_Line1(msg1);
								m=poten(8);// adc convert value
								if (m==0) m=1;// let the least ADC value is 1
							 if ((m>=140)&&(m<=255)) f=(unsigned int) 1/ (1/11400 + m*0.0000376+0.000075)-0.5;//caculate and slightly adjust square wave frequency
							 if ((m>=101)&&(m<=139)) f=(unsigned int) 1/ (1/11400 + m*0.0000376+0.000075)-1.5;//caculate and slightly adjust square wave frequency
							if ((m>=70)&&(m<=100)) f=(unsigned int) 1/ (1/11400 + m*0.0000376+0.000075)-2.5;//caculate and slightly adjust square wave frequency
							if ((m>=64)&&(m<=69)) f=(unsigned int) 1/ (1/11400 + m*0.0000376+0.000075)-3.5;//caculate and slightly adjust square wave frequency
							if ((m>=55)&&(m<=63)) f=(unsigned int) 1/ (1/11400 + m*0.0000376+0.000075)-4.5;//caculate and slightly adjust square wave frequency
							if ((m>=46)&&(m<=54)) f=(unsigned int) 1/ (1/11400 + m*0.0000376+0.000075)-5.5;//caculate and slightly adjust square wave frequency
							if ((m>=45)&&(m<=43)) f=(unsigned int) 1/ (1/11400 + m*0.0000376+0.000075)-6.5;//caculate and slightly adjust square wave frequency
							if ((m>=40)&&(m<=42)) f=(unsigned int) 1/ (1/11400 + m*0.0000376+0.000075)-7.5;//caculate and slightly adjust square wave frequency
							if ((m>=30)&&(m<=40)) f=(unsigned int) 1/ (1/11400 + m*0.0000376+0.000075)-9.5;//caculate and slightly adjust square wave frequency
							if ((m>=20)&&(m<=29)) f=(unsigned int) 1/ (1/11400 + m*0.0000376+0.000075)-11.5;//caculate and slightly adjust square wave frequency
							if ((m>=10)&&(m<=19)) f=(unsigned int) 1/ (1/11400 + m*0.0000376+0.000075)-2.5*m;//caculate and slightly adjust square wave frequency
							if (m==10) f=2131;//caculate and slightly adjust square wave frequency
							if (m==9) f=2313;//caculate and slightly adjust square wave frequency
							if (m==8) f=2540;//caculate and slightly adjust square wave frequency
							if (m==7) f=2810;//caculate and slightly adjust square wave frequency
							if (m==6) f=3140;//caculate and slightly adjust square wave frequency
							if (m==5) f=3570;//caculate and slightly adjust square wave frequency
							if (m==4) f=4130;//caculate and slightly adjust square wave frequency
							if (m==3) f=4900;//caculate and slightly adjust square wave frequency
							if (m==2) f=6020;//caculate and slightly adjust square wave frequency
							if (m==1) f=7690;	//caculate and slightly adjust square wave frequency
							sprintf(msg2,"%10d Hz",f);
								LCD_Line2(msg2);// show frequency
if (SWITCH_1==0)
{
	switch_release();//wait for RA5 release
	return 2;// if RA5 pressed goto wavetype function
 }									
								}
								while(SWITCH_0 == 1);
								switch_release();//wait for RB0 release
								squarewave(m);//output square wave
								switch_release();//wait for RA5 release
								return 3;// if RA5 pressed goto frequency range function
		break;
        default: 
		break;
	}

}
	




	


void squarewave(unsigned char m)
{ unsigned short i,n=16;//16 samples

while (SWITCH_1==1) //if RA5 not pressed
{for(i=0;i<=n;i++)
{
PORTD=0b00000000;// output low level
Delay10TCYx(m);
}
for(i=0;i<=n;i++)
{
PORTD=0b11111111;//output high level
Delay10TCYx(m);
}

}
}
void triwave(unsigned char m)
{
unsigned int flag;
PORTD=0x00; 

while (SWITCH_1==1) //if RA5 not pressed
{


if (flag==1)
{
PORTD++;//output tri wave
Delay10TCYx(m);//  f=(double) 1/ (1/847 + n*0.00057+0.001230);
if (PORTD==0xFF){flag=0;}
}//end if
else
{
PORTD--;
Delay10TCYx(m);//  f=(double) 1/ (1/847 + n*0.00057+0.001230);
if (PORTD==0x00){flag=1;}
}//end else

}//end while
}
void sawtooth (unsigned char m)
{
PORTD=0x00;
                                                                                                                                                                                                                                                                                                                                                                                                                            
while (SWITCH_1==1) //if RA5 not pressed
{

PORTD=PORTD+4;//output sawtooth
Delay100TCYx(m);//f=(double) 1/ (1/15600 + n*0.000709+0.00007);

}

}

void sinewave (unsigned char m)
{ unsigned char i,n;
 unsigned char s[31];
float PI=3.141593;
n=31;//32 samples
for(i=0;i<=n;i++)
{s[i]=(unsigned char)(sin(2*PI/(n+1)*i)*127+128);
}
while (SWITCH_1==1)//if RA5 not pressed 
{
for(i=0;i<=n;i++)
{
PORTD=s[i];
//PORTD=(unsigned char)(sin(2*PI/(n+1)*i)*127+128);//output sine wave
Delay100TCYx(m);//f=(double) 1/ (1/44.6 + n*0.00035);
}

}
}







