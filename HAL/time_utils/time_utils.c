/*
 * time_utils.c
 *
 *  Created on: Sep 12, 2024
 *      Author: sakka
 */

#include "time_utils.h"
#include <avr/io.h>
#include "../../include/defines.h"

void time_logic(void)
{
	if(countMode == MODE_COUNT_UP)
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

void decTime(signed char *low, signed char *high, signed char max_low, signed int max_high)
{
	(*low)--;

	if(*low < 0 && *high > 0)
	{
		*low = max_low;
		(*high)--;
	}

	if(*low < 0)
	{
		*low = 0;
	}
}

void incTime(signed char *low, signed char *high, signed char max_low, signed int max_high)
{
	(*low)++;

	if(*high == max_high && *low > 9)
	{
		*low = max_low;
	}

	if(*low > max_low)
	{
		*low = 0;
		(*high)++;
	}

	if(*high > max_high)
	{
		*high = max_high;
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
