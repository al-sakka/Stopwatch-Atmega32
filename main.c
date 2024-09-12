/*
 * main.c
 *
 *  Created on: Sep 10, 2024
 *      Author: sakka
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "HAL/7Segment/7segment.h"
#include "HAL/Buttons/buttons.h"
#include "HAL/time_utils/time_utils.h"
#include "MCAL/GPIO/gpio.h"
#include "MCAL/Interrupts/interrupts.h"
#include "MCAL/Timer/timer.h"
#include "include/defines.h"


int main(void)
{
	Pins_Init();
	TIMER1_Init();
	INT0_Init();
	INT1_Init();
	INT2_Init();
	sei();

	while(1)
	{
		checkMode();
		show_number_on_segment();
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(countMode == MODE_COUNT_UP)
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
