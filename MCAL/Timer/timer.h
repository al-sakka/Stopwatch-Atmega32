/*
 * timer.h
 *
 *  Created on: Sep 12, 2024
 *      Author: sakka
 */

#ifndef TIMER_H_
#define TIMER_H_

#define F_CPU 16000000UL
#define CMP_VALUE 15625

void TIMER1_Init(void);
void pauseTimer(void);
void resetTimer(void);
void resumeTimer(void);


#endif /* TIMER_H_ */
