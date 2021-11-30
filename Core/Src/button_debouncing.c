/*
 * button.c
 *
 *  Created on: Nov 22, 2021
 *      Author: Khiem
 */
#include "button_debouncing.h"

#include <stdint.h>
#include "main.h"

#define 	TIMER_INTERRUPT					10
#define 	DURATION_BUTTON_PRESSED_1S		(1000 / TIMER_INTERRUPT)
#define 	PRESSED							GPIO_PIN_SET
#define 	RELEASED						GPIO_PIN_RESET

static GPIO_PinState btn_debounced_buf[NUM_OF_BUTTONS];
static GPIO_PinState btn_state_prev_buf[NUM_OF_BUTTONS];
static GPIO_PinState btn_state_curr_buf[NUM_OF_BUTTONS];
static bool b_flag_btn_pressed_1s_buf[NUM_OF_BUTTONS];
static uint16_t counter_btn_pressed_1s_buf[NUM_OF_BUTTONS];

static GPIO_PinState read_button_pin(button_t btn)
{
	if (btn == BUTTON_1) return HAL_GPIO_ReadPin(BTN_0_GPIO_Port, BTN_0_Pin);
	else if (btn == BUTTON_2) return HAL_GPIO_ReadPin(BTN_1_GPIO_Port, BTN_1_Pin);
	else if (btn == BUTTON_3) return HAL_GPIO_ReadPin(BTN_2_GPIO_Port, BTN_2_Pin);

	return RELEASED;
}

void button_reading(void)
{
	for (button_t btn = BUTTON_1; btn < NUM_OF_BUTTONS; btn++)
	{
		btn_state_prev_buf[btn] = btn_state_curr_buf[btn];
		btn_state_curr_buf[btn] = read_button_pin(btn);
		if (btn_state_curr_buf[btn] == btn_state_prev_buf[btn])
		{
			btn_debounced_buf[btn] = btn_state_curr_buf[btn];
			if (btn_debounced_buf[btn] == PRESSED)
			{
				if (counter_btn_pressed_1s_buf[btn] < DURATION_BUTTON_PRESSED_1S)
				{
					counter_btn_pressed_1s_buf[btn]++;
				}
				else
				{
					b_flag_btn_pressed_1s_buf[btn] = true;
				}
			}
			else
			{
				counter_btn_pressed_1s_buf[btn] = 0;
				b_flag_btn_pressed_1s_buf[btn] = false;
			}
		}
	}
}

bool is_button_pressed(button_t btn)
{
	if (btn >= NUM_OF_BUTTONS) return false;
	return (btn_debounced_buf[btn] == PRESSED);
}

bool is_button_pressed_1s(button_t btn)
{
	if (btn >= NUM_OF_BUTTONS) return false;
	return b_flag_btn_pressed_1s_buf[btn];
}

