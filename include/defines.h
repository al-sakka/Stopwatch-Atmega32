/*
 * defines.h
 *
 *  Created on: Sep 12, 2024
 *      Author: sakka
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#define F_CPU 16000000UL

#define DELAY_VALUE 5
#define DEBOUNCE_VALUE 20
#define CMP_VALUE 15625 // (F_CPU / 1024)

#define ONES_CMP 9
#define TENS_CMP 5

// Global variables
extern unsigned char isModeBtnPressed;
extern unsigned char isControlHours1Pressed;
extern unsigned char isControlHours2Pressed;
extern unsigned char isControlMins1Pressed;
extern unsigned char isControlMins2Pressed;
extern unsigned char isControlSecs1Pressed;
extern unsigned char isControlSecs2Pressed;

extern signed char seconds_1;
extern signed char seconds_2;
extern signed char minutes_1;
extern signed char minutes_2;
extern signed char hours_1;
extern signed char hours_2;

// Enumeration type for mode selection
typedef enum
{
    MODE_COUNT_DOWN,
    MODE_COUNT_UP
} CountMode;

extern CountMode countMode;

#endif

