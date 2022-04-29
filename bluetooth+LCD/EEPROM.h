/*
 * EEPROM.h
 *
 * Created: 4/14/2022 11:01:17 PM
 *  Author: Parikshit Sah 
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include <avr/io.h>
#include <string.h>

void EEPROM_write_one_char(uint16_t uiAddress, int16_t ucData);
void EEPROM_write_string(uint16_t uiAddress, int16_t *ucData);
char EEPROM_read(uint16_t uiAddress);
void EEPROM_read_string(uint16_t uiAddress, int16_t *EEPROM_buff_ptr);







#endif /* EEPROM_H_ */