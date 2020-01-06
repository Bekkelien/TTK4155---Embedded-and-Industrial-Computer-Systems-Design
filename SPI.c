/*
* CFile1.c
*
* Created: 15.10.2016 12:50:05
*  Author: espebek
*/

#include "SPI.h"

////////////////////////////////////////
/////////////// SPI_Init ///////////////
////////////////////////////////////////

void SPI_Init(void){
	
	DDRB |= (1<<PB4)|(1<<PB5)|(1<<PB7);						// Setter SS som output, Setter MOSI som output, Setter SCK (Clock) som output
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);					// Aktiverer SPI, Master, CLK: fck/16
	DDRB &= ~(1<<PB6);										// Setter MISO som input
	
	PORTB |= (1<<PB6);                                      // Internal Pull-up på SPI
	
	//DDRE |= (1<<PE0);										// Setter PE0 som interuptpin
}

////////////////////////////////////////
//////////////// SPI ON ////////////////
////////////////////////////////////////

void SS_Aktiver(void){
	PORTB &= ~(1<<PB4);
}

////////////////////////////////////////
///////////// SPI Sende data ///////////
////////////////////////////////////////

int SPI_Transmit(uint8_t Spi_data){
	SPDR = Spi_data;										// Start sending
	while(!(SPSR & (1<<SPIF)));								// Vent til data er sendt
	return 0;
}

////////////////////////////////////////
///////////// SPI Mota data ////////////
////////////////////////////////////////

uint8_t SPI_Receive(void){
	SPDR = 0x00;
	while(!(SPSR & (1<<SPIF))){
		//wait
	}
	return SPDR;
}

////////////////////////////////////////
/////////////// SPI Off ////////////////
////////////////////////////////////////

void SS_Deaktiver(void){
	PORTB |= (1<<PB4);
}