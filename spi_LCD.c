#include <p18F87J11.h>
#include <delays.h>

//*****************************************************************
// Functions that can be called by the main
//*****************************************************************
void LCD_Reset(void);      //Initializing LCD
void LCD_Line1(char[]);    //Write a char[] to Line 1
void LCD_Line2(char[]);    //Write a char[] to Line 2
//******END********************************************************


//****Other function prototypes************************************
void InitSPI(void);
void WriteGPIO(char, char);
void data_write(char);
void command_write(char);
void string_write(char[]);

//*****************************************************************
// Initialize MCP23S17 SPI
//*****************************************************************
void InitSPI(void)
{
// RC3 is connected to SCK (PIC18 Explorer Datasheet Page 31)
TRISCbits.TRISC3 = 0;
// RC5 is connected to SI (PIC18 Explorer Datasheet Page 31)
TRISCbits.TRISC5 = 0;
// SSPxCON1: MSSPx CONTROL REGISTER 1 (I2C MODE)
// SSPEN=1, 1 = Enables the serial port and configures the SDAx and SCLx pins as the serial port pins
// SSPM<3:0>=0010, 0010 = SPI Master mode, clock = FOSC/64
// CKP=0, 0 = Holds clock low (clock stretch), used to ensure data setup time
SSP1CON1 = 0x22; // 00100010
// CKE: SPI Clock Select bit
// 1 = Transmit occurs on transition from active to Idle clock state
// 0 = Transmit occurs on transition from Idle to active clock state
SSP1STATbits.CKE = 1;
// SSP1IF: MSSP1 Interrupt Flag bit
//1 = The transmission/reception is complete (must be cleared in software)
//0 = Waiting to transmit/receive
PIR1bits.SSPIF = 0;
}

//*****************************************************************
// Write to MCP23S17 GPIO
// SPI protocol: 4 steps to write to SPI
// (1) Set CS = 0 (Connects RA2: PIC18 Explorer Datasheet Page 31)
// (2) Send the register address via SSPBUF
// (3) Send the content via SSPBUF (whether it's data or command)
// (4) Set CS = 1
//*****************************************************************
void WriteGPIO(char addr, char byte)
{
LATAbits.LATA2 = 0;       //CS = 0 
SSPBUF = 0x40;
while(!PIR1bits.SSPIF);   //Wait for transmission completion
PIR1bits.SSPIF = 0;       //Reset flag
SSPBUF = addr;            //Sending destination address
while(!PIR1bits.SSPIF);
PIR1bits.SSPIF = 0;
SSPBUF = byte;            //Sending content
while(!PIR1bits.SSPIF);
PIR1bits.SSPIF = 0;
LATAbits.LATA2 = 1;       //CS = 1
}
//*****************************************************************
// Send data to the LCD
// GPA address is 12h, GPB address is 13h (MCP23S17 sheet Page 5)
// RS is connected to GPA7
// E is connected to GPA6 (from PIC18 Explorer datasheet Page 31)
//*****************************************************************
void data_write(char byte)
{
WriteGPIO(0x12, 0x80);    //RS = 1, E = 0
WriteGPIO(0x13, byte);    
WriteGPIO(0x12, 0xC0);    //RS = 1, E = 1 
WriteGPIO(0x12, 0);       //RS = 0, E = 0
}
//*****************************************************************
// Send a command to the LCD
//*****************************************************************
void command_write(char byte)
{
WriteGPIO(0x12, 0);      //RS = 0, E = 0
WriteGPIO(0x13, byte); 
WriteGPIO(0x12, 0x40);   //RS = 0, E = 1
WriteGPIO(0x12, 0);      //RS = 0, E = 0
}
//******************************************************************
// LCD Initialization function
//******************************************************************
void LCD_Reset(void)
{
TRISAbits.TRISA2 = 0;           //Will write to CS, hence RA2 output
LATAbits.LATA2 = 1;             // CS = 1; (optional)
Delay10TCYx(0);

//RF6 connects the RESET of expander (PIC18 Explorer Datasheet Page 31)
//Reset it for the first time
TRISFbits.TRISF6 = 0;
LATFbits.LATF6 = 0;
Delay10TCYx(0);
LATFbits.LATF6 = 1;            

InitSPI();
WriteGPIO(0x00, 0);
WriteGPIO(0x01, 0);

command_write( 0b00111100 );	//0011NFxx
command_write( 0b00001100 );	//Display Off
command_write( 0b00000001 );	//Display Clear
command_write( 0b00000110 );	//Entry mode
}

//*****************************************************************
// Write to line 1 of the display
//*****************************************************************
void LCD_Line1(char *sentence)
{
command_write(0x80);            //Move cursor to column 1 row 1
string_write(sentence);
}
//*****************************************************************
// Write to line 2 of the display
//*****************************************************************
void LCD_Line2(char *sentence)
{
command_write(0xC0);            //Move cursor to column 1 row 2
string_write(sentence);
}

//******************************************************************
// Write a string on LCD
//******************************************************************
void string_write(char *sentence) {
unsigned int i=0;
while (*(sentence+i) != '\0')    //End of the char array
{
data_write(*(sentence+i));
i++;
Delay10KTCYx(5);	
}
}
