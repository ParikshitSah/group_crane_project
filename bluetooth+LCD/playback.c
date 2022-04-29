/*
 * playback.c
 *
 * Created: 4/27/2022 6:22:15 PM
 *  Author: sahp
 */ 

#include "playback.h"



void playback(void)
{
	int16_t motor_arr[7] = {120, 3600, 2200, 2400, -120, 3600, 3800};
	//toEEPROM[7] = {200, 3400, 2200, 2500, -200, 3500, 3800};
	//load EEPROM array into motor_arr
	//EEPROM_read_string(Address_EEPROM, toEEPROM);
	//String_out("reading from the EEPROM");
	//String_out(motor_arr);
	stepper_playback(motor_arr[0]);
	//slow_servo(motor_arr[1]);
	while (tick < 500);
	tick = 0;
	slow_servo(motor_arr[1]);
	while (tick < 500);
	tick = 0;
	OCR1A = motor_arr[2];
	while (tick < 500);
	tick = 0;
	slow_servo(motor_arr[3]);
	//OCR1B = motor_arr[3];
	stepper_playback(motor_arr[4]);
	//slow_servo(motor_arr[5]);
	slow_servo(motor_arr[5]);
	OCR1A = motor_arr[6];

	return;

}

void stepper_playback(int16_t stepper_value)
{
	uint8_t stepper_index;
	
	if (stepper_value < 0)	//if value is negative
	{
		for (uint16_t i =0;i < abs(stepper_value);i++)	//repeat as many times as recorded value
		{
			for(stepper_index = 0; stepper_index<8 ;stepper_index++)	//go CWW
			{
				PORTC = half[stepper_index];
				while (tick < 5);
				tick = 0;
			}
		}
	}
	else
	{
		for (uint16_t i =0;i< abs(stepper_value);i++)
		{
			for(stepper_index = 7; stepper_index>0 ;stepper_index--) //go cw
			{
				PORTC = half[stepper_index];
				while (tick < 5);
				tick = 0;
			}
		}
	}
}

void slow_servo(uint16_t servo_value)
{
	uint16_t pwm_buf = 0;	//buffer before assigning to OCR
	uint8_t steps = 30;	//servo_value will be divided into this many steps
	uint8_t pwm_inc;	//value increment for each step
	uint8_t inc_rem;	//value increment for last step
	//uint8_t initial_value;	//initial OCR value
	//uint8_t displacement;	//difference between initial and final OCR

	//calculate values for each variable
	pwm_inc = servo_value / steps;
	inc_rem = servo_value % steps;
	pwm_buf = OCR1B;

	for(uint8_t i=0; i<steps; i++)	//repeat steps
	{
		pwm_buf += pwm_inc;
		OCR1B = pwm_buf;	// assign to arm
		while(tick<100);	//4ms delay per step
		tick = 0;
	}
	
	pwm_buf += inc_rem;	//increment last value
	OCR1B = pwm_buf;

	return;
}