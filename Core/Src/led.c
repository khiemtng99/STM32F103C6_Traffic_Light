/*
 * led.c
 *
 *  Created on: Nov 23, 2021
 *      Author: Khiem
 */
#include "led.h"

#include "main.h"

#define		ON		GPIO_PIN_RESET
#define 	OFF		GPIO_PIN_SET

static uint8_t led_7seg_buf[10] = { 0x01, 0x4f, 0x12, 0x06, 0x4c, 0x24, 0x20, 0x0f, 0x00, 0x04 };
static uint8_t led_buf[4];
static uint8_t led_index;

static void display_num(uint8_t number)
{
	if (number >= 10) return;
	HAL_GPIO_WritePin(SEG_0_GPIO_Port, SEG_0_Pin, (led_7seg_buf[number] & 0x40) >> 6);
	HAL_GPIO_WritePin(SEG_1_GPIO_Port, SEG_1_Pin, (led_7seg_buf[number] & 0x20) >> 5);
	HAL_GPIO_WritePin(SEG_2_GPIO_Port, SEG_2_Pin, (led_7seg_buf[number] & 0x10) >> 4);
	HAL_GPIO_WritePin(SEG_3_GPIO_Port, SEG_3_Pin, (led_7seg_buf[number] & 0x08) >> 3);
	HAL_GPIO_WritePin(SEG_4_GPIO_Port, SEG_4_Pin, (led_7seg_buf[number] & 0x04) >> 2);
	HAL_GPIO_WritePin(SEG_5_GPIO_Port, SEG_5_Pin, (led_7seg_buf[number] & 0x02) >> 1);
	HAL_GPIO_WritePin(SEG_6_GPIO_Port, SEG_6_Pin, (led_7seg_buf[number] & 0x01));
}

static void enable_7seg_led(uint8_t index)
{
	if (index == 0)
	{
		HAL_GPIO_WritePin(EN_0_GPIO_Port, EN_0_Pin, ON);
		HAL_GPIO_WritePin(EN_0_GPIO_Port, EN_1_Pin | EN_2_Pin | EN_3_Pin, OFF);
	}
	else if (index == 1)
	{
		HAL_GPIO_WritePin(EN_1_GPIO_Port, EN_1_Pin, ON);
		HAL_GPIO_WritePin(EN_1_GPIO_Port, EN_0_Pin | EN_2_Pin | EN_3_Pin, OFF);
	}
	else if (index == 2)
	{
		HAL_GPIO_WritePin(EN_2_GPIO_Port, EN_2_Pin, ON);
		HAL_GPIO_WritePin(EN_2_GPIO_Port, EN_1_Pin | EN_0_Pin | EN_3_Pin, OFF);
	}
	else if (index == 3)
	{
		HAL_GPIO_WritePin(EN_3_GPIO_Port, EN_3_Pin, ON);
		HAL_GPIO_WritePin(EN_3_GPIO_Port, EN_1_Pin | EN_2_Pin | EN_0_Pin, OFF);
	}
}

void scan_led_buf(void)
{
	enable_7seg_led(led_index);
	display_num(led_buf[led_index]);
	led_index = (led_index >= 3) ? 0 : led_index+1;
}

void display_7seg_led(uint8_t num_1, uint8_t num_2)
{
	led_buf[0] = num_1 / 10;
	led_buf[1] = num_1 % 10;
	led_buf[2] = num_2 / 10;
	led_buf[3] = num_2 % 10;
}

void turn_on(light_t light)
{
	if (light == RED_1)
	{
		HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin, ON);
		HAL_GPIO_WritePin(RED_1_GPIO_Port, AMBER_1_Pin | GREEN_1_Pin, OFF);
	}
	else if (light == AMBER_1)
	{
		HAL_GPIO_WritePin(RED_1_GPIO_Port, AMBER_1_Pin, ON);
		HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin | GREEN_1_Pin, OFF);
	}
	else if (light == GREEN_1)
	{
		HAL_GPIO_WritePin(RED_1_GPIO_Port, GREEN_1_Pin, ON);
		HAL_GPIO_WritePin(RED_1_GPIO_Port, AMBER_1_Pin | RED_1_Pin, OFF);
	}
	else if (light == RED_2)
	{
		HAL_GPIO_WritePin(RED_2_GPIO_Port, RED_2_Pin, ON);
		HAL_GPIO_WritePin(RED_2_GPIO_Port, AMBER_2_Pin | GREEN_2_Pin, OFF);
	}
	else if (light == AMBER_2)
	{
		HAL_GPIO_WritePin(RED_2_GPIO_Port, AMBER_2_Pin, ON);
		HAL_GPIO_WritePin(RED_2_GPIO_Port, RED_2_Pin | GREEN_2_Pin, OFF);
	}
	else if (light == GREEN_2)
	{
		HAL_GPIO_WritePin(RED_2_GPIO_Port, GREEN_2_Pin, ON);
		HAL_GPIO_WritePin(RED_2_GPIO_Port, AMBER_2_Pin | RED_2_Pin, OFF);
	}
}

void blink(light_t light)
{
	if (light == RED_1)
	{
		HAL_GPIO_TogglePin(RED_1_GPIO_Port, RED_1_Pin);
	}
	else if (light == AMBER_1)
	{
		HAL_GPIO_TogglePin(AMBER_1_GPIO_Port, AMBER_1_Pin);
	}
	else if (light == GREEN_1)
	{
		HAL_GPIO_TogglePin(GREEN_1_GPIO_Port, GREEN_1_Pin);
	}
	else if (light == RED_2)
	{
		HAL_GPIO_TogglePin(RED_2_GPIO_Port, RED_2_Pin);
	}
	else if (light == AMBER_2)
	{
		HAL_GPIO_TogglePin(AMBER_2_GPIO_Port, AMBER_2_Pin);
	}
	else if (light == GREEN_2)
	{
		HAL_GPIO_TogglePin(GREEN_2_GPIO_Port, GREEN_2_Pin);
	}
}

void turn_all_off(void)
{
	HAL_GPIO_WritePin(RED_1_GPIO_Port, RED_1_Pin | AMBER_1_Pin | GREEN_1_Pin | RED_2_Pin | AMBER_2_Pin | GREEN_2_Pin, OFF);
}

