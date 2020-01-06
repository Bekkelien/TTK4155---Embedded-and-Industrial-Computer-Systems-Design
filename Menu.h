/*
* CFile1.c
*
* Created: 29.09.2016 16:15:00
*  Author: espebek
*/

#include <stdio.h>

#include "Joy.h"
#include "Oled.h"


uint8_t menu_arrow;
uint8_t Main_menu_option;
uint8_t Main_menu_option_sub;

void Meny (void);
uint8_t Menupointer_Down(void);
uint8_t Menupointer_Up(void);
void Menusystem(void);
void StartGame(void);
void HighScore(void);
void Options(void);
void Menu_start(void);
void Oled_Game_over(void);
