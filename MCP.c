/*
* CFile1.c
*
* Created: 20.10.2016 09:42:35
*  Author: dagfinae
*/

#include "MCP.h"
#include "SPI.h"
#include "MCP2515.h"

////////////////////////////////////////
////////////Restater MCP////////////////
////////////////////////////////////////

void MCP_Reset(void){
	SS_Aktiver();
	SPI_Transmit(MCP_RESET);
	_delay_ms(1);
	SS_Deaktiver();
}

////////////////////////////////////////
////////////// MCP INIT/////////////////
////////////////////////////////////////

uint8_t MCP_Init(void){
	SPI_Init();
	MCP_Reset();														// Send reset-command
	
	//////////// Self-test //////////
	uint8_t value = MCP_Read(MCP_CANSTAT);
	if((value & MODE_MASK) != MODE_CONFIG) {
		printf("MCP is NOT in configuration mode afterreset!\n");
		return 1;
	}
	////////// More initialization //////////
	
	return 0;
}

////////////////////////////////////////
////////////// Leser MCP ///////////////
////////////////////////////////////////

uint8_t MCP_Read(uint8_t MCP_address){
	SS_Aktiver();
	SPI_Transmit(MCP_READ);												 // MCPen leser data
	SPI_Transmit(MCP_address);
	uint8_t result = SPI_Receive();
	SS_Deaktiver();

	return result;
}

////////////////////////////////////////
///////// Skriver over MCP//////////////
////////////////////////////////////////

void MCP_Write(uint8_t Address, uint8_t MCP_Data){
	SS_Aktiver();
	SPI_Transmit(MCP_WRITE);
	SPI_Transmit(Address);
	SPI_Transmit(MCP_Data);
	SS_Deaktiver();
	
}

////////////////////////////////////////
////// Spør om å sende over MCP/////////
////////////////////////////////////////

void MCP_Request_To_Send(uint8_t CAN_Buffer){
	SS_Aktiver();
	SPI_Transmit(CAN_Buffer);
	SS_Deaktiver();
	
}

////////////////////////////////////////
////////// Leser MCP status ////////////
////////////////////////////////////////

uint8_t MCP_ReadStatus(void){
	SS_Aktiver();
	SPI_Transmit(MCP_READ_STATUS);
	uint8_t result = SPI_Receive;
	SS_Deaktiver();
	return result;
}


////////////////////////////////////////
/////////// MCP Bit Modify /////////////
////////////////////////////////////////

void MCP_BitModify(uint8_t address, uint8_t mask, uint8_t data){
	SS_Aktiver();
	SPI_Transmit(MCP_BITMOD);
	SPI_Transmit(address);
	SPI_Transmit(mask);
	SPI_Transmit(data);
	SS_Deaktiver();
	
	// Modify command byte is then sent to the MCP2515.
	// The command is followed by the address of the
	// register, the mask byte and finally the data byte.
	
}



