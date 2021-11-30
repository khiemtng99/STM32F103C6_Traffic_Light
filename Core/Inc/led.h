/*
 * led.h
 *
 *  Created on: Nov 23, 2021
 *      Author: Khiem
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include <stdint.h>

typedef enum
{
	RED_1,
	AMBER_1,
	GREEN_1,
	RED_2,
	AMBER_2,
	GREEN_2,
	NUM_OF_LIGHTS
} light_t;

// for 7seg leds
void scan_led_buf(void);
void display_7seg_led(uint8_t num_1, uint8_t num_2);

// for traffic lights
void turn_on(light_t light);
void blink(light_t light);
void turn_all_off(void);

#endif /* INC_LED_H_ */
