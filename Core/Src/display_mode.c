/*
 * display_mode.c
 *
 *  Created on: Nov 24, 2021
 *      Author: Khiem
 */
#include "display_mode.h"

#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "led.h"

static light_t traffic_light_state[2];
static uint8_t selected_duration_buf[3];
static uint8_t modified_duration_buf[3];
static uint8_t duration_buf[2];
static uint8_t tmp[2];
extern bool b_flag_buf[NUM_OF_TIMERS];
mode_t mode;

static void traffic_light(uint8_t index)
{
	if (index >= 2) return;
	switch (traffic_light_state[index])
	{
		case RED_1:
		{
			turn_on(RED_1);
			duration_buf[index] = selected_duration_buf[0] - tmp[index];
			if (b_flag_buf[TMR_TRAFFIC_LIGHT_1])
			{
				tmp[index]++;
				if (tmp[index] == selected_duration_buf[0])
				{
					tmp[index] = 0;
					traffic_light_state[index] = GREEN_1;
				}
				set_timer(TMR_TRAFFIC_LIGHT_1, TIMER_COUNTING_DOWN);
			}
		}
		break;
		case AMBER_1:
		{
			turn_on(AMBER_1);
			duration_buf[index] = selected_duration_buf[1] - tmp[index];
			if (b_flag_buf[TMR_TRAFFIC_LIGHT_1])
			{
				tmp[index]++;
				if (tmp[index] == selected_duration_buf[1])
				{
					tmp[index] = 0;
					traffic_light_state[index] = RED_1;
				}
				set_timer(TMR_TRAFFIC_LIGHT_1, TIMER_COUNTING_DOWN);
			}
		}
		break;
		case GREEN_1:
		{
			turn_on(GREEN_1);
			duration_buf[index] = selected_duration_buf[2] - tmp[index];
			if (b_flag_buf[TMR_TRAFFIC_LIGHT_1])
			{
				tmp[index]++;
				if (tmp[index] == selected_duration_buf[2])
				{
					tmp[index] = 0;
					traffic_light_state[index] = AMBER_1;
				}
				set_timer(TMR_TRAFFIC_LIGHT_1, TIMER_COUNTING_DOWN);
			}
		}
		break;
		case RED_2:
		{
			turn_on(RED_2);
			duration_buf[index] = selected_duration_buf[0] - tmp[index];
			if (b_flag_buf[TMR_TRAFFIC_LIGHT_2])
			{
				tmp[index]++;
				if (tmp[index] == selected_duration_buf[0])
				{
					tmp[index] = 0;
					traffic_light_state[index] = GREEN_2;
				}
				set_timer(TMR_TRAFFIC_LIGHT_2, TIMER_COUNTING_DOWN);
			}
		}
		break;
		case AMBER_2:
		{
			turn_on(AMBER_2);
			duration_buf[index] = selected_duration_buf[1] - tmp[index];
			if (b_flag_buf[TMR_TRAFFIC_LIGHT_2])
			{
				tmp[index]++;
				if (tmp[index] == selected_duration_buf[1])
				{
					tmp[index] = 0;
					traffic_light_state[index] = RED_2;
				}
				set_timer(TMR_TRAFFIC_LIGHT_2, TIMER_COUNTING_DOWN);
			}
		}
		break;
		case GREEN_2:
		{
			turn_on(GREEN_2);
			duration_buf[index] = selected_duration_buf[2] - tmp[index];
			if (b_flag_buf[TMR_TRAFFIC_LIGHT_2])
			{
				tmp[index]++;
				if (tmp[index] == selected_duration_buf[2])
				{
					tmp[index] = 0;
					traffic_light_state[index] = AMBER_2;
				}
				set_timer(TMR_TRAFFIC_LIGHT_2, TIMER_COUNTING_DOWN);
			}
		}
		break;
		default:
		break;
	}
}

void main_init(void)
{
	set_timer(TMR_TRAFFIC_LIGHT_1, TIMER_COUNTING_DOWN);
	set_timer(TMR_TRAFFIC_LIGHT_2, TIMER_COUNTING_DOWN);
	set_timer(TMR_SCANNING_7SEG_LED, TIMER_INTERRUPT);

	mode = MODE_1_NORMAL;

	selected_duration_buf[0] = 5;
	selected_duration_buf[1] = 2;
	selected_duration_buf[2] = 3;

	traffic_light_state[0] = RED_1;
	traffic_light_state[1] = GREEN_2;
}

