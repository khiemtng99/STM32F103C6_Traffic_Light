/*
 * button.h
 *
 *  Created on: Nov 22, 2021
 *      Author: Khiem
 */

#ifndef INC_BUTTON_DEBOUNCING_H_
#define INC_BUTTON_DEBOUNCING_H_

#include <stdbool.h>

typedef enum
{
	BUTTON_1,
	BUTTON_2,
	BUTTON_3,
	NUM_OF_BUTTONS
} button_t;

void button_reading(void);
bool is_button_pressed(button_t btn);
bool is_button_pressed_1s(button_t btn);

#endif /* INC_BUTTON_DEBOUNCING_H_ */
