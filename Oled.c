/*
* CFile1.c
*
* Created: 22.09.2016 16:19:08
*  Author: dagfinae
*/


#include "Oled.h"
#include "Character.h"


////////////////////////////////////////
///////////// Oled Adresse  ////////////
////////////////////////////////////////

void Oled_cmd(uint8_t cmd){
	
	volatile char* ext_oled_cmd = (char *) 0x1000;
	
	*ext_oled_cmd = cmd;

}


////////////////////////////////////////
////////////// Oled Iinit //////////////
////////////////////////////////////////

void Oled_start(){
	
	Oled_cmd(0xae);								 // display off
	Oled_cmd(0xa1);								 // segment remap
	Oled_cmd(0xda);								 // common pads hardware: alternative
	Oled_cmd(0x12);
	Oled_cmd(0xc8);								 // common output scan direction:com63~com0
	Oled_cmd(0xa8);								 // multiplex ration mode:63
	Oled_cmd(0x3f);
	Oled_cmd(0xd5);								 // display divide ratio/osc. freq. mode
	Oled_cmd(0x80);
	Oled_cmd(0x81);								 // contrast control
	Oled_cmd(0x50);
	Oled_cmd(0xd9);								 //set pre-charge period
	Oled_cmd(0x21);
	Oled_cmd(0x20);								 // Set Memory Addressing Mode
	Oled_cmd(0x02);
	Oled_cmd(0xdb);                              // VCOM deselect level mode
	Oled_cmd(0x30);
	Oled_cmd(0xad);								 // master configuration
	Oled_cmd(0x00);
	Oled_cmd(0xa4);								 // out follows RAM content
	Oled_cmd(0xa6);								 //set normal display
	Oled_cmd(0xaf);								 // display on

}


////////////////////////////////////////
///////// Sende data til Oleden ////////
////////////////////////////////////////

void Oled_data(uint8_t data){
	
	volatile char* ext_oled_data = (char *) 0x1200;

	*ext_oled_data = data;
	
}


////////////////////////////////////////
////////// Posisjon på Oleden  /////////
////////////////////////////////////////

void Oled_position(uint8_t linje, uint8_t kolonne){
	
	Oled_cmd(0x21);
	Oled_cmd(kolonne);
	Oled_cmd(127);
	
	Oled_cmd(0x22);
	Oled_cmd(linje);
	Oled_cmd(7);
	
}



////////////////////////////////////////
////////////// Oled linje  /////////////
////////////////////////////////////////

void Oled_line(uint8_t linje){					// 8 Pages and 128 Segments gir 8*128 = 1024 punkter
	
	Oled_cmd(0x00);
	Oled_cmd(0x10);
	Oled_cmd(linje);

	
	for(int i=00; i<=127; i++) {
		Oled_data(0x00);

	}
	
}


////////////////////////////////////////
/////////////// Oled Page //////////////
////////////////////////////////////////

void Oled_page(uint8_t kolonne){				// 8 Pages
	Oled_cmd(0x00);
	Oled_cmd(0x10);
	Oled_cmd(kolonne);

	
	for(int i=0; i<=7; i++) {
		Oled_data(0x00);

	}
}

////////////////////////////////////////
////////// Oled Clear skjerm ///////////
////////////////////////////////////////

void Oled_clear(void){							// 8 Pages and 128 Segments gir 8*128 = 1024 punkter
	for(int i=0; i<=7; i++){
		Oled_position(i,0);
		
		for(int i=0; i<=127; i++) {
			Oled_data(0x00);
		}
	}

}

////////////////////////////////////////
///////// Skrive til Oleden ////////////
////////////////////////////////////////

void Oled_print(char* Tekst){
	int i = 0;
	while (Tekst[i] != '\0'){
		Oled_print_symbol(Tekst[i++]);
		
	}
}

////////////////////////////////////////
///////////// ASCII kode ///////////////
////////////////////////////////////////

void Oled_print_symbol(char Symbol){
	
	char Bokstav[8];

	Ascii_to_char(Bokstav, Symbol);
	
	for(int i=0; i<=7; i++){
		
		Oled_data(Bokstav[i]);

	}
}

