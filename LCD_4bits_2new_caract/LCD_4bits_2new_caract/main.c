/*
 * LCD_4bits_2new_caract.c
 *
 * Created: 22/08/2020 20:34:59
 * Author : Diego
 */ 

//====================================================================================================================//
//										CRIANDO CARACTERES PARA O LCD 16x2
//
//											Interface de dados de 4 bits
//====================================================================================================================//

#include "def_principais.h"
#include "LCD.h"

const unsigned char carac1[] PROGMEM = {0b01110,
										0b10001,
										0b10000,
										0b10000,     // Ç
										0b10101,
										0b01110,
										0b10000};

const unsigned char carac2[] PROGMEM = {0b00100,
										0b00100,
										0b01010,
										0b01010,    // Delta
										0b10001,
										0b11111,
										0b00000};

//--------------------------------------------------------------------------------------------------------------------//

int main(void)
{
	unsigned char k;
	
	DDRD = 0xFF;
	DDRB = 0xFF;
	
	inic_LCD_4bits();
	
	cmd_LCD(0x40, 0);                               // Endereço base para gravar novo segmento
	for (k = 0; k < 7; k++)                         // Grava 8 bytes na DDRAM começando no end. 0x40
		cmd_LCD(pgm_read_byte(&carac1[k]), 1);
	cmd_LCD(0x00, 1);                               // Apaga útila posição da CGRAm para evitar algum dado espúrio
	
	cmd_LCD(0x48, 0);                               // Endereço base para gravar novo segmento
	for (k = 0; k < 7; k++)                         // Grava 8 bytes na DDRAM começando no end. 0x48
		cmd_LCD(pgm_read_byte(&carac2[k]), 1);
	cmd_LCD(0x00, 1);                               // Apaga útila posição da CGRAm para evitar algum dado espúrio
	
	cmd_LCD(0x80, 0);    // Cursor na primeira posição a esquerda - 1ª linha
	cmd_LCD(0x00, 1);    // Apresenta primeiro caractere 0x00
	cmd_LCD(0x01, 1);    // Apresenta segundo caractere 0x01
	
    while (1);
    return 0;
}
//====================================================================================================================//
