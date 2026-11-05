/**
 ******************************************************************************
@brief Pingpong, functions for Pingpong-program
@file pingpong_functions.c
@author Jonathan Björnebro
@version 1.0
@date 12-August-2019
@brief Functions and structures for program Pingpong
 ******************************************************************************
 */
#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "pingpong_functions.h"

const uint8_t ALL_LEDS[NUM_LEDS] = {1,2,3,4,5,6,7,8};
/**
@brief L_hit, check if L button is pressed
@param void
@return bool, true if L button pushed, false otherwise
 */
bool L_hit(void)
{
	if (HAL_GPIO_ReadPin(L_button_GPIO_Port, L_button_Pin) == 0) return true;
	else return false;
}
/**
@brief R_hit, check if R button is pressed
@param void
@return bool, true if R button pushed, false otherwise
 */
bool R_hit(void)
{
	if (HAL_GPIO_ReadPin(R_button_GPIO_Port, R_button_Pin) == 0) return true;
	else return false;
}

static void Led_set(uint8_t Lednr, GPIO_PinState state)
{
	switch(Lednr)
	{
	case 1:
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, state);
		break;
	case 2:
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, state);
		break;
	case 3:
		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, state);
		break;
	case 4:
		HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, state);
		break;
	case 5:
		HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, state);
		break;
	case 6:
		HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, state);
		break;
	case 7:
		HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, state);
		break;
	case 8:
		HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, state);
		break;
	default:
		;
	}
	return;
}
/**
@brief Led_on, turn one of the pingpong leds on
@param uint8_t Lednr , number to the Led that is turned on
Lednr can be 1-8, all other values turns all leds off
@return void
 */
void Led_on(uint8_t Lednr)
{
	uint8_t i;
	for (i=1; i<=8; i++)
	{
		if(i == Lednr) Led_set(i, GPIO_PIN_SET);
		else Led_set(i, GPIO_PIN_RESET);
	}
	return;
}
static void Leds_set(uint8_t n, const uint8_t Lednrs[], GPIO_PinState state)
{
	uint8_t i;
	for(i=0; i<n; i++)
		Led_set(Lednrs[i], state);
	return;
}

//Simple blink leds function
void Leds_blink(uint8_t n, const uint8_t Lednrs[], speed Speed, uint8_t Times)
{
	uint8_t i;
	for(i = 0; i<=Times; i++)
	{
		Leds_set(n, Lednrs, GPIO_PIN_SET);
		HAL_Delay(Speed);
		Led_on(0);
		HAL_Delay(Speed);
	}

	return;
}
void New_round(uint8_t L_points, uint8_t R_points)
{
	HAL_Delay(300);
	//Blink_leds(NUM_LEDS, ALL_LEDS, 100);
	HAL_Delay(100);
	//Blink_leds(NUM_LEDS, ALL_LEDS, 100);
	HAL_Delay(250);
	//Show_points(1250);
	return;
}
void Show_points(uint8_t L_points, uint8_t R_points, float Seconds) //For how to long to show the points
{
	uint8_t i;
	for(i=1; i<=L_points; i++)
	{
		Led_set(i, GPIO_PIN_SET);
	}
	for(i=1; i<=R_points; i++)
	{
		Led_set(9-i, GPIO_PIN_SET);
	}
	HAL_Delay(1000 * Seconds);
	Led_on(0);
	return;
}

void Led_blink(uint8_t Lednr, speed Speed, uint8_t Times)
{
	uint8_t i;
	for(i=0; i<Times; i++)
	{
		Led_on(Lednr);
		HAL_Delay(Speed);
		Led_on(0);
		HAL_Delay(Speed);
	}
}

