/*
* CFile1.c
*
* Created: 29.09.2016 16:14:34
*  Author: espebek
*/

#include "Menu.h"
#include "Joy.h"
#include "Gameplay.h"

////////////////////////////////////////
/////// Spillets startsekvens //////////
////////////////////////////////////////

void  Menu_start(void){
	Oled_position(0,15);
	Oled_print("BOOTING GAME");
	Oled_position(1,26);
	Oled_print("PING-PONG");
	
	Oled_position(7,0);
	Oled_print("----------------");
	
	Oled_position(5,3);
	Oled_print("|");
	Oled_position(6,3);
	Oled_print("|");
	Oled_position(4,3);
	Oled_print("--");
	Oled_position(5,9);
	Oled_print("|");
	Oled_position(6,9);
	Oled_print("|");
	Oled_position(5,6);
	Oled_print("|");
	Oled_position(4,6);
	Oled_print("|");
	Oled_position(3,7);
	Oled_print("o");
	
	////////////////////
	
	Oled_position(5,110);
	Oled_print("|");
	Oled_position(6,110);
	Oled_print("|");
	Oled_position(4,110);
	Oled_print("--");
	Oled_position(5,116);
	Oled_print("|");
	Oled_position(6,116);
	Oled_print("|");
	Oled_position(5,113);
	Oled_print("|");
	Oled_position(4,113);
	Oled_print("|");
	Oled_position(3,114);
	Oled_print("o");
	
	
	_delay_ms(500);
	
	for(int i = 0; i <= 5; i++){
		
		for (int i = 20; i <= 94; i++){
			Oled_position(4,6+i);
			Oled_print("o");
			Oled_position(4,6+(i-8));
			Oled_print(" ");
			_delay_ms(10);
		}
		
		for (int i = 20; i <= 94; i++){
			Oled_position(4,120-i);
			Oled_print("o");
			Oled_position(4,120-(i+8));
			Oled_print(" ");
			_delay_ms(10);
		}
	}
	Oled_clear();
}

////////////////////////////////////////
//////////////  MENY  //////////////////
////////////////////////////////////////

void Meny (void){
	Oled_position(0,40);
	Oled_print("<MENU>");
	Oled_position(2,15);
	Oled_print("Start Game");
	Oled_position(3,15);
	Oled_print("High Score");
	Oled_position(4,15);
	Oled_print("Options");

}

////////////////////////////////////////
//////// MENY Pil retning ned  /////////
////////////////////////////////////////

uint8_t Menupointer_Down(void){
	if(adcReturnVal_y <= -50){
		
		Oled_position(menu_arrow,0);
		Oled_print(" ");

		menu_arrow = menu_arrow +1;
		
		if(menu_arrow == 6){
			menu_arrow = 2;
		}
		
		Oled_position(menu_arrow,0);
		Oled_print(">");
		
	}
	return menu_arrow;
}

////////////////////////////////////////
//////// MENY Pil retning opp  /////////
////////////////////////////////////////

uint8_t Menupointer_Up(void){
	if(adcReturnVal_y >= 50){
		Oled_position(menu_arrow,0);
		Oled_print(" ");

		menu_arrow = menu_arrow -1;

		if(menu_arrow == 1){
			menu_arrow = 5;
		}
		
		Oled_position(menu_arrow,0);
		Oled_print(">");
	}
	return menu_arrow;
}

////////////////////////////////////////
//////////// Selve Menyen  /////////////
////////////////////////////////////////

void Menusystem(void){
	//Start Meny
	if (Joy_button == 1 && Main_menu_option_sub == 1){
		Main_menu_option = menu_arrow -1;
		switch(Main_menu_option){
			
			case 1:
			Oled_clear();
			StartGame();
			Main_menu_option_sub = 2;
			break;

			case 2:
			Oled_clear();
			HighScore();
			Main_menu_option_sub = 3;
			break;
			/*
			case 3:
			Oled_clear();
			Options();
			Main_menu_option_sub = 4;
			break;*/
		}
		
	}
	

	if((Joy_button == 1) && (Main_menu_option_sub == 2 || 3 || 4) && (menu_arrow == 5)){
		Oled_clear();
		Meny();
		Main_menu_option_sub = 1;
	}
	
}


////////////////////////////////////////
//////////// Menyen Game on  ///////////
////////////////////////////////////////

void StartGame(void){
	Oled_position(0,35);
	Oled_print("GAME-ON");
	Oled_position(2,5);
	Oled_print("|-----------|");
	Oled_position(3,15);
	Oled_print("Score:");
	Oled_position(4,5);
	Oled_print("|-----------|");
	//Oled_position(5,15);
	//Oled_print("Back");
}

////////////////////////////////////////
////////// Highscore meny  /////////////
////////////////////////////////////////

void HighScore(void){
	Oled_position(0,30);
	Oled_print("HIGHSCORE");
	Oled_position(2,5);
	Oled_print("|-----------|");
	Oled_position(3,20);
	Oled_print("Score:");
	Oled_position(4,5);
	Oled_print("|-----------|");
	Oled_position(5,20);
	Oled_print("Back");

}

////////////////////////////////////////
/////////// Options meny  //////////////
////////////////////////////////////////

void Options(void){
	Oled_position(0,35);
	Oled_print("OPTIONS");
	Oled_position(2,15);
	Oled_print("Difficulty");
	Oled_position(3,15);
	Oled_print("Sound");
	Oled_position(5,15);
	Oled_print("Back");
}

////////////////////////////////////////
////////// Game over meny //////////////
////////////////////////////////////////

void Oled_Game_over(void){
	Oled_clear();
	Oled_position(1,15);
	Oled_print("GAME OVER");
	Oled_position(3,15);
	Oled_print("SCORE:");
}


