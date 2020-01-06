/*
* CFile1.c
*
* Created: 20.10.2016 09:43:08
*  Author: dagfinae
*/


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void MCP_Reset(void);
uint8_t MCP_Init(void);
uint8_t MCP_Read(uint8_t address);
void MCP_Write(uint8_t address, uint8_t MCP_Data);
void MCP_BitModify(uint8_t address, uint8_t mask, uint8_t data);
uint8_t MCP_ReadStatus(void);
void MCP_Request_To_Send(uint8_t CAN_Buffer);


