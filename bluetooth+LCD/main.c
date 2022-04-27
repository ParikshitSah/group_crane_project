// /****************************************************/
// /*													*/
// /* Project name:	LCD_Test_8bit_parallel and USART*/
// /* 				*/
// /*													*/
// /*	The project uses USAR0 to display the input
// 	from the switches to the LEDs.The project also
// 	uses string from terminal and displays it on LCD
//
// /* on the 2x16 dot matrix LCD at a specific 		*/
// /* position using the ATMEL ATmega2560				*/
// /*													*/
// /* PORTL for LCD data:							 	*/
// /* 													*/
// /* L.0  LCD D0								        */
// /* L.1  LCD D1 								        */
// /* etc.									    		*/
// /* L.7  LCD D7								        */
// /*													*/
// /* PORTD for LCD control:							*/
// /*													*/
// /*	D.0	LCD RS							         	*/
// /*	D.1	LCD R/!W						        	*/
// /*	D.2	LCD E							            */
// /*													*/
// /* 	The code is written as a single .c module		*/
// /*													*/
// /*	Author:		Parikshit Sah			*/
// /*	Date:		4/8/2022							*/
// /*	Ver:		1.0									*/
// /*	Filename:	main.c		*/
// /*													*/
// /****************************************************/
//
// /* #defines */

// IO connections
//  PORTF (ADC) PF0 and PF1 to potentiometers
//  PB5 for OC1A
//  PB6 for OC1B
//  PK0 for Roller
//  PA0&1 for pushbuttons
//  PC0:4 for stepper motor

#define F_CPU 16000000UL // F_CPU must be defined BEFORE the #include <util/delay.h>

/*includes*/

#include "main.h"

// prototypes
void Validate(void);

#define Roller 0x01

uint16_t volatile rx_char;
volatile uint8_t i;
volatile uint16_t LCD_update;
char rx_buffer[25] = {};
char password[25] = {"test"};
char sucess[25] = {"Access Granted"};
char fail[25] = {"Try Again"};
uint8_t access;
uint8_t edit_mode;
uint32_t number;

uint16_t half[8] = {0x09, 0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08};
uint8_t stepper_index = 0; // variable

// global variables
volatile uint16_t ADC_value;
volatile uint16_t ADC_res0;
volatile uint16_t ADC_res1;
volatile uint8_t ADC_channel;
volatile uint16_t tick;

void init_ADC(void);
void Timer_Init(void);
void Init_IO(void);
void stepper_home(void);
void startup(void);
void manual_ctrl(void);
void record_mode(void);

int main(void)
{
	startup();

	while (1) /* start of super loop */
	{
		if (LCD_update == 1) /// only chars
		{
			switch (rx_buffer[0])
			{
				case '#':			//start button pressed
				String_out("Starting");
				break;
				
				case '&':			//home button pressed
				stepper_home();
				break;
				
				case '?':			//calibrate button pressed
				Validate();
				
				break;
			}

			memset(rx_buffer, 0, 25); // clear the array
			LCD_update = 0;
		}

		/*if (edit_mode == 1)
		{
			manual_ctrl();
			

			if (LCD_update == 1) /// only chars
			{
				switch (rx_buffer[0])
				{
				case '!':
					stepper_home();
					break;
				}

				memset(rx_buffer, 0, 25); // clear the array
				LCD_update = 0;
			}
		}*/
		
		
	} // end superloop

} /* end main */

void record_mode(void)
{
	
	
	Validate();
	if(edit_mode)
	{
		
	}
}

