/*
 * LCD_4bits_ident_num.c
 *
 * Created: 23/08/2020 00:26:56
 * Author : Diego
 */ 

//====================================================================================================================//
//									ACIONANDO UM DISPLAY DE CRISTAL LIQUIDO DE 16x2
//
//											Uso da função ident_num(...)
//====================================================================================================================//


#include "def_principais.h"
#include "LCD.h"

//--------------------------------------------------------------------------------------------------------------------//

int main(void)
{
    unsigned char digitos[tam_vetor];    // Declaração da variável para armazenagem dos dígitos
    unsigned char cont;
	DDRD = 0xFF;
    DDRB = 0xFF;
   
    inic_LCD_4bits();
   
    while (1) 
    {
		for (cont = 0; cont < 101; cont++)
		{
			ident_num(cont, digitos);
			cmd_LCD(0x8D, 0);
			cmd_LCD(digitos[2], 1);
			cmd_LCD(digitos[1], 1);
			cmd_LCD(digitos[0], 1);
			_delay_ms(200);
		}
    }
}

