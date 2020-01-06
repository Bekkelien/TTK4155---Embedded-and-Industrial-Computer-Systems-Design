/*
* CFile1.c
*
* Created: 22.09.2016 15:19:45
*  Author: dagfinae
*/


#include "Joy.h"
#include "ADC.h"
#include "CAN.h"

//////////////////////////////////
///////// Leser JOYSTICK /////////
//////////////////////////////////

void Joy_read(void){
	ADC_start(0);													// Leser Opp og ned
	
	adcReturnVal_UD = ADC_read();
	adcReturnVal_y = (((adcReturnVal_UD)*(100)/(255))-(50));
	
	ADC_start(1);													// Leser Høyre og venstre
	
	adcReturnVal_RL = ADC_read();
	adcReturnVal_x = (((adcReturnVal_RL)*(100)/(255))-(50));
	
	
	adcReturnVal_y = adcReturnVal_y * 2;
	adcReturnVal_x = adcReturnVal_x * 2;
	
	printf("Y = %d   X = %d\n", adcReturnVal_y, adcReturnVal_x);
	
	if ((PINB & (1<<PB0) == 1) != 1){
		
		Joy_button = 1;
	}
	
	if ((PINB & (1<<PB0) == 1) == 1){
		
		Joy_button = 0;
	}
}

//////////////////////////////////
////////// Leser Silder //////////
//////////////////////////////////

void Slider_read(void){

	ADC_start(2);													 // Venstre slider
	adcReturnVal_Slider_L = ADC_read();
	adcReturnVal_Slider_L = ((adcReturnVal_Slider_L)*(100)/(255));


	ADC_start(3);													 // Høyre slider
	adcReturnVal_Slider_R = ADC_read();
	adcReturnVal_Slider_R = ((adcReturnVal_Slider_R)*(100)/(255));


	printf("Silder venste: %d Silder høyre: %d \n", adcReturnVal_Slider_L, adcReturnVal_Slider_R);

}

/////////////////////////////////////
/////////// JOY_X_OVER_CAN //////////
/////////////////////////////////////

int CAN_JOY_Position_x(void){
	
	ADC_start(1);													// Leser Høyre og venstre
	adcReturnVal_RL = ADC_read();
	_delay_us(50);
	adcReturnVal_x = (((adcReturnVal_RL)*(100)/(255))-(50));
	adcReturnVal_x = adcReturnVal_x * 2;
	adcReturnVal_x = adcReturnVal_x + 100;
	
	printf("\n adc_ReturnVal_x: %d", adcReturnVal_x);
	
	CAN_Message_t message;
	message.id = 1;
	message.length = 1;
	message.data[0] = adcReturnVal_x;
	
	CAN_Transmit(&message, 0);
	_delay_us(50);
	
	return adcReturnVal_x;
}
/////////////////////////////////////
/////////// JOY_Y_OVER_CAN //////////
/////////////////////////////////////

int CAN_JOY_Position_y(void){

	ADC_start(0);													// Leser Opp og ned
	adcReturnVal_UD = ADC_read();
	adcReturnVal_y = (((adcReturnVal_UD)*(100)/(255))-(50));
	adcReturnVal_y = adcReturnVal_y * 2;
	adcReturnVal_y = adcReturnVal_y + 100;

	CAN_Message_t message;
	message.id = 2;
	message.length = 1;
	message.data[0] = adcReturnVal_y;

	CAN_Transmit(&message, 0);

	return adcReturnVal_y;
}

////////////////////////////////////////
/////////// Silder_R_OVER_CAN //////////
////////////////////////////////////////

int CAN_Slider_read(void){

	ADC_start(3);													// Høyre slider
	adcReturnVal_Slider_R = ADC_read();
	adcReturnVal_Slider_R = ((adcReturnVal_Slider_R)*(100)/(255));

	CAN_Message_t message;
	message.id = 3;
	message.length = 1;
	message.data[0] = adcReturnVal_Slider_R;

	CAN_Transmit(&message, 0);

	return adcReturnVal_Slider_R;
}

////////////////////////////////////////
/////////// Shooter_OVER_CAN ///////////
////////////////////////////////////////

void Shooter(void){
	skyter = PIND & (1 << PIND4);
	if (skyter >= 1){
		CAN_Message_t message;
		message.id = 2;
		message.length = 1;
		message.data[0] = 10;
		
		CAN_Transmit(&message, 0);
		_delay_us(50);
		

		_delay_us(50);
		
	}
}

/////////////////////////////////////////
/////////// Kode for spill av ///////////
/////////////////////////////////////////

void CAN_GameMode(void){
	CAN_Message_t message;
	message.id = 4;
	message.length = 1;
	message.data[0] = 50;
}