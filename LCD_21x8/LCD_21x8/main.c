/*
 * LCD_21x8.c
 *
 * Created: 08/07/2021 20:42:28
 * Author : diego
 */ 

#include "def_principais.h"
#include "LCDG.h"

//teste da escrita com os caracteres ASCII
PROGMEM const char ascii0[] = " !\"#$%&'()*+,-./01234\0";
PROGMEM const char ascii1[] = "56789:;<=>?@ABCDEFGHI\0";
PROGMEM const char ascii2[] = "JKLMNOPQRSTUVWXYZ[\\]^\0";
PROGMEM const char ascii3[] = "_`abcdefghijklmnopqrs\0";
PROGMEM const char ascii4[] = "tuvwxyz{|}~\0";

int main(void)
{
	DDRD  = 0xFF;	//pinos do PORTD como saída
	DDRC  = 0xFF;	//pinos do PORTC como saída
	UCSR0B= 0x00;	//para uso dos pinos do PORTD no Arduino

	inic_LCDG();
	
	escreve_stringFLASH_LCDG(ascii0,0,0);
	escreve_stringFLASH_LCDG(ascii1,0,1);
	escreve_stringFLASH_LCDG(ascii2,0,2);
	escreve_stringFLASH_LCDG(ascii3,0,3);
	escreve_stringFLASH_LCDG(ascii4,0,4);
	escreve_stringRAM_LCDG("LCD 128x64 COMO UM",10,6);
	escreve_stringRAM_LCDG("ALFANUMERICO 21x8",13,7);
	
	while(1){}		//código principal
	
}

