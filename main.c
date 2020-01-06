

/////////////////////////////////// TTK4155-BYGGERN /////////////////////////////////////////
////////////////////////////// NTNU-HØST-2016-Gruppe 56 /////////////////////////////////////
////// Nøkkelord: CAN / ADC / DAC / SPI / OLED / UART / SRAM / MCP / ATMEGA / Motor /////////
/////////// Prosjekt av: Espen Bekkelien, Dagfinn Nærheim and Per Kristian Pöcher ///////////

//////////////////////////////////
///////Eksterne bibilotek ////////
//////////////////////////////////

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdbool.h>


//////////////////////////////////
//////// Inerne bibilotek ////////
//////////////////////////////////
#include "MCP2515.h"
#include "UART.h"											// UART for å skrive tekst til PC
#include "TestSRAM.h"										// Program for test av SRAM
#include "ADC.h"											// ADC_start og ADC_read
#include "Character.h"										// Kode for symboler til display
#include "Oled.h"											// Oled
#include "joy.h"											// Joystick
#include "Menu.h"											// Menysystem
#include "SPI.h"											// SPI Interface
#include "MCP.h"											// MCP
#include "CAN.h"											// CAN
#include "BitManipulation.h"								// BitManipulation
#include "Gameplay.h"										// Gameplay


int main(void)												// Program start
{
	/////////////////////////////////////////////////////////////////
	///////////// Initialisering av variabler og driver /////////////
	/////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////
	/////// Setter forhåndsbestemte variabler ///////
	/////////////////////////////////////////////////
	
	menu_arrow = 1;											// Menypilens posisons variabel
	Main_menu_option = 1;									// Menyverdi som angir hvilken meny som er valgt
	Main_menu_option_sub =1;								// Menyverdi som angir hvilken sub meny som er valgt
	CAN_Interupt = 0;										// Setter Can interupt til 0;

	
	Timer1 = 0;												// Setter "Timer0"
	Timer2 = 0;												// Setter "Timer1"
	
	CAN_Message_t message;
	
	////////////////////////////////////////////
	/////// Setter utganger og innganger ///////
	////////////////////////////////////////////
	
	MCUCR |= (1 << SRE);									// Aktiverer External memory interface
	SFIOR |= (1 << XMM2);									// Frigjør JTAG interface
	
	DDRD &= ~(1<<PD2);										// Setter PD2 til interrupt for CAN
	PORTD |= (1<<PD2);										// Setter PD2 pullup
	GICR |= (1<<INT0);										// Aktiverer interrupt vector
	
	DDRD &= ~(1<<PD3);										// Setter PD3 til input Venstre knapp
	DDRD &= ~(1<<PD4);										// Setter PD4 til input Høyre knapp
	DDRD &= ~(1<<PD5);										// Setter PD5 til input for game over
	DDRB &= ~(1<<PB0);										// Setter PE0 til input, Brukers til JOYstick knapp
	DDRE &= ~(1<<PE2);										// Setter PE2 til input, Interuptpin til ADC
	
	DDRB |= (1<<PB3);										// Output til soilinoid
	PORTB |= (1<<PB3);										// Setter spolinoid i nedre posisjon
	
	//////////////////////////////////
	/////// Setter UART CONFIG ///////
	//////////////////////////////////
	
	USART_Init ( MYUBRR );									// UART initialisering
	fdevopen(USART_Transmit, USART_Receive);				// Linker printf til USART Transmit/Receive
	
	CAN_Init();												// Initaliserer CAN / SPI / MCP og setter den i loopback mode
	
	///////////////////////////
	/////// Start Oled ///////
	//////////////////////////
	Oled_start();											// Initialiserer skjermen
	Oled_clear();											// Clearer skjermen
	Menu_start();											// Booting game
	Meny();													// Går til menyen
	
	sei();													// Setter global interupt
	
	while(1){
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////// Kontinuerlig program ////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//////////////////////////////////////////////////
		////////////////// Menysystem ////////////////////
		//////////////////////////////////////////////////
		
		if(Main_menu_option_sub == 1){
			Meny();												// Starter menyen
		}
		Joy_read();											// Leser Joy posisjon
		Menusystem();										// Menysystem
		Menupointer_Down();									// Menyvelger ned
		Menupointer_Up();									// Menyvelger opp
		_delay_ms(600);										// Forsinkelse for menyvelger
	
		CAN_GameMode();										// Sier ifra om at vi ikke spiller
		
		/////////////////////////////
		/////// Start spillet ///////
		/////////////////////////////
		
		while(Main_menu_option_sub == 2){					// Start spillet
			CAN_JOY_Position_x();							// Leser posisjonen til joystickens x retning
			CAN_Slider_read();								// Leser Høyre slider for servo posisjon
			Shooter();										// Sender Meling over CAN om shooter knappen er trykt
			Score();										// Teller poengscore
			End_Game();										// Skjekker om man har tapt
		}
		
		
		/////////////////////////////////////////////////////////////////
		//////////// KODE SOM HAR BLITT BENYTTET FOR TESTING ////////////
		/////////////////////////////////////////////////////////////////
		
		//PORTB |= (1<<PB2);
		
		//MCP_Reset();
		//MCP_Read(MCP_CANSTAT);
		
		//MCP_Write(0xAA, 0xFE);
		//MCP_Read(0xAA);
		
		//MCP_Read(0b01011110);
		//MCP_Request_To_Send(0b1000001);
		//MCP_Read(0b01011110);
		
		//MCP_Read(0b00001100);
		//MCP_BitModify(0b00001100 , 0b11111111 , 0b00000111);
		//MCP_Read(0b00001100);
		
		//Slider_read();
		//Oled_clear();
		//SRAM();
		
		/*
		Button_left = PIND & (1 << PIND3);
		printf("Button_left: %d \n", Button_left);
		_delay_ms(50);
		
		Button_right = PIND & (1 << PIND4);
		printf("Button_right: %d \n", Button_right);
		_delay_ms(50);
		
		//SRAM(); // Tester SRAMen via terminalen
		
		volatile char* ext_adc = (char *) 0x1400;
		ext_adc[0] = 0xFF;
		
		_delay_ms(1000);
		
		volatile char* ext_oled = (char *) 0x1000;
		ext_oled[0] = 0xFF;
		
		_delay_ms(1000);
		
		DDRD |= (1 << PD3); // Setter PC0 til output
		
		_delay_ms(500);
		PORTD |= (1 << PD3); // Setter PC0 HIGH
		_delay_ms(500);
		PORTD &= ~(1 << PD3); // Setter PC LOW
		
		printf("Heisann \n");
		printf("Per \n");
		*/
	}
}