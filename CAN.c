/*
* CFile2.c
*
* Created: 27.10.2016 09:22:17
*  Author: dagfinae
*/

#include "CAN.h"
#include "MCP.h"
#include "MCP2515.h"


///////////////////////////////////////////////////////////
////////////////////  CAN Driver //////////////////////////
///////////////////////////////////////////////////////////

int CAN_Init(void){
	
	MCP_Init();																	//Set MCP to configuration mode
	MCP_BitModify(MCP_CANINTE, 0x01, 1);					
	MCP_BitModify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);                         //Set MCP_CANCTRL to Normal mode
	
	uint8_t MCP_Status;
	
	MCP_Status = MCP_Read(MCP_CANSTAT);
	printf("Status MCP = %d \n" , MCP_Status);
	
	
	return 0;
}

///////////////////////////////////////////////////////////
//////////////// Sjekker CAN Bufferet /////////////////////
///////////////////////////////////////////////////////////

int CAN_Check_Transmit_Register(void){
	if (test_bit(MCP_Read(MCP_TXB0CTRL),3)){
		return 0;
		} else {
		return 1;
	}
}

///////////////////////////////////////////////////////////
//////////////Sjekker for feilsending CAN//////////////////
///////////////////////////////////////////////////////////


int CAN_Error(void){
	if(test_bit(MCP_Read(MCP_TXB0CTRL),5)){										// Check if the message was lost
		return 1;
	}
	if(test_bit(MCP_Read(MCP_TXB0CTRL),4)){										// Check if the message transmission encountered an error condition
		return 1;
	}
}

///////////////////////////////////////////////////////////
////////////////// Sende Data over CAN/////////////////////
///////////////////////////////////////////////////////////


int CAN_Transmit(CAN_Message_t* message, uint8_t buffer){
	
	if(CAN_Check_Transmit_Register()){
		
		///////// Meldings-ID/////////
		
		MCP_Write((MCP_TXB0SIDH), (int8_t)(message->id) >> 3);
		MCP_Write((MCP_TXB0SIDL), (int8_t)(message->id)<< 5);
		
		///////// Meldingslengde /////////
		MCP_Write(MCP_TXB0DLC, (0x0F) & (message->length));
		
		///////// Meldingsdata /////////
		for (int i=0; i < message->length; i++){
			MCP_Write(MCP_TXB0D0 + i, message->data[i]);
			
			MCP_Request_To_Send(MCP_RTS_TX0 | (1<<buffer));
			
			uint8_t Data_send1,Data_send2, Data_send3;
			Data_send1 = MCP_Read(0x30);
			Data_send2 = MCP_Read(0x40);
			Data_send3 = MCP_Read(0x50);
			
			printf("Data1 = %d Data2 = %d Data3 = %d", Data_send1, Data_send2, Data_send3);
			
		}
		
		printf("Data er sendt \n");
		
	}
	
	//else {
	///	if (CAN_Error() > 0)
	//	printf("Ikke sendt \n");
	//	return -1;
	//}
	
}

///////////////////////////////////////////////////////////
////////////////// Mota Data over CAN//////////////////////
///////////////////////////////////////////////////////////

CAN_Message_t CAN_data_receive(void) {
	
	CAN_Message_t message;

	if(test_bit(MCP_Read(MCP_CANINTF), 0)){
		//if(CAN_Interupt == 1){
		
		// Motta meldings-ID
		message.id  = (MCP_Read(MCP_RXB0SIDH) << 3) | (MCP_Read(MCP_RXB0SIDL) >> 5);
		
		// Motta meldingslengde
		message.length = (0x0F) & (MCP_Read(MCP_RXB0DLC));
		
		// Motta meldingsdata
		for(int i = 0; i < message.length; i++) {
			message.data[i] = MCP_Read(MCP_RXB0D0 + i);
		}
		
		//CAN_Interupt = 0;
		//MCP_BitModify(MCP_CANINTF, 0x01, 0);	// Clear CAN_Interrupt
		
	}
	else {
		message.id = -1;
	}
	
	printf("Motatt melding %d   %d   %d \n", message.id, message.length, message.data[0]);
	
	return message;
}

///////////////////////////////////////////////////////////
////////////////// Interupt for CAN ///////////////////////
///////////////////////////////////////////////////////////

/*
//Interupt for CAN
ISR(INT0_vect){
_delay_ms(20);
CAN_Interupt = 1;
}*/
