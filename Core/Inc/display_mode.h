/*
 * display_mode.h
 *
 *  Created on: Nov 24, 2021
 *      Author: Khiem
 */

#ifndef INC_DISPLAY_MODE_H_
#define INC_DISPLAY_MODE_H_

typedef enum
{
	MODE_1_NORMAL,
	MODE_2_MODIFY_RED,
	MODE_3_MODIFY_AMBER,
	MODE_4_MODIFY_GREEN,
	NUM_OF_MODES
} mode_t;

// for button_event.c
void begin_mode(void);
void increase_duration_value(void);
void save_selected_duration_value(void);

// for loop in main.c
void display_mode(void);
void scan_7seg_led(void);
void main_init(void);

#endif /* INC_DISPLAY_MODE_H_ */
