/*
 * USART.c
 *
 * Created: 4/6/2022 12:44:03 AM
 *  Author: Parikshit Sah
 */ 

#include "USART.h"								//include header files
#include <stddef.h>





void Init_USART(void)
{
	uint16_t myubr;									//init variable
	UCSR0A = 0x00;									//clear register
	UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);		//enable transmit, recieve and recieve interrupt
	UCSR0C  = (1<<UCSZ00)|(1<<UCSZ01);				//no parity, async normal, 8 bit 
	myubr = (F_CPU/(16UL*(uint16_t)9600))-1;		//calculate UBR value
	UBRR0L= myubr;									//assign UBR value
	UBRR0H = 0x00;									//clear this register
	
}

void UART_out(uint8_t ch)						//Send data from USART
{
	while((UCSR0A & (1<<UDRE0))==0);			//Wait for data
	UDR0 = ch;									//Assign value to variable
}

void String_out(char *string)
{
	
	while(*string != '\0')
	{
		UART_out(*string);
		string++;
	}
	
	
}
void Num_out(int16_t *string)
{
	for(int i =0; i<2;i++)
	{
		
		UART_out(*string);
		string++;
	}
	
	
}

ISR(USART0_RX_vect)
{

		
	rx_char = UDR0;										//read UDR0
			
			
			
			if (rx_char == 0x0A)						//when 0A hex received
			{
				return;									//end and return func
			}	
			
				if(rx_char != 0x0D)						//carriage return?
				{
					rx_buffer[i] = rx_char;				//put recived char into buffer array
					i++	;								//increment index
				}
				else									//if carriage return
				{
					
					UART_out(0x0D);						//carriage return end of sentence
					
					i=0;								// reset index
					LCD_update = 1;						//update LCD
					
				}
				
				
				
			
}