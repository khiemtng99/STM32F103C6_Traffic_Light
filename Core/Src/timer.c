/*
 * timer.c
 *
 *  Created on: Nov 23, 2021
 *      Author: Khiem
 */
#include "timer.h"

#include <stdint.h>
#include <stdbool.h>
#include "button_debouncing.h"

static uint16_t counter_buf[NUM_OF_TIMERS];
bool b_flag_buf[NUM_OF_TIMERS];

void set_timer(timer_name_t tmr, uint16_t duration)
{
	if (tmr >= NUM_OF_TIMERS) return;
	counter_buf[tmr] = duration / TIMER_INTERRUPT;
	b_flag_buf[tmr] = false;
}

static void run_timer(void)
{
	for (timer_name_t tmr = TMR_TRAFFIC_LIGHT_1; tmr < NUM_OF_TIMERS; tmr++)
	{
		if (counter_buf[tmr] > 0)
		{
			counter_buf[tmr]--;
			if(counter_buf[tmr] == 0) b_flag_buf[tmr] = true;
		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2)
	{
		button_reading();
		run_timer();
	}
}
