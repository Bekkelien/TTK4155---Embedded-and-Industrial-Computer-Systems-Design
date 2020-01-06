/*
* CFile2.c
*
* Created: 27.10.2016 09:22:35
*  Author: dagfinae
*/

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "BitManipulation.h"

typedef struct {
	int id;
	uint8_t length;
	int data[8];
} CAN_Message_t;


uint8_t CAN_Interupt;


int CAN_Init();
int CAN_Check_Transmit_Register(void);
CAN_Message_t CAN_data_receive(void);
int CAN_Transmit(CAN_Message_t* message, uint8_t buffer);
int CAN_Error(void);
//ISR(INT0_vect);