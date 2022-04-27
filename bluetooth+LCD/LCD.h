/*
 * LCD.h
 *
 * Created: 4/5/2022 11:52:25 PM
 *  Author: Parikshit Sah
 */ 
#define F_CPU 16000000UL										// F_CPU must be defined BEFORE the #include <util/delay.h>

/*includes*/
#include <avr/io.h>												//include delay and general files
#include <util/delay.h>


#define INSTR_WR	0											//LCD instruction variable
#define DATA_WR		1											//LCD data variable

/* declare function prototypes */

void Init_PORTs (void);											//PORT initialization function header
void Init_LCD (void);											//LCD initialization function header
void LCD_write (unsigned char RS, unsigned char data);			//LCD write function prototype 
void Print_string(char *data_ptr);								//write to LCD function prototype