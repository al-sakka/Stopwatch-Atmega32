/*
 * interrupts.c
 *
 *  Created on: Sep 12, 2024
 *      Author: sakka
 */

#include "interrupts.h"
#include <avr/io.h>

void INT0_Init(void)
{
	MCUCR |= (1 << ISC01);
	GICR |= (1 << INT0);
}

void INT1_Init(void)
{
	MCUCR |= (1 << ISC10) | (1 << ISC11);
	GICR |= (1 << INT1);
}

void INT2_Init(void)
{
	MCUCSR &= ~(1 << ISC2);
	GICR |= (1 << INT2);
}
