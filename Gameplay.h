/*
 * Gameplay.h
 *
 * Created: 13.11.2016 12:23:39
 *  Author: espebek
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "Menu.h"


uint8_t Timer1;
uint8_t Timer2;
uint8_t Result;

int skyter;

char Time[5];


void Score(void);
void End_Game(void);

