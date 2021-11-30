/*
 * button_event.c
 *
 *  Created on: Nov 23, 2021
 *      Author: Khiem
 */
#include "button_event.h"

#include "button_debouncing.h"
#include <stdbool.h>
#include "led.h"
#include "display_mode.h"
#include "timer.h"

typedef enum
{
	BTN_RELEASED,
	BTN_PRESSED,
	BTN_PRESSED_MORE_THAN_1S
} btn_event_t;

static btn_event_t btn_event_buf[NUM_OF_BUTTONS];
extern bool b_flag_buf[NUM_OF_TIMERS];
extern mode_t mode;

void event_btn_1(void)
{
	switch (btn_event_buf[BUTTON_1])
	{
		case BTN_RELEASED:
		{
			if (is_button_pressed(BUTTON_1))
			{
				turn_all_off();
				mode = (mode >= NUM_OF_MODES-1) ? MODE_1_NORMAL : mode+1;
				begin_mode();
				btn_event_buf[BUTTON_1] = BTN_PRESSED;
			}
		}
		break;
		case BTN_PRESSED:
		{
			if(!is_button_pressed(BUTTON_1))
			{
				btn_event_buf[BUTTON_1] = BTN_RELEASED;
			}
		}
		break;
		default:
		break;
	}
}

void event_btn_2(void)
{
	switch (btn_event_buf[BUTTON_2])
	{
		case BTN_RELEASED:
		{
			if (is_button_pressed(BUTTON_2))
			{
				increase_duration_value();
				btn_event_buf[BUTTON_2] = BTN_PRESSED;
			}
		}
		break;
		case BTN_PRESSED:
		{
			if (!is_button_pressed(BUTTON_2))
			{
				btn_event_buf[BUTTON_2] = BTN_RELEASED;
			}
			else if (is_button_pressed_1s(BUTTON_2))
			{
				set_timer(TMR_AUTO_INCREASING_DURATION, TIMER_AUTO_INCREASING_DURATION);
				btn_event_buf[BUTTON_2] = BTN_PRESSED_MORE_THAN_1S;
			}
		}
		break;
		case BTN_PRESSED_MORE_THAN_1S:
		{
			if (!is_button_pressed(BUTTON_2))
			{
				btn_event_buf[BUTTON_2] = BTN_RELEASED;
			}
			else
			{
				if (b_flag_buf[TMR_AUTO_INCREASING_DURATION])
				{
					increase_duration_value();
					set_timer(TMR_AUTO_INCREASING_DURATION, TIMER_AUTO_INCREASING_DURATION);
				}
			}
		}
		break;
		default:
		break;
	}
}

void event_btn_3(void)
{
	switch (btn_event_buf[BUTTON_3])
	{
		case BTN_RELEASED:
		{
			if (is_button_pressed(BUTTON_3))
			{
				save_selected_duration_value();
				btn_event_buf[BUTTON_3] = BTN_PRESSED;
			}
		}
		break;
		case BTN_PRESSED:
		{
			if(!is_button_pressed(BUTTON_3))
			{
				btn_event_buf[BUTTON_3] = BTN_RELEASED;
			}
		}
		break;
		default:
		break;
	}
}
