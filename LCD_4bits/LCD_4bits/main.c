/*
 * LCD_4bits.c
 *
 * Created: 21/08/2020 19:31:33
 * Author : Diego
 */ 

//====================================================================================================================//
//									ACIONANDO UM DISPLAY DE CRISTAL LIQUIDO DE 16x2
//
//											Interface de dados de 4 bits
//====================================================================================================================//


#include "def_principais.h"
#include "LCD.h"

// Definição para acessar a memória flash
PROGMEM const char mensagem[] = " DADOS DE 4BITS!\0";   // Mensagem armazenada na memória flash

//--------------------------------------------------------------------------------------------------------------------//

int main(void)
{
	DDRD = 0xFF;
	DDRB = 0xFF;   
	
	inic_LCD_4bits();
	escreve_LCD(" INTERFACE DE");   // String armazenada na RAM
	cmd_LCD(0xC0, 0);               // Desloca cursor para segunda linha
	escreve_LCD_Flash(mensagem);    // String armazenada na memória flash
	
    for(;;);
	return 0;
}

