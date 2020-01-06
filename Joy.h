/*
* CFile1.c
*
* Created: 22.09.2016 15:20:10
*  Author: dagfinae
*/


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>

bool Button_left;
bool Button_right;
bool Joy_button;

uint8_t adcReturnVal_UD;
uint8_t adcReturnVal_RL;
uint8_t adcReturnVal_Slider_L;
uint8_t adcReturnVal_Slider_R;

int8_t adcReturnVal_y;
int8_t adcReturnVal_x;

int skyter;


void Joy_read(void);
void Slider_read(void);
int CAN_JOY_Position_x(void);
int CAN_JOY_Position_Y(void);
int CAN_Slider_read(void);
void Shooter(void);