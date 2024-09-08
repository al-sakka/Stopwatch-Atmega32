/*
 * seven_seg.c
 *
 *  Created on: Aug 16, 2024
 *      Author: sakka
 */

/*
 *
 * PA1 --> A
 * PA2 --> B
 * PA3 --> C
 * PA4 --> D
 * PA5 --> E
 * PA6 --> F
 * PA7 --> G
 * PB0 --> Dot
 *
 */

#include <avr/io.h>
#include "seven_seg.h"

void seven_segment(int num)
{
	switch(num)
	{
	case 0:
		PORTA |= (1 << A);
		PORTA |= (1 << B);
		PORTA |= (1 << C);
		PORTA |= (1 << D);
		PORTA |= (1 << E);
		PORTA |= (1 << F);
		PORTA &= ~(1 << G);
		PORTB &= ~(1 << DOT);
		break;
	case 1:
		PORTA &= ~(1 << A);
		PORTA |= (1 << B);
		PORTA |= (1 << C);
		PORTA &= ~(1 << D);
		PORTA &= ~(1 << E);
		PORTA &= ~(1 << F);
		PORTA &= ~(1 << G);
		PORTB &= ~(1 << DOT);
		break;
	case 2:
		PORTA |= (1 << A);
		PORTA |= (1 << B);
		PORTA &= ~(1 << C);
		PORTA |= (1 << D);
		PORTA |= (1 << E);
		PORTA &= ~(1 << F);
		PORTA |= (1 << G);
		PORTB &= ~(1 << DOT);
		break;
	case 3:
		PORTA |= (1 << A);
		PORTA |= (1 << B);
		PORTA |= (1 << C);
		PORTA |= (1 << D);
		PORTA &= ~(1 << E);
		PORTA &= ~(1 << F);
		PORTA |= (1 << G);
		PORTB &= ~(1 << DOT);
		break;
	case 4:
		PORTA &= ~(1 << A);
		PORTA |= (1 << B);
		PORTA |= (1 << C);
		PORTA &= ~(1 << D);
		PORTA &= ~(1 << E);
		PORTA |= (1 << F);
		PORTA |= (1 << G);
		PORTB &= ~(1 << DOT);
		break;
	case 5:
		PORTA |= (1 << A);
		PORTA &= ~(1 << B);
		PORTA |= (1 << C);
		PORTA |= (1 << D);
		PORTA &= ~(1 << E);
		PORTA |= (1 << F);
		PORTA |= (1 << G);
		PORTB &= ~(1 << DOT);
		break;
	case 6:
		PORTA |= (1 << A);
		PORTA &= ~(1 << B);
		PORTA |= (1 << C);
		PORTA |= (1 << D);
		PORTA |= (1 << E);
		PORTA |= (1 << F);
		PORTA |= (1 << G);
		PORTB &= ~(1 << DOT);
		break;
	case 7:
		PORTA |= (1 << A);
		PORTA |= (1 << B);
		PORTA |= (1 << C);
		PORTA &= ~(1 << D);
		PORTA &= ~(1 << E);
		PORTA &= ~(1 << F);
		PORTA &= ~(1 << G);
		PORTB &= ~(1 << DOT);
		break;
	case 8:
		PORTA |= (1 << A);
		PORTA |= (1 << B);
		PORTA |= (1 << C);
		PORTA |= (1 << D);
		PORTA |= (1 << E);
		PORTA |= (1 << F);
		PORTA |= (1 << G);
		PORTB &= ~(1 << DOT);
		break;
	case 9:
		PORTA |= (1 << A);
		PORTA |= (1 << B);
		PORTA |= (1 << C);
		PORTA |= (1 << D);
		PORTA &= ~(1 << E);
		PORTA |= (1 << F);
		PORTA |= (1 << G);
		PORTB &= ~(1 << DOT);
		break;
	case 10:
		PORTA |= (1 << A);
		PORTA |= (1 << B);
		PORTA |= (1 << C);
		PORTA &= ~(1 << D);
		PORTA |= (1 << E);
		PORTA |= (1 << F);
		PORTA |= (1 << G);
		PORTB &= ~(1 << DOT);
		break;
	case 11:
		PORTA &= ~(1 << A);
		PORTA &= !(1 << B);
		PORTA |= (1 << C);
		PORTA |= (1 << D);
		PORTA |= (1 << E);
		PORTA |= (1 << F);
		PORTA |= (1 << G);
		PORTB &= ~(1 << DOT);
		break;
	case 12:
		PORTA |= (1 << A);
		PORTA &= ~(1 << B);
		PORTA &= ~(1 << C);
		PORTA |= (1 << D);
		PORTA |= (1 << E);
		PORTA |= (1 << F);
		PORTA &= ~(1 << G);
		PORTB &= ~(1 << DOT);
		break;
	case 13:
		PORTA &= ~(1 << A);
		PORTA |= (1 << B);
		PORTA |= (1 << C);
		PORTA |= (1 << D);
		PORTA |= (1 << E);
		PORTA &= ~(1 << F);
		PORTA |= (1 << G);
		PORTB &= ~(1 << DOT);
		break;
	case 14:
		PORTA |= (1 << A);
		PORTA &= ~(1 << B);
		PORTA &= ~(1 << C);
		PORTA |= (1 << D);
		PORTA |= (1 << E);
		PORTA |= (1 << F);
		PORTA |= (1 << G);
		PORTB &= ~(1 << DOT);
		break;
	case 15:
		PORTA |= (1 << A);
		PORTA &= ~(1 << B);
		PORTA &= ~(1 << C);
		PORTA &= ~(1 << D);
		PORTA |= (1 << E);
		PORTA |= (1 << F);
		PORTA |= (1 << G);
		PORTB &= ~(1 << DOT);
		break;
	default:
		PORTA &= ~(1 << A);
		PORTA &= ~(1 << B);
		PORTA &= ~(1 << C);
		PORTA &= ~(1 << D);
		PORTA &= ~(1 << E);
		PORTA &= ~(1 << F);
		PORTA &= ~(1 << G);
		PORTB |= (1 << DOT);
		break;
	}
}


void segment_init(void)
{
	// 0b 1111 1110
	// 0b 0000 0001
	// 0b 1100 0000

	DDRA |= 0xFE;
	DDRB |= 0x01;
	DDRC |= 0xC0;

	PORTC |= 0xC0;

	seven_segment(INITIAL_VALUE);
}