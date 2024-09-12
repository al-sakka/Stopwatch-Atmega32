/*
 * buttons.c
 *
 *  Created on: Sep 12, 2024
 *      Author: sakka
 */

#include "buttons.h"
#include <avr/io.h>
#include <util/delay.h>
#include "../../include/defines.h"

#define DEBOUNCE_VALUE 20

extern unsigned char isModeBtnPressed;
extern unsigned char isControlHours1Pressed;
extern unsigned char isControlHours2Pressed;

void countDwnBtns(void)
{
	//// decrement hours button
	if(!(PINB & (1 << PB0)))
	{
		_delay_ms(DEBOUNCE_VALUE);
		if(!(PINB & (1 << PB0)) && !isControlHours1Pressed)
		{
			isControlHours1Pressed = 1;
			decTime(&hours_1, &hours_2, 9, 5);
		}
	}
	else
	{
		isControlHours1Pressed = 0;
	}


	//// increment hours button
	if(!(PINB & (1 << PB1)))
	{
		_delay_ms(DEBOUNCE_VALUE);
		if(!(PINB & (1 << PB1)) && !isControlHours2Pressed)
		{
			isControlHours2Pressed = 1;
			incTime(&hours_1, &hours_2, 9, 5);
		}
	}
	else
	{
		isControlHours2Pressed = 0;
	}

	//// decrement minutes button
	if(!(PINB & (1 << PB3)))
	{
		_delay_ms(DEBOUNCE_VALUE);
		if(!(PINB & (1 << PB3)) && !isControlMins1Pressed)
		{
			isControlMins1Pressed = 1;
			decTime(&minutes_1, &minutes_2, 9, 5);
		}
	}
	else
	{
		isControlMins1Pressed = 0;
	}

	//// increment minutes button
	if(!(PINB & (1 << PB4)))
	{
		_delay_ms(DEBOUNCE_VALUE);
		if(!(PINB & (1 << PB4)) && !isControlMins2Pressed)
		{
			isControlMins2Pressed = 1;
			incTime(&minutes_1, &minutes_2, 9, 5);
		}
	}
	else
	{
		isControlMins2Pressed = 0;
	}

	//// decrement seconds button
	if(!(PINB & (1 << PB5)))
	{
		_delay_ms(DEBOUNCE_VALUE);
		if(!(PINB & (1 << PB5)) && !isControlSecs1Pressed)
		{
			isControlSecs1Pressed = 1;
			decTime(&seconds_1, &seconds_2, 9, 5);
		}
	}
	else
	{
		isControlSecs1Pressed = 0;
	}

	//// increment seconds button
	if(!(PINB & (1 << PB6)))
	{
		_delay_ms(DEBOUNCE_VALUE);
		if(!(PINB & (1 << PB6)) && !isControlSecs2Pressed)
		{
			isControlSecs2Pressed = 1;
			incTime(&seconds_1, &seconds_2, 9, 5);
		}
	}
	else
	{
		isControlSecs2Pressed = 0;
	}
}

void checkMode(void)
{
	if(!(PINB & (1 << PB7)))
	{
		_delay_ms(DEBOUNCE_VALUE);
		if(!(PINB & (1 << PB7)) && !isModeBtnPressed)
		{
			isModeBtnPressed = 1;
			countMode = (countMode == MODE_COUNT_UP) ? MODE_COUNT_DOWN : MODE_COUNT_UP;

			PORTD &= ~(1 << PD0);
		}
	}
	else
	{
		isModeBtnPressed = 0;
	}

	if(countMode == MODE_COUNT_UP)
	{
		PORTD &= ~(1 << PD5);
		PORTD |= (1 << PD4);
	}
	else
	{
		PORTD &= ~(1 << PD4);
		PORTD |= (1 << PD5);
		countDwnBtns();
	}
}
