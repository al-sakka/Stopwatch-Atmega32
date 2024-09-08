/*
 * main.c
 *
 *  Created on: Aug 6, 2024
 *      Author: sakka
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "seven_seg.h"

#define F_CPU 16000000UL

unsigned char tick = 0;

unsigned char seconds_1 = 0;
unsigned char seconds_2 = 0;

void TIMER1_Init(void)
{
	TCCR1A = (1 << COM1A0); 
	TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS12);

	TIMSK |= (1 << OCIE1A); // Enable OCR1

	TCNT1 = 0;


	OCR1A = 250;

	sei();
}

ISR(TIMER1_COMPA_vect)
{
	tick++;

	if(tick >= 62)
	{
		seconds_1++;
		tick = 0;
	}
}

void showTime(unsigned char seconds_1, unsigned seconds_2)
{
	PORTC |= (1 << 6);
	PORTC &= ~(1 << 7);
	seven_segment(seconds_1);

	_delay_ms(10);

	PORTC |= (1 << 7);
	PORTC &= ~(1 << 6);
	seven_segment(seconds_2);

	_delay_ms(10);
}

int main(void)
{
	TIMER1_Init();
	segment_init();

	while(1)
	{
		if(seconds_1 > 9)
		{
			seconds_1 = 0;
			seconds_2++;
		}
		else if(seconds_2 > 5)
		{
			seconds_1 = 0;
			seconds_2 = 0;
		}
		
		showTime(seconds_1, seconds_2);

	} // super loop
}