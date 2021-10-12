/*
 * LCD_4bits_big_number.c
 *
 * Created: 22/08/2020 21:25:45
 * Author : diego
 */ 

//====================================================================================================================//
//       									CRIANDO BIG NUMBERS PARA O LCD 16x2
//====================================================================================================================//

#include "def_principais.h"
#include "LCD.h"

const unsigned char novos_caract[] PROGMEM={0b00000001,    // 0
											0b00000001,
											0b00000001,
											0b00000001,
											0b00000001,
											0b00000001,
											0b00011111,
											0b00011111,    // 1
											0b00010000,
											0b00010000,
											0b00010000,
											0b00010000,
											0b00010000,
											0b00010000,
											0b00011111,    // 2
											0b00000001,
											0b00000001,
											0b00000001,
											0b00000001,
											0b00000001,
											0b00000001,
											0b00000001,    // 3
											0b00000001,
											0b00000001,
											0b00000001,
											0b00000001,
											0b00000001,
											0b00000001,
											0b00011111,    // 4
											0b00000000,
											0b00000000,
											0b00000000,
											0b00000000,
											0b00000000,
											0b00011111,
											0b00011111,    // 5
											0b00000001,
											0b00000001,
											0b00000001,
											0b00000001,
											0b00000001,
											0b00011111,
											0b00011111,    // 6
											0b00000000,
											0b00000000,
											0b00000000,
											0b00000000,
											0b00000000,
											0b00000000,
											0b00011111,   // 7
											0b00010000,
											0b00010000,
											0b00010000,
											0b00010000,
											0b00010000,
											0b00011111};

const unsigned char nr_grande[10][4] PROGMEM= {	{0x01, 0x02, 0x4C, 0x00},   // nr. 0
												{0x20, 0x7C, 0x20, 0x7C},   // nr. 1
												{0x04, 0x05, 0x4C, 0x5F},   // nr. 2
												{0x06, 0x05, 0x5F, 0x00},   // nr. 3
												{0x4C, 0x00, 0x20, 0x03},   // nr. 4
												{0x07, 0x04, 0x5F, 0x00},   // nr. 5
												{0x07, 0x04, 0x4C, 0x00},   // nr. 6
												{0x06, 0x02, 0x20, 0x03},   // nr. 7
												{0x07, 0x05, 0x4C, 0x00},   // nr. 8
												{0x07, 0x05, 0x20, 0x03}};  // nr. 9
													
//--------------------------------------------------------------------------------------------------------------------//
											
void cria_novos_caract()
{
	unsigned char i, k, j = 0, n = 0x40;
	
	for(i = 0; i < 8; i++)
	{
		cmd_LCD(n, 0);		// Endereco base para gravar novo segmento
		for(k = 0; k < 7; k++)
			cmd_LCD(pgm_read_byte(&novos_caract[k + j]), 1);
		
		cmd_LCD(0x00, 1);	// Apaga ultima posição do end. da CGRAM para evitar algum dado espúrio
		j += 7;
		n += 8;
	}
}

//--------------------------------------------------------------------------------------------------------------------//

void escreve_BIG(unsigned char end, unsigned char nr)
{
	cmd_LCD(end, 0);								   // Endereco de incio de escrita (1a linha)
	cmd_LCD(pgm_read_byte(&nr_grande[nr][0]), 1);
	cmd_LCD(pgm_read_byte(&nr_grande[nr][1]), 1);
	cmd_LCD(end +64 , 0);							   // Desloca para a 2a linha
	cmd_LCD(pgm_read_byte(&nr_grande[nr][2]), 1);
	cmd_LCD(pgm_read_byte(&nr_grande[nr][3]), 1);
}

//--------------------------------------------------------------------------------------------------------------------//

int main()
{
	DDRD = 0xFF;					// PORTD como saída
	DDRB = 0xFF;					// PORTB como saída

	inic_LCD_4bits();
	cria_novos_caract();
		
	escreve_BIG(0x80, 0);
	escreve_BIG(0x82, 1);
	escreve_BIG(0x85, 2);           // Escreve os números 0, 1, 2, 3, 4 e 5
	escreve_BIG(0x88, 3);
	escreve_BIG(0x8B, 4);
	escreve_BIG(0x8E, 5);
	
	for(;;);
}
//--------------------------------------------------------------------------------------------------------------------//
