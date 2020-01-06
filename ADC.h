/*
* CFile1.c
*
* Created: 15.09.2016 10:26:14
*  Author: dagfinae
*/

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void ADC_start(uint8_t channel);
uint8_t ADC_read(void);
