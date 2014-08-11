/*
 * =====================================================================================
 *
 *       Filename:  switch_poten.h
 *
 *    Description
 *
 *        Version:  1.0
 *        Created:  3/31/2014 12:48:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gregory LI (), vieux113@gmail.com
 *        Company:
 *
 * =====================================================================================
 */

/*	header file of init config of switched and potentiameter
 *
 */

#include <p18F87J11.h>


#define SWITCH_0 PORTBbits.RB0
#define SWITCH_1 PORTAbits.RA5
/*function prototypes*/
void switch_Init(void);
void switch_release(void);
void ADC_Init1(void);
void ADC_Init2(void);
/*FYI: input the number of bits returned 1~10*/
short poten(unsigned char);
void msg(char*, char*);
