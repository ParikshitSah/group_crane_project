/*
 * playback.c
 *
 * Created: 4/27/2022 6:22:15 PM
 *  Author: sahp
 */ 



void playback(void)
{
	motor_arr[7] = {};
	
	//load EEPROM array into motor_arr
	stepper_playback(motor_arr[0]);
	slow_servo(motor_arr[1]);
	OCR1A = motor_arr[2];
	slow_servo(motor_arr[3]);
	stepper_playback(motor_arr[4]);
	slow_servo(motor_arr[5]);
	OCR1A = motor_arr[6];

	return();

}

void stepper_playback(int16_t stepper_value)
{
	if (stepper_value < 0)	//if value is negative
	{
		for (uint16_t i =0;i < abs(stepper_value);i++)	//repeat as many times as recorded value
		{
			for(stepper_index = 0; stepper_index<8 ;stepper_index++)	//go CW
			{
				PORTC = half[stepper_index];
				while (tick < 10);
				tick = 0;
			}
		}
	}
	else
	{
		for (uint16_t i =0;i< abs(stepper_value);i++)
		{
			for(stepper_index = 7; stepper_index>0 ;stepper_index--)
			{
				PORTC = half[stepper_index];
				while (tick < 10);
				tick = 0;
			}
		}
	}
}

void slow_servo(servo_value)
{
	uint16_t pwm_buf = 0;	//buffer before assigning to OCR
	uint8_t steps = 50;	//servo_value will be divided into this many steps
	uint8_t pwm_inc;	//value increment for each step
	uint8_t inc_rem;	//value increment for last step
	uint8_t initial_value;	//initial OCR value
	uint8_t displacement;	//difference between initial and final OCR

	//calculate values for each variable
	initial_value = OCR1B;
	displacement = abs(initial_value - servo_value)
	pwm_inc = displacement / steps;
	inc_rem = displacement % steps;

	for(uint8_t i=0; i<steps; i++)	//repeat steps
	{
		pwm_buf += pwm_inc;
		OCR1B = pwm_buf;	// assign to arm
		while(tick<4);	//4ms delay per step
		tick = 0;
	}
	
	pwm_buf += inc_rem;	//increment last value
	OCR1B = pwm_buf;

	return();
}