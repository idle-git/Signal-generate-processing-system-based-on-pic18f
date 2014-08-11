# MPLAB IDE generated this makefile for use with GNU make.
# Project: LCD.mcp
# Date: Thu Mar 21 16:55:37 2013

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

LCD.cof : main.o spi_LCD.o
	$(LD) /p18F87J11 /l"C:\Program Files\Microchip\mplabc18\v3.40\lib" "main.o" "spi_LCD.o" /u_CRUNTIME /z__MPLAB_BUILD=1 /o"LCD.cof" /M"LCD.map" /W

main.o : main.c ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/delays.h ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/stdio.h main.c ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/p18F87J11.h ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/p18cxxx.h ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/p18f87j11.h switch00.h ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/stdarg.h ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/stddef.h ADC.h
	$(CC) -p=18F87J11 "main.c" -fo="main.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

spi_LCD.o : spi_LCD.c ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/delays.h spi_LCD.c ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/p18F87J11.h ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/p18cxxx.h ../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.40/h/p18f87j11.h
	$(CC) -p=18F87J11 "spi_LCD.c" -fo="spi_LCD.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "main.o" "spi_LCD.o" "LCD.cof" "LCD.hex"

