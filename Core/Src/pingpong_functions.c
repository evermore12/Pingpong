/**
 ******************************************************************************
@brief Pingpong, functions for Pingpong-program
@file pingpong_functions.c
@author Jonathan Björnebro
@version 1.0
@date 12-November-2026
@brief Functions for the LEDs and buttons on the Pingpong board
@note Comment updated by AI (Claude)
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

/**
@brief Led_set, turn a single LED on or off without changing the others
@param Lednr uint8_t, number of the LED, 1-8. Other values are ignored
@param state GPIO_PinState, GPIO_PIN_SET turns the LED on, GPIO_PIN_RESET turns it off
@return void
@note Comment written by AI (Claude)
 */
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
/**
@brief Leds_set, turn several LEDs on or off at the same time
@param n uint8_t, number of LEDs in Lednrs
@param Lednrs const uint8_t[], the LED numbers (1-8) to change
@param state GPIO_PinState, GPIO_PIN_SET turns the LEDs on, GPIO_PIN_RESET turns them off
@return void
@note Comment written by AI (Claude)
 */
static void Leds_set(uint8_t n, const uint8_t Lednrs[], GPIO_PinState state)
{
	uint8_t i;
	for(i=0; i<n; i++)
		Led_set(Lednrs[i], state);
	return;
}

/**
@brief Leds_blink, blink several LEDs together, used to mark a missed ball
Blocks while blinking. All LEDs are off when the function returns.
@param n uint8_t, number of LEDs in Lednrs
@param Lednrs const uint8_t[], the LED numbers (1-8) to blink
@param Speed speed, time in ms that the LEDs are on, and then off, in each blink
@param Times uint8_t, the loop runs Times+1 times, so the LEDs blink Times+1 times
@return void
@note Comment written by AI (Claude)
 */
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

/**
@brief Show_points, shows points after missed ball
L's points light LEDs from LED1 inwards and R's points light LEDs from LED8
inwards. Example: L=2 and R=3 lights LED 1, 2 and 6, 7, 8.
Blocks while the score is shown. All LEDs are off when the function returns.
@param L_points uint8_t, points for left player, 0-4
@param R_points uint8_t, points for right player, 0-4
@param Seconds float, how long the score is shown, in seconds
@return void, no return value
@note Comment written by AI (Claude)
 */
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

/**
@brief Led_blink, blink a single LED, used to show whose turn it is to serve
All other LEDs are off while it blinks. Blocks while blinking.
@param Lednr uint8_t, number of the LED to blink, 1-8
@param Speed speed, time in ms that the LED is on, and then off, in each blink
@param Times uint8_t, number of blinks
@return void
@note Comment written by AI (Claude)
 */
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

