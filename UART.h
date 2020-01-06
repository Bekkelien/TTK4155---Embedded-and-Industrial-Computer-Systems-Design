/*
* UART.h
*
* Created: 06.09.2016 16:43:57
*  Author: dagfinae
*/


#define BAUD 9600
#define FOSC 4915200// Klokke hastighet
#define F_CPU 4915200UL
#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h>

void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
