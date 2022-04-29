/*
 * main.h
 *
 * Created: 4/6/2022 10:04:30 PM
 *  Author: Parikshit Sah
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define Address_EEPROM 0x0000							//define EEPROM address
#define Address_Step1 0x0003
#define Address_Step2 0x0005
#define Address_Step3 0x0007
#define Address_Step4 0x0009
#define Address_Step5 0x00B0
#define Address_Step6 0x00D0
#define Address_Step7 0x00F0




#include <avr/io.h>						
#include <util/delay.h>				//include delay library
#include  <avr/interrupt.h>			//include interrupt library
#include <string.h>					//include string library to clear array later
#include <stdio.h>
#include <stdlib.h>
#include "LCD.h"				//include LCD header file
#include "USART.h"				//include USART header files
#include "EEPROM.h"										//import EEPROM file


// global variables
extern uint16_t half[8];			//make this global

extern volatile uint8_t i ;					//global variable for index
extern  uint8_t access ;					//global variable for index
extern volatile uint16_t LCD_update;		//global variable to notify when to update the LCD
extern char rx_buffer[25] ;					//char to store string recieved from terminal


extern volatile uint16_t ADC_value;
extern volatile uint16_t ADC_res0;
extern volatile uint16_t ADC_res1;
extern volatile uint8_t ADC_channel;
extern volatile uint16_t tick;

char password[25];
char sucess[25];
char fail[25];
uint8_t access;
uint8_t edit_mode;
int16_t stepper_counts;
int16_t toEEPROM[7] ;
uint16_t currentAddress;
#endif /* MAIN_H_ */