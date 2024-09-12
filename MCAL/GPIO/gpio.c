/*
 * gpio.c
 *
 *  Created on: Sep 12, 2024
 *      Author: sakka
 */

#include "gpio.h"
#include <avr/io.h>

void Pins_Init(void)
{
	DDRC |= 0x0F;
	DDRA |= 0x3F;
	DDRD &= ~(1 << PD2) & ~(1 << PD3);
	DDRB = 0x00;
	DDRD |= (1 << PD4) | (1 << PD5) | (1 << PD0);

	PORTC &= ~(0x0F);
	PORTA &= ~(0x3F);
	PORTD |= (1 << PD2);
	PORTB = 0xFF;

	PORTD |= (1 << PD4);
	PORTD &= ~(1 << PD5);
	PORTD &= ~(1 << PD0);

}
