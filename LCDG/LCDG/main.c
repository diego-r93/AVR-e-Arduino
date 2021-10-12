/*
 * LCDG.c
 *
 * Created: 08/07/2021 20:16:06
 * Author : diego
 */ 

#include "def_principais.h"
#include "LCDG.h"
#include "dragao.h"		//figura com 1024 bytes


int main(void)
{
	DDRD  = 0xFF;	//pinos do PORTD como sa�da
	DDRC  = 0xFF;	//pinos do PORTC como sa�da
	UCSR0B= 0x00;	//para uso dos pinos do PORTD no Arduino

	inic_LCDG();
	
	escreve_todo_LCDG(dragao);
	
	while(1){}		//c�digo principal
}

