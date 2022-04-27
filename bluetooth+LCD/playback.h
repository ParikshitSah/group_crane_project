/*
 * playback.h
 *
 * Created: 4/27/2022 6:23:11 PM
 *  Author: sahp
 */ 


#ifndef PLAYBACK_H_
#define PLAYBACK_H_

#include <avr/io.h>

void playback(void);
void stepper_playback(int16_t stepper_value);
void slow_servo(servo_value);


#endif /* PLAYBACK_H_ */