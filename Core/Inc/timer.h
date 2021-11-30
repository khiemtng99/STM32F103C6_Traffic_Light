/*
 * timer.h
 *
 *  Created on: Nov 23, 2021
 *      Author: Khiem
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"

#define 	TIMER_INTERRUPT						10

#define 	TIMER_COUNTING_DOWN					1000
#define 	TIMER_BLINKING_LED					250
#define		TIMER_AUTO_INCREASING_DURATION		250
#define		TIMER_SCANNING_7SEG_LED				250

typedef enum
{
	TMR_TRAFFIC_LIGHT_1,
	TMR_TRAFFIC_LIGHT_2,
	TMR_BLINKING_LED,
	TMR_AUTO_INCREASING_DURATION,
	TMR_SCANNING_7SEG_LED,
	NUM_OF_TIMERS
} timer_name_t;

void set_timer(timer_name_t tmr, uint16_t duration);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /* INC_TIMER_H_ */
