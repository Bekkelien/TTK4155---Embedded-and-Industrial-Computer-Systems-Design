/*
* CFile1.c
*
* Created: 15.10.2016 12:49:50
*  Author: espebek
*/


#include <avr/io.h>

void SPI_Init(void);
void SS_Aktiver(void);
int SPI_Transmit(uint8_t Spi_data);
uint8_t SPI_Receive(void);
void SS_Deaktiver(void);

