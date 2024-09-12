/*
 * time_utils.h
 *
 *  Created on: Sep 12, 2024
 *      Author: sakka
 */

#ifndef TIME_UTILS_H_
#define TIME_UTILS_H_

void time_logic(void);
void decTime(signed char *low, signed char *high, signed char max_low, signed int max_high);
void incTime(signed char *low, signed char *high, signed char max_low, signed int max_high);
void checkAlarm(void);

#endif
