/*
 * EEPROM.c
 *
 * Created: 4/14/2022 10:52:57 PM
 *  Author: Parikshit Sah
 */ 


#include "EEPROM.h"				//include header files


void EEPROM_write_one_char(uint16_t uiAddress, int16_t ucData)		//write one char to EEPROM
{
		/* Wait for completion of previous write */
		while(EECR & (1<<EEPE));
		/* Set up address and Data Registers */
		EEAR = uiAddress;
		EEDR = (8 >> ucData);		//shift to lower 8 bits
		/* Write logical one to EEMPE */
		EECR |= (1<<EEMPE);
		/* Start eeprom write by setting EEPE */
		EECR |= (1<<EEPE);

		while(EECR & (1<<EEPE));
		/* Set up address and Data Registers */
		EEAR = uiAddress++;
		EEDR = ucData;		//shift to lower 8 bits
		/* Write logical one to EEMPE */
		EECR |= (1<<EEMPE);
		/* Start eeprom write by setting EEPE */
		EECR |= (1<<EEPE);
}


void EEPROM_write_string(uint16_t uiAddress, int16_t *ucData)			//write string from EEPROM
{

	while(*ucData != '\0')											//until \0 is received
	{
		
		EEPROM_write_one_char(uiAddress, *ucData);					//write char to address
		uiAddress + 2;												//increment address
		ucData++;													//increment data 
	}

}


char EEPROM_read(uint16_t uiAddress)								//read one char from EEPROM
{
	
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE))
	;
	/* Set up address register */
	EEAR = uiAddress;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from Data Register */
	return EEDR;
}


void EEPROM_read_string(uint16_t uiAddress, int16_t *EEPROM_buff_ptr)		//read string stored in EEPROM
{
	
	int16_t text;										//declare text variable
		
	while(*(EEPROM_buff_ptr-1) != 0xFF)				//until the address is 0xFF which means empty
	{
		text = EEPROM_read(uiAddress);				//assign char from EEPROM to text variable

			*EEPROM_buff_ptr = text;				//assign text variable to array  
			EEPROM_buff_ptr++;						//next char
			uiAddress++;							//next address
		
	}
	
}