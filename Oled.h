/*
* CFile1.c
*
* Created: 22.09.2016 16:18:39
*  Author: dagfinae
*/


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void Oled_cmd(uint8_t cmd);
void Oled_data(uint8_t data);
void Oled_start(void);
void Oled_page(uint8_t kolonne);
void Oled_line(uint8_t linje);
void Oled_position(uint8_t linje, uint8_t rad);
void Oled_clear(void);
void Oled_print_symbol(char Symbol);
void Oled_print(char* Tekst);

