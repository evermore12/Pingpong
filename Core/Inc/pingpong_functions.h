/*
 * pingpong_functions.h
 *
 *  Created on: Nov 3, 2026
 *      Author: test
 */

#ifndef INC_PINGPONG_FUNCTIONS_H_
#define INC_PINGPONG_FUNCTIONS_H_
#include "stdbool.h"
typedef enum{
	SPEED_SLOW = 500,
	SPEED_MEDIUM = 250,
	SPEED_FAST = 100,
}speed;
#define NUM_LEDS 8
extern const uint8_t ALL_LEDS[NUM_LEDS];
void Led_on(uint8_t Lednr);
void Leds_blink(uint8_t n, const uint8_t Lednrs[], speed Speed, uint8_t Times);
void Led_blink(uint8_t Lednr, speed Speed, uint8_t Times);
void Show_points(uint8_t L_points, uint8_t R_points, float Seconds);
bool L_hit(void);
bool R_hit(void);
#endif /* INC_PINGPONG_FUNCTIONS_H_ */
