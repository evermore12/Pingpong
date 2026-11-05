/**
******************************************************************************
@brief   Pingpong statemachine for Pingpong-program
@file    pingpong.c
@author  Bengt Molin
@version 1.0
@date    12-August-2019
@brief   Functions and structures for program Pingpong

******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "pingpong.h"
#include <stdbool.h>
#include "main.h"
#include "pingpong_functions.h"

/* Define states for state machine*/
typedef enum
{  Start,
MoveRight,
MoveLeft,
ShowPoints,
Gameover,
ServeL,
ServeR

} states;
bool Serve_L;
static states State, NextState;
typedef struct Tick
{
	uint32_t CYCLE;
	uint32_t CYCLE_MAX; //Cycle defines speed.
}Tick;
void Pingpong(void)
{
	bool ButtonPressed = false ;  // To remember that button is pressed

	uint32_t Varv, Speed, InitialSpeed, Speedup, MaxSpeed; // Ball speed
	uint8_t Led;   // LED nr

	uint8_t R_points = 0, L_points = 0;
	Tick FLASH_LED = {0, 2000000};

	State= Start;     // Initiate State to Start
	NextState= Start;

	InitialSpeed = 500000; // Number of loops
	Speed = InitialSpeed;
	Speedup = 1000*5; //(Amount of speed up, 1000 * Multiplier)
	MaxSpeed = Speed - Speedup*8*9;
	/* Infinite loop */
	while (1)
	{
		State = NextState;
		switch (State) // State machine
		{
		case Start:
			Led_on(0);  // Turn off all LEDs

			if ( L_hit() == true )        // L serve
			{
				Led = 1;
				NextState= MoveRight;
				Serve_L = true;
				while ( L_hit() == true );  // wait until button is released
			}
			else if ( R_hit() == true )   // R serve
			{
				Led = 8;
				NextState= MoveLeft;
				Serve_L = false;
				while ( R_hit() == true );  // wait until button is released
			}
			else
				NextState = Start;  // Stay in Start state
			break;
		case Gameover:
			Show_points(L_points, R_points, 1);
			NextState=Start;
			break;
		case ShowPoints:
			Leds_blink(NUM_LEDS, ALL_LEDS, SPEED_FAST, 2);
			Show_points(L_points, R_points, 1);
			Speed = InitialSpeed;
			if(R_points == 4 || L_points == 4)
				NextState = Gameover;
			else
			{
				if(Serve_L) NextState=ServeR;
				else NextState=ServeL;
			}
			break;
		case ServeL:
			FLASH_LED.CYCLE++;
			if(FLASH_LED.CYCLE > FLASH_LED.CYCLE_MAX)
			{
				Led_blink(1, SPEED_FAST, 3);
				FLASH_LED.CYCLE = 0;
			}
			if ( L_hit() == true )        // L serve
			{
				Led = 1;
				NextState= MoveRight;
				Serve_L = true;
				while ( L_hit() == true );  // wait until button is released
			}
			break;
		case ServeR:
			FLASH_LED.CYCLE++;
			if(FLASH_LED.CYCLE > FLASH_LED.CYCLE_MAX)
			{
				Led_blink(8, SPEED_FAST, 3);
				FLASH_LED.CYCLE = 0;
			}
			if ( R_hit() == true )   // R serve
			{
				Led = 8;
				NextState= MoveLeft;
				Serve_L = false;
				while ( R_hit() == true );  // wait until button is released
			}
			break;
		case MoveRight:
			{
				Led_on(Led);
				Varv = Speed;

				if(Speed>MaxSpeed)
					Speed-=Speedup;
				while(Varv != 0)
				{
					if ( R_hit() ) ButtonPressed = true;  // R hit
					Varv--;
				}

				if ( ButtonPressed )   // R pressed
				{
					if ( Led == 8 )  // and LED8 active
					{
						NextState=MoveLeft;   // return ball
						Led=7;
					}
					else
					{
						NextState = ShowPoints;   // hit to early
						L_points++;
					}

				}
				else
				{
					if ( Led == 9 )
					{
						NextState = ShowPoints;
						L_points++;// no hit or to late
					}
					else
						NextState = MoveRight;  // ball continues to move right
				}
				if ( !ButtonPressed ) Led++; // prepare to turn next LED on
				ButtonPressed=false;
			}
			break;

		case MoveLeft:
			{
				Led_on(Led);
				Varv = Speed;

				if(Speed>MaxSpeed)
					Speed-=Speedup;
				while(Varv != 0)
				{
					if ( L_hit() ) ButtonPressed = true;  // L hit
					Varv--;
				}

				if ( ButtonPressed )   // L pressed
				{
					if ( Led == 1 )  // and LED1 active
					{
						NextState=MoveRight;   // return ball
						Led=2;
					}
					else
					{
						NextState = ShowPoints;   // hit to early
						R_points++;
					}
				}
				else
				{
					if ( Led == 0 )
					{
						NextState = ShowPoints;
						R_points++;
					}

					else
						NextState = MoveLeft;  // ball continues to move left
				}
				if ( !ButtonPressed ) Led--; // prepare to turn next LED on
				ButtonPressed=false;

			}
			break;

		default:
			break;
		}
	}
}  // End of function Pingpong
