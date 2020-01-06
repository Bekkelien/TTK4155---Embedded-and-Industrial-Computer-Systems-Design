/*
* Gameplay.c
*
* Created: 13.11.2016 12:23:21
*  Author: espebek
*/

#include "Gameplay.h"


//////////////////////////////////
////////// Teller score //////////
//////////////////////////////////

void Score(void){
	Timer1 = Timer1 +1;
	if(Timer1 == 6){
		Timer2 = Timer2 + 1;
		Timer1 = 0;
		sprintf(Time, "%d", Timer2);
		Oled_position(3,79);
		Oled_print(Time);
	}
}

//////////////////////////////////////////////
/////// Sjekker om man har tapt //////////////
////////////////////////////////// ///////////

void End_Game(void){
	while(PIND & (1<<PD5)){
		//Wait
		Oled_Game_over();
		Oled_position(3,70);
		Oled_print(Time);	
		Main_menu_option_sub = 1;
		Timer1 = 0;
		Timer2 = 0;
		
		_delay_ms(10000);
		Oled_clear();
		Meny();
	}
}


