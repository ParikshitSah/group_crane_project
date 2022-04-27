/*
 * main.h
 *
 * Created: 4/6/2022 10:04:30 PM
 *  Author: Parikshit Sah
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <avr/io.h>						
#include <util/delay.h>				//include delay library
#include  <avr/interrupt.h>			//include interrupt library
#include <string.h>					//include string library to clear array later

#include "LCD.h"				//include LCD header file
#include "USART.h"				//include USART header files

extern volatile uint8_t i ;					//global variable for index
extern  uint8_t access ;					//global variable for index
extern volatile uint16_t LCD_update;		//global variable to notify when to update the LCD
extern char rx_buffer[25] ;					//char to store string recieved from terminal





#endif /* MAIN_H_ */