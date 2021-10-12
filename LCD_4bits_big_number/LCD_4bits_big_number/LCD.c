/*
 * LCD.c
 *
 * Created: 21/08/2020 20:15:23
 *  Author: Diego
 */ 

//====================================================================================================================//
//							Sub-rotinas para o trabalho com um LCD 16x2 com via de dados de 4 bits
//										Controlador HD44780 - Pino R/W aterrado
//							A via de dados do LCD deve ser ligado aos 4 bits mais significativos ou
//							aos 4 bits menos significativos do PORT do uC
//====================================================================================================================//

#include "LCD.h"

//--------------------------------------------------------------------------------------------------------------------//
//				Sub-rotina para enviar caracteres e comandos ao LCD com via de dados de 4 bits
//--------------------------------------------------------------------------------------------------------------------//

void cmd_LCD(unsigned char c, char cd) // c é o dado e cd indica se é instrução ou caractere
{
	if (cd == 0)                   // Instrução
		clr_bit(CONTR_LCD, RS);
	else                           // Caractere
		set_bit(CONTR_LCD, RS);
	
	// Primeiro nibble de dados - 4 MSB
	#if (nibble_dados)				// Compila o código para os pinos de dados do LCD nos 4 MSB do PORT
		DADOS_LCD = (DADOS_LCD & 0x0F) | (0xF0 & c);
	#else							// Compila o código para os pinos de dados do LCD nos 4 LSB do PORT
		DADOS_LCD = (DADOS_LCD & 0xF0) | (c>>4);
	#endif
	
	pulso_enable();
	
	
	// Segundo nibble de dados - 4 LSB
	#if (nibble_dados)				// Compila o código para os pinos de dados do LCD nos 4 MSB do PORT
	DADOS_LCD = (DADOS_LCD & 0x0F) | (0xF0 & (c<<4));
	#else							 // Compila o código para os pinos de dados do LCD nos 4 LSB do PORT
	DADOS_LCD = (DADOS_LCD & 0xF0) | (0x0F & c);
	#endif
	
	pulso_enable();
	
	if ((cd == 0) && (c < 4))   // Se for instrução de limpeza ou retorno de cursor, espera o tempo necessário
		_delay_ms(2);
}

//--------------------------------------------------------------------------------------------------------------------//
//						Sub-rotina para inicialização do LCD com via de dados de 4 bits
//--------------------------------------------------------------------------------------------------------------------//

void inic_LCD_4bits()
{
	clr_bit(CONTR_LCD, RS);
	clr_bit(CONTR_LCD, E);
	
	_delay_ms(20);
	
	// Interface de 8 bits
	#if (nibble_dados)
		DADOS_LCD = (DADOS_LCD & 0x0F) | 0x30;
	#else
		DADOS_LCD = (DADOS_LCD & 0xF0) | 0x03;
	#endif
	
	pulso_enable();
	_delay_ms(5);
	pulso_enable();
	_delay_us(200);
	pulso_enable();   // Até aqui ainda é uma interface de 8 bits.
	
	// Interface de 4 bits, deve se enviado duas vezes (a outra ésta abaixo)
	#if (nibble_dados)
	DADOS_LCD = (DADOS_LCD & 0x0F) | 0x20;
	#else
	DADOS_LCD = (DADOS_LCD & 0xF0) | 0x02;
	#endif
	pulso_enable();
	
	cmd_LCD(0x28, 0);   // Interface de 4 bits 2 linhas (aqui se habilita as 2 linhas)
						// São enviados os 2 nibbles (0x2 e 0x8)
	cmd_LCD(0x08, 0);   // Desliga o LCD
	cmd_LCD(0x01, 0);   // Limpa todo o display
	cmd_LCD(0x0C, 0);   // Mensagem aparente cursor inativo não piscando
	cmd_LCD(0x80, 0);   // Escreve na primeira posição a esquerda - 1ª linha
}

//--------------------------------------------------------------------------------------------------------------------//
//								Sub-rotina de escrita no LCD - Dados armazenados na RAM
//--------------------------------------------------------------------------------------------------------------------//

void escreve_LCD(char *c)
{	
	for (; *c != 0; c++)
		cmd_LCD(*c, 1);
}

//--------------------------------------------------------------------------------------------------------------------//
//								Sub-rotina de escrita no LCD - Dados armazenados na FLASH
//--------------------------------------------------------------------------------------------------------------------//

void escreve_LCD_Flash(const char *c)
{
	for (; pgm_read_byte(&(*c)) != 0; c++)
		cmd_LCD(pgm_read_byte(&(*c)), 1);
}

//--------------------------------------------------------------------------------------------------------------------//
//					Conversão de um número e seus gigitos individuais - função auxiliar
//--------------------------------------------------------------------------------------------------------------------//

void ident_num(unsigned int valor, unsigned char *disp)
{
	unsigned char n;
	
	for (n = 0; n < tam_vetor; n++)
		disp[n] = 0 + conv_ascii;             // Limpa vetor para armazenagem dos digitos
		
	do 
	{
		*disp = (valor % 10) + conv_ascii;    // Pega o resto da divisão por 10
		valor /= 10;
		disp++;
	} while (valor != 0);
}
