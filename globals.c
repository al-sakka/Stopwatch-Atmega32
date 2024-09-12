/*
 * globals.c
 *
 *  Created on: Sep 12, 2024
 *      Author: sakka
 */


#include "include/defines.h"

// Global variables initialization
unsigned char isModeBtnPressed = 0;

unsigned char isControlHours1Pressed = 0;
unsigned char isControlHours2Pressed = 0;
unsigned char isControlMins1Pressed = 0;
unsigned char isControlMins2Pressed = 0;
unsigned char isControlSecs1Pressed = 0;
unsigned char isControlSecs2Pressed = 0;

signed char seconds_1 = 0;
signed char seconds_2 = 0;
signed char minutes_1 = 0;
signed char minutes_2 = 0;
signed char hours_1 = 0;
signed char hours_2 = 0;

CountMode countMode = MODE_COUNT_UP;
