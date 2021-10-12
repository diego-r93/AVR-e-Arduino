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

// Definição para acessar a memória flash como ponteiro
PROGMEM const char mensagem1[] = "Teclado 4 x 4\0";	//mensagem armazenada na memória flash
PROGMEM const char mensagem2[] = "tecla =\0";		//mensagem armazenada na memória flash

int main(void)
{
    unsigned char nr;
	
	DDRB = 0xFF;	// LCD no PORTB
	DDRD = 0x0F;	// Definições das entradas e saídas para o teclado
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
			cmd_LCD(0xCF, 0);	// Desloca o cursor para a última posição da segunda linha
			cmd_LCD(nr, 1);     // nr já está em formato ASCII
		}
    }
}
//====================================================================================================================//