void display_mode(void)
{
	switch (mode)
	{
		case MODE_1_NORMAL:
		{
			traffic_light(0);
			traffic_light(1);

			display_7seg_led(duration_buf[0], duration_buf[1]);
		}
		break;
		case MODE_2_MODIFY_RED:
		{
			if (b_flag_buf[TMR_BLINKING_LED])
			{
				blink(RED_1);
				blink(RED_2);
				set_timer(TMR_BLINKING_LED, TIMER_BLINKING_LED);
			}

			display_7seg_led(modified_duration_buf[0], 2);
		}
		break;
		case MODE_3_MODIFY_AMBER:
		{
			if (b_flag_buf[TMR_BLINKING_LED])
			{
				blink(AMBER_1);
				blink(AMBER_2);
				set_timer(TMR_BLINKING_LED, TIMER_BLINKING_LED);
			}

			display_7seg_led(modified_duration_buf[1], 3);
		}
		break;
		case MODE_4_MODIFY_GREEN:
		{
			if (b_flag_buf[TMR_BLINKING_LED])
			{
				blink(GREEN_1);
				blink(GREEN_2);
				set_timer(TMR_BLINKING_LED, TIMER_BLINKING_LED);
			}

			display_7seg_led(modified_duration_buf[2], 4);
		}
		break;
		default:
		break;
	}
}

void scan_7seg_led(void)
{
	if (b_flag_buf[TMR_SCANNING_7SEG_LED])
	{
		scan_led_buf();
		set_timer(TMR_SCANNING_7SEG_LED, TIMER_SCANNING_7SEG_LED);
	}
}

void begin_mode(void)
{
	if (mode == MODE_1_NORMAL)
	{
		traffic_light_state[0] = RED_1;
		traffic_light_state[1] = GREEN_2;
		set_timer(TMR_TRAFFIC_LIGHT_1, TIMER_COUNTING_DOWN);
		set_timer(TMR_TRAFFIC_LIGHT_2, TIMER_COUNTING_DOWN);
		set_timer(TMR_SCANNING_7SEG_LED, TIMER_INTERRUPT);
		tmp[0] = 0;
		tmp[1] = 0;
	}
	else if (mode == MODE_2_MODIFY_RED)
	{
		set_timer(TMR_BLINKING_LED, TIMER_BLINKING_LED);
		modified_duration_buf[0] = selected_duration_buf[0];
	}
	else if (mode == MODE_3_MODIFY_AMBER)
	{
		set_timer(TMR_BLINKING_LED, TIMER_BLINKING_LED);
		modified_duration_buf[1] = selected_duration_buf[1];
	}
	else if (mode == MODE_4_MODIFY_GREEN)
	{
		set_timer(TMR_BLINKING_LED, TIMER_BLINKING_LED);
		modified_duration_buf[2] = selected_duration_buf[2];
	}
}

void increase_duration_value(void)
{
	if (mode == MODE_2_MODIFY_RED)
	{
		modified_duration_buf[0] = (modified_duration_buf[0] >= 99) ? 0 : modified_duration_buf[0]+1;
	}
	else if (mode == MODE_3_MODIFY_AMBER)
	{
		modified_duration_buf[1] = (modified_duration_buf[1] >= 99) ? 0 : modified_duration_buf[1]+1;
	}
	else if (mode == MODE_4_MODIFY_GREEN)
	{
		modified_duration_buf[2] = (modified_duration_buf[2] >= 99) ? 0 : modified_duration_buf[2]+1;
	}
}

void save_selected_duration_value(void)
{
	if (mode == MODE_2_MODIFY_RED)
	{
		selected_duration_buf[0] = modified_duration_buf[0];
	}
	else if (mode == MODE_3_MODIFY_AMBER)
	{
		selected_duration_buf[1] = modified_duration_buf[1];
	}
	else if (mode == MODE_4_MODIFY_GREEN)
	{
		selected_duration_buf[2] = modified_duration_buf[2];
	}
}
