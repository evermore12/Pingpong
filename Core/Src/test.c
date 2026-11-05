/*
 * test.c
 *
 *  Created on: Nov 3, 2026
 *      Author: test
 */
#include <stdint.h>
#include "main.h"
#include "pingpong_functions.h"
void Test_buttons(void)
{
	int8_t j;
	/* Checking buttons */
	j=4;
	Led_on(j); // Light on
	while (j<9 && j>0)
	{
		if ( L_hit() == true ) // Wait for left button hit
		{
			j++; // next led to the right
			Led_on(j); // Light on
			HAL_Delay(5); // 5 ms
			while ( L_hit() == true ); // Wait for button release
			HAL_Delay(5); // 5 ms
		}
		if ( R_hit() == true ) // Wait for right button hit
		{
			j--; // next led to the left
			Led_on(j); // Light on
			HAL_Delay(5); // 5 ms
			while ( R_hit() == true ); // Wait for button release
			HAL_Delay(5); // 5 ms
			if (j<1) j=0; // Start again from left
		}
	}
	return;
}
void Test_show_points(void)
{
	int8_t R_points;
	int8_t L_points;
	for(R_points = 0; R_points<=4; R_points++){
		for(L_points = 0; L_points<=4; L_points++){
			Show_points(L_points, R_points, 1);
		}
	}
}
void Test_led_blink(void)
{
	uint8_t i;
	for(i=1; i<=8; i++)
	{
		Led_blink(i, SPEED_SLOW, 3);
		HAL_Delay(500);
		Led_blink(i, SPEED_MEDIUM, 3);
		HAL_Delay(500);
		Led_blink(i, SPEED_FAST, 3);
		HAL_Delay(500);
	}
}
void Test_leds_blink(void)
{
	Leds_blink(NUM_LEDS, ALL_LEDS, SPEED_SLOW, 10);
	HAL_Delay(500);
	Leds_blink(NUM_LEDS, ALL_LEDS, SPEED_MEDIUM, 10);
	HAL_Delay(500);
	Leds_blink(NUM_LEDS, ALL_LEDS, SPEED_FAST, 10);
	HAL_Delay(500);

}
void Test_led(void)
{
	int8_t Lednr;
	/* Loop checking that all leds can be turned on*/
	for (Lednr=1; Lednr<= 8; Lednr++) {
		Led_on(Lednr);
		HAL_Delay(500);
	}
	Led_on(9); // Turn off led 8
	HAL_Delay(1000); // 1000 ms
	return;
}

void Test_program(void)
{
	//Test_led();
	//Test_show_points();
	//Test_buttons();
	Test_led_blink();
	//Test_leds_blink();
}

