/*
 * main.c
 *
 *  Created on: Sep 10, 2024
 *      Author: sakka
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL

#define DELAY_VALUE 5
#define CMP_VALUE 15625
#define TICKS_PER_SEC 1

unsigned char ticks = 0;

unsigned char seconds_1 = 0;
unsigned char seconds_2 = 0;

unsigned char minutes_1 = 0;
unsigned char minutes_2 = 0;

unsigned char hours_1 = 0;
unsigned char hours_2 = 0;

void resetTimer(void)
{
	TCNT1 = 0;

	seconds_1 = 0;
	seconds_2 = 0;
	minutes_1 = 0;
	minutes_2 = 0;
	hours_1 = 0;
	hours_2 = 0;
}

void pauseTimer(void)
{
	TCCR1B &= ~(1 << CS10) & ~(1 << CS11) & ~(1 << CS12);
}

void resumeTimer(void)
{
	TCCR1B |= (1 << CS10) | (1 << CS12);
}

void Pins_Init(void)
{
	DDRC |= 0x0F;
	DDRA |= 0x3F;
	DDRD &= ~(1 << PD2) & ~(1 << PD3);
	DDRB &= ~(1 << PB2);

	PORTC &= ~(0x0F);
	PORTA &= ~(0x3F);
	PORTD |= (1 << PD2);
	PORTB |= (1 << PB2);

	sei();
}

void TIMER1_Init(void)
{
	TCCR1A = (1 << COM1A0);
	TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS12);

	TIMSK |= (1 << OCIE1A);

	TCNT1 = 0;

	OCR1A = CMP_VALUE; // Compare Value
}

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

void time_logic(void)
{
	if(seconds_1 > 9)
	{
		seconds_1 = 0;
		seconds_2++;
	}

	if(seconds_2 > 5)
	{
		seconds_2 = 0;
		minutes_1++;
	}

	if(minutes_1 > 9)
	{
		minutes_1 = 0;
		minutes_2++;
	}

	if(minutes_2 > 5)
	{
		minutes_2 = 0;
		hours_1++;
	}


	if(hours_1 > 9)
	{
		hours_1 = 0;
		hours_2++;
	}

	if(hours_2 > 9)
	{
		resetTimer();
	}

}

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

int main(void)
{
	Pins_Init();
	TIMER1_Init();
	INT0_Init();
	INT1_Init();
	INT2_Init();

	while(1)
	{
		show_number_on_segment();
	}
}

ISR(TIMER1_COMPA_vect)
{
	seconds_1++;
	time_logic();
}

ISR(INT0_vect)
{
	resetTimer();
}

ISR(INT1_vect)
{
	pauseTimer();
}

ISR(INT2_vect)
{
	resumeTimer();
}
