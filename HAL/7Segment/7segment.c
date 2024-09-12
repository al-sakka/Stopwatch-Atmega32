/*
 * 7segment.c
 *
 *  Created on: Sep 12, 2024
 *      Author: sakka
 */

#include "7segment.h"
#include <avr/io.h>
#include <util/delay.h>

#define DELAY_VALUE 5

extern signed char seconds_1, seconds_2;
extern signed char minutes_1, minutes_2;
extern signed char hours_1, hours_2;

void show_number_on_segment(void)
{
	PORTA &= ~(0x3F);
	PORTC &= ~(0x0F);
	PORTA |= (1 << 5);
	PORTC |= seconds_1;
	_delay_ms(DELAY_VALUE);

	PORTA &= ~(0x3F);
	PORTC &= ~(0x0F);
	PORTA |= (1 << 4);
	PORTC |= seconds_2;
	_delay_ms(DELAY_VALUE);

	PORTA &= ~(0x3F);
	PORTC &= ~(0x0F);
	PORTA |= (1 << 3);
	PORTC |= minutes_1;
	_delay_ms(DELAY_VALUE);

	PORTA &= ~(0x3F);
	PORTC &= ~(0x0F);
	PORTA |= (1 << 2);
	PORTC |= minutes_2;
	_delay_ms(DELAY_VALUE);

	PORTA &= ~(0x3F);
	PORTC &= ~(0x0F);
	PORTA |= (1 << 1);
	PORTC |= hours_1;
	_delay_ms(DELAY_VALUE);

	PORTA &= ~(0x3F);
	PORTC &= ~(0x0F);
	PORTA |= (1 << 0);
	PORTC |= hours_2;
	_delay_ms(DELAY_VALUE);

}
