/*
 * timer.c
 *
 *  Created on: Sep 12, 2024
 *      Author: sakka
 */


#include "timer.h"
#include <avr/io.h>
#include "../../include/defines.h"

void TIMER1_Init(void) {
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS12);
    TIMSK |= (1 << OCIE1A);
    TCNT1 = 0;
    OCR1A = CMP_VALUE;
}

void pauseTimer(void)
{
	TCCR1B &= ~(1 << CS10) & ~(1 << CS11) & ~(1 << CS12);
}

void resetTimer(void)
{
	TCNT1 = 0;

	seconds_1 = 0;
	seconds_2 = 0;
	minutes_1 = 0;
	minutes_2 = 0;
	hours_1 = 0;
	hours_2 = 0;

	if(countMode == MODE_COUNT_DOWN)
	{
		PORTD &= ~(1 << PD0);
		pauseTimer();
	}
}

void resumeTimer(void)
{
	if(countMode == MODE_COUNT_UP)
	{
		TCCR1B |= (1 << CS10) | (1 << CS12);
	}
	else
	{
		if(seconds_1 || seconds_2 || minutes_1 || minutes_2 || hours_1 || hours_2)
		{
			TCCR1B |= (1 << CS10) | (1 << CS12);
		}
	}
}