void manual_ctrl(void)
{
	if (ADC_channel == 0) // when channel one is selected, plunger
	{

		OCR1A = ((uint32_t)ADC_res0 * 25 / 16) + 2200; // assign value to servo 1
	}
	if (ADC_channel == 1) // when channel 2 is selected, arm
	{
		OCR1B = ((uint32_t)ADC_res1 * 625 / 512) + 2400; // assign value to servo 2
	}

	if ((PINA & 0x01) != 0) // pushbutton 1
	{
		while ((PINA & 0x01) != 0)
		{
			PORTC = half[stepper_index];

			while (tick < 10);
			tick = 0;

			++stepper_index;
			stepper_index = stepper_index % 8;
			number++;
		}
	}

	if ((PINA & 0x02) != 0) // pushbutton 2
	{
		while ((PINA & 0x02) != 0)
		{

			if (stepper_index == 0)
			{
				stepper_index = 7;
			}
			PORTC = half[stepper_index];

			while (tick < 10);
			tick = 0;
			--stepper_index;
			number--;
		}
		// rotate counter clockwise
	}
}

void startup(void)
{
	sei(); // enable interrupt
	Init_IO();
	Timer_Init();
	init_ADC();
	stepper_home(); // return to home position (stepper)

	Init_LCD();
	Init_USART();
}

void Validate(void)
{
	String_out("Enter configuration password:");
	while (edit_mode != 1)
	{
		if (LCD_update == 1)
		{
			// check password attempt
			for (int i = 0; i < 25; i++)
			{
				if (rx_buffer[i] != password[i])
				{
					access = 1;
				}
			}
			if (access == 0)
			{
				String_out(sucess);
				edit_mode = 1;
			}
			else
			{
				String_out(fail);
				access = 0;
			}
			memset(rx_buffer, 0, 25); // clear the array
			LCD_update = 0;
		}
	}
}

void init_ADC(void)
{

	DDRF = 0x00;  // set PORTF as input
	PORTF = 0xFE; // turn off pull-up resistor for LSB

	ADMUX = (1 << REFS0);
	// ref voltage: AVCC, default channel: 0, left align
	ADCSRA = (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) | (1 << ADIE); // prescaler: 128
	ADCSRA |= (1 << ADEN) | (1 << ADSC);							   // enable conversion
}

ISR(ADC_vect) // interrupt for ADC
{
	ADC_value = ADCL;				// sets ADC_value to ADCL
	ADC_value = ADCL | (ADCH << 8); // adds last two bits

	if (ADC_channel == 0)
	{
		ADC_res0 = ADC_value;
	}
	else if (ADC_channel == 1)
	{
		ADC_res1 = ADC_value;
	}

	ADC_channel++;
	ADC_channel = ADC_channel % 2; // alternates ADC_channel

	ADMUX = (ADMUX & 0xE0) | ADC_channel; // set ADC port
	ADCSRA |= (1 << ADSC);
}

void Timer_Init(void)
{
	// FOR TIMER1
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11); // NON Inverted PWM
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11);	// PRESCALER=8 MODE 14(FAST PWM)
	ICR1 = 20000;											// freq=50Hz
	DDRB |= (1 << PB5) | (1 << PB6);						// PWM Pins as Output

	// TIMER0 for delay
	TCNT0 = 6; // 240
	TCCR0A = 0x00;
	TCCR0B = (1 << CS00) | (1 << CS01);
	TIMSK0 = (1 << TOIE0); // enable interrupts

}
ISR(TIMER0_OVF_vect) // timer overflow for interrupt
{
	TCNT0 = 0; // 240
	tick++;
}

void Init_IO(void)
{
	DDRK = 0x00;	// Set PORTK to input switch
	PORTK = Roller; // Set PORTK to roller switch

	DDRA = 0x00;
	PORTA = 0x03; // set PORTA 0 & 1 pushbuttons

	DDRC = 0x0F; // stepper motor output								change this back to 0x0F
	PORTC = 0x00;
}

void stepper_home(void)
{
	OCR1A = 3800;
	OCR1B = 2400;

	while ((PINK & Roller) != 0)
	{
		PORTC = half[stepper_index];
		while (tick < 10);
		tick = 0;
		++stepper_index;
		stepper_index = stepper_index % 8;
		
	}
	String_out("Home position reached");
}
