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
#define CMP_VALUE 15625 // (F_CPU / 1024)

unsigned char isModeBtnPressed = 0;

unsigned char isControlHours1Pressed = 0;
unsigned char isControlHours2Pressed = 0;

unsigned char isControlMins1Pressed = 0;
unsigned char isControlMins2Pressed = 0;

unsigned char isControlSecs1Pressed = 0;
unsigned char isControlSecs2Pressed = 0;

unsigned char countMode = 1; // 1 count-up | 0 Count-down

signed char seconds_1 = 0;
signed char seconds_2 = 0;

signed char minutes_1 = 0;
signed char minutes_2 = 0;

signed char hours_1 = 0;
signed char hours_2 = 0;

unsigned char endCondition = 0;

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

	if(!countMode)
	{
		PORTD &= ~(1 << PD0);
		pauseTimer();
	}
}

void resumeTimer(void)
{
	if(countMode)
	{
		TCCR1B |= (1 << CS10) | (1 << CS12);
	}
	else
	{
		endCondition = (seconds_1 + seconds_2 + minutes_1 + minutes_2 + hours_1 + hours_2);

		if(endCondition)
		{
			TCCR1B |= (1 << CS10) | (1 << CS12);
		}
	}
}

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

	sei();
}

void TIMER1_Init(void)
{
	TCCR1A = 0;
	TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS12);

	TIMSK |= (1 << OCIE1A);

	TCNT1 = 0;

	OCR1A = CMP_VALUE;
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
	if(countMode)
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
	else
	{
		if(seconds_1 < 0 && seconds_2 > 0)
		{
			seconds_1 = 9;
			seconds_2--;
		}

		if(seconds_1 < 0 && minutes_1 > 0)
		{
			minutes_1--;

			seconds_1 = 9;
			seconds_2 = 5;
		}

		if(seconds_1 < 0 && minutes_2 > 0 && minutes_1 == 0)
		{
			minutes_2--;
			minutes_1 = 9;

			seconds_1 = 9;
			seconds_2 = 5;
		}

		if(minutes_1 < 0 && minutes_2 > 0)
		{
			minutes_1 = 9;
			minutes_2--;
		}

		if(minutes_1 < 0 && hours_1 > 0)
		{
			hours_1--;

			minutes_1 = 9;
			minutes_2 = 5;
		}

		if(hours_1 < 0 && hours_2 > 0)
		{
			hours_1 = 9;
			hours_2--;
		}

		if(hours_1 < 0)
		{
			hours_1 = 0;
		}

		if(seconds_1 < 0 && hours_1 > 0)
		{
			hours_1--;

			seconds_1 = 9;
			seconds_2 = 5;

			minutes_1 = 9;
			minutes_2 = 5;
		}

		if(seconds_1 < 0 && hours_2 > 0 && hours_1 == 0 && minutes_1 == 0 && minutes_2 == 0)
		{
			hours_2--;
			hours_1 = 9;

			minutes_2 = 5;
			minutes_1 = 9;

			seconds_2 = 5;
			seconds_1 = 9;
		}
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

void decHours(void)
{
	hours_1--;

	if(hours_1 < 0 && hours_2 > 0)
	{
		hours_1 = 9;
		hours_2--;
	}

	if(hours_1 < 0)
	{
		hours_1 = 0;
	}
}

void incHours(void)
{
	hours_1++;

	if(hours_2 == 9 && hours_1 > 9)
	{
		hours_1 = 9;
	}

	if(hours_1 > 9)
	{
		hours_1 = 0;
		hours_2++;
	}

	if(hours_2 > 9)
	{
		hours_2 = 9;
	}

}

void decMinutes(void)
{
	minutes_1--;

	if(minutes_1 < 0 && minutes_2 > 0)
	{
		minutes_1 = 9;
		minutes_2--;
	}

	if(minutes_1 < 0)
	{
		minutes_1 = 0;
	}
}

void incMinutes(void)
{
	minutes_1++;

	if(minutes_2 == 5 && minutes_1 > 9)
	{
		minutes_1 = 9;
	}

	if(minutes_1 > 9)
	{
		minutes_1 = 0;
		minutes_2++;
	}

	if(minutes_2 > 9)
	{
		minutes_2 = 9;
	}
}

void decSecs(void)
{
	seconds_1--;

	if(seconds_1 < 0 && seconds_2 > 0)
	{
		seconds_1 = 9;
		seconds_2--;
	}

	if(seconds_1 < 0)
	{
		seconds_1 = 0;
	}
}

void incSecs(void)
{
	seconds_1++;

	if(seconds_2 == 5 && seconds_1 > 9)
	{
		seconds_1 = 9;
	}

	if(seconds_1 > 9)
	{
		seconds_1 = 0;
		seconds_2++;
	}

	if(seconds_2 > 5)
	{
		seconds_2 = 5;
	}
}

void countDwnBtns(void)
{
	if(!(PINB & (1 << PB0)))
	{
		_delay_ms(10);
		if(!(PINB & (1 << PB0)) && !isControlHours1Pressed)
		{
			isControlHours1Pressed = 1;
			decHours();
		}
	}
	else
	{
		isControlHours1Pressed = 0;
	}

	if(!(PINB & (1 << PB1)))
	{
		_delay_ms(10);
		if(!(PINB & (1 << PB1)) && !isControlHours2Pressed)
		{
			isControlHours2Pressed = 1;
			incHours();
		}
	}
	else
	{
		isControlHours2Pressed = 0;
	}

	////

	if(!(PINB & (1 << PB3)))
	{
		_delay_ms(10);
		if(!(PINB & (1 << PB3)) && !isControlMins1Pressed)
		{
			isControlMins1Pressed = 1;
			decMinutes();
		}
	}
	else
	{
		isControlMins1Pressed = 0;
	}

	if(!(PINB & (1 << PB4)))
	{
		_delay_ms(10);
		if(!(PINB & (1 << PB4)) && !isControlMins2Pressed)
		{
			isControlMins2Pressed = 1;
			incMinutes();
		}
	}
	else
	{
		isControlMins2Pressed = 0;
	}

	////

	if(!(PINB & (1 << PB5)))
	{
		_delay_ms(10);
		if(!(PINB & (1 << PB5)) && !isControlSecs1Pressed)
		{
			isControlSecs1Pressed = 1;
			decSecs();
		}
	}
	else
	{
		isControlSecs1Pressed = 0;
	}

	if(!(PINB & (1 << PB6)))
	{
		_delay_ms(10);
		if(!(PINB & (1 << PB6)) && !isControlSecs2Pressed)
		{
			isControlSecs2Pressed = 1;
			incSecs();
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
		_delay_ms(10);
		if(!(PINB & (1 << PB7)) && !isModeBtnPressed)
		{
			isModeBtnPressed = 1;
			countMode = !countMode;

			PORTD &= ~(1 << PD0);
		}
	}
	else
	{
		isModeBtnPressed = 0;
	}

	if(countMode)
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

void checkAlarm(void)
{
	if (!(seconds_1 || seconds_2 || minutes_1 || minutes_2 || hours_1 || hours_2))
	{
		PORTD |= (1 << PD0);
		pauseTimer();
	}
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
		checkMode();
		show_number_on_segment();
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(countMode)
	{
		seconds_1++;
	}
	else
	{
		seconds_1--;
		checkAlarm();
	}

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
