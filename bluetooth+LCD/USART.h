/*
 * USART.h
 *
 * Created: 4/6/2022 12:44:13 AM
 *  Author: Parikshit Sah
 */ 

#define F_CPU 16000000UL			//define microcontroller timer speed
#include <avr/io.h>					
#include  <avr/interrupt.h>			//include interrupt library
#include "main.h"					//include main header files

void Init_USART(void);				//init USART func prototype
void UART_out(uint8_t ch);			//send to USART func prototype
void String_out(char *string);


 uint16_t extern volatile rx_char;

