/*
* CFile1.c
*
* Created: 15.09.2016 10:26:00
*  Author: dagfinae
*/


#include "ADC.h"


//////////////////////////////////////////////////
/////////// ADC Driver, kanal 0-3 ////////////////
//////////////////////////////////////////////////

void ADC_start(uint8_t channel){
	
	volatile char* ext_adc = (char *) 0x1400;				// Peker til ADC adressen
	
	if (channel == 0)ext_adc[0] = (char *) 0x4;				// Setter opp channel 0
	else if (channel == 1) ext_adc[0] = (char *) 0x5;		// Setter opp channel 1
	else if (channel == 2) ext_adc[0] = (char *) 0x6;		// Setter opp channel 2
	else if (channel == 3) ext_adc[0] = (char *) 0x7;		// Setter opp channel 3	
	
}

uint8_t ADC_read(void){
	
	volatile char* ext_adc = (char *) 0x1400;				// Peker til ADC adressen
	while (PINE & (1 << PINE2)){
		//Wait												// Venter til ADC verdien er avlest
	} 
	return *ext_adc;
}
