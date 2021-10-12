/*
 * Teclado_Matricial.c
 *
 * Created: 06/07/2021 09:33:14
 * Author : diego
 */ 

//====================================================================================================================//
//												LEITURA DE UM TECLADO 4 X 4
//====================================================================================================================//

#include <avr/io.h>
#include "def_principais.h"
#include "LCD.h"
#include "teclado.h"

// Defini��o para acessar a mem�ria flash como ponteiro
PROGMEM const char mensagem1[] = "Teclado 4 x 4\0";	//mensagem armazenada na mem�ria flash
PROGMEM const char mensagem2[] = "tecla =\0";		//mensagem armazenada na mem�ria flash

int main(void)
{
    unsigned char nr;
	
	DDRB = 0xFF;	// LCD no PORTB
	DDRD = 0x0F;	// Defini��es das entradas e sa�das para o teclado
	PORTD = 0xFF;	// Habilita os pull-ups do PORTD e coloca colunas em 1
	UCSR0B = 0x00;	// Para o uso dos PORTD no Arduino
	
	inic_LCD_4bits();
	escreve_LCD_Flash(mensagem1);
	cmd_LCD(0xC7, 0);	// Desloca o cursor para a segunda linha do LCD
	escreve_LCD_Flash(mensagem2);
	
    while (1) 
    {
		nr = ler_teclado();
		
		if (nr != 0xFF)	// Se alguma tecla foi pressionada, mostra seu valor
		{
			cmd_LCD(0xCF, 0);	// Desloca o cursor para a �ltima posi��o da segunda linha
			cmd_LCD(nr, 1);     // nr j� est� em formato ASCII
		}
    }
}
//====================================================================================================================//