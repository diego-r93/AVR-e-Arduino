/*
* LCD_8bits.c
*
* Created: 19/08/2020 17:31:32
* Author : Diego
*/

//====================================================================================================================//
//									ACIONANDO UM DISPLAY DE CRISTAL LIQUIDO DE 16x2
//
//											Interface de dados de 8 bits
//====================================================================================================================//

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define set_bit(Y, bit_x) (Y|=(1<<bit_x))
#define clr_bit(Y, bit_x) (Y&=~(1<<bit_x))
#define tst_bit(Y, bit_x) (Y&(1<<bit_x))
#define cpl_bit(Y, bit_x) (Y^=(1<<bit_x))

#define pulso_enable() _delay_us(1); set_bit(CONTR_LCD, E); _delay_us(1); clr_bit(CONTR_LCD, E); _delay_us(45)

#define DADOS_LCD  PORTD   // 8 bits de dados do LCD
#define CONTR_LCD  PORTB   // Pinos de controle
#define RS         PB1     // Pino de instrução ou dados
#define E          PB0     // Pino de enable do LCD

const unsigned char msg1[] PROGMEM = "ABCDEFGHIJKLMNOP";

//--------------------------------------------------------------------------------------------------------------------//
//								Sub-rotina para enviar caracteres e comandos ao LCD
//--------------------------------------------------------------------------------------------------------------------//

void cmd_LCD(unsigned char c, char cd) // c é o dado e cd indica se é instrução ou caractere
{
	DADOS_LCD = c;
	
	if (cd == 0)
		clr_bit(CONTR_LCD, RS);   // RS = 0
	else
		set_bit(CONTR_LCD, RS);   // RS = 1
		
	pulso_enable();
	
	if ((cd == 0) && (c < 4))   // Se for instrução de limpeza ou retorno de cursor, espera o tempo necessário
		_delay_ms(2);
}

//--------------------------------------------------------------------------------------------------------------------//
//											Sub-rotina de inicialização do LCD
//--------------------------------------------------------------------------------------------------------------------//

void inic_LCD_8bits()
{
	
	clr_bit(CONTR_LCD, RS);   // RS = 0
	
	_delay_ms(15);	
						// Fixa modo de utilização do LCD
	DADOS_LCD = 0x38;   // Interface 8 bits, 2 linhas, matriz 5x7 pontos
	
	pulso_enable();
	_delay_ms(5);
	pulso_enable();
	_delay_us(200);
	pulso_enable();
	pulso_enable();
	
	cmd_LCD(0x08, 0);   // Desliga o LCD
	cmd_LCD(0x01, 0);   // Limpa todo o display
	cmd_LCD(0x0C, 0);   // Mensagem aparente cursor inativo não piscando
	cmd_LCD(0x80, 0);   // Escreve na primeira posição a esquerda - 1ª linha
}

//--------------------------------------------------------------------------------------------------------------------//
//												Sub-rotina de escrita no LCD
//--------------------------------------------------------------------------------------------------------------------//

void escreve_LCD(char *c)
{
	
	for (; *c != 0; c++)
		cmd_LCD(*c, 1);
}

//--------------------------------------------------------------------------------------------------------------------//

int main(void)
{
	unsigned char i;
	
	DDRB = 0xFF;     // PORTB como saída
	DDRD = 0xFF;     // PORTD como saída
	UCSR0B = 0x00;   // Habilita os pinos PD0 e PD1 como I/O genéricos
	
	inic_LCD_8bits();
	
	for (i = 0; i < 16; i++)
		cmd_LCD(pgm_read_byte(&msg1[i]), 1);   // Lê na memória flash e usa cmd_LCD
		
	cmd_LCD(0xC0, 0);                  // Desloca o cursor para a segunda linha do LCD
	escreve_LCD("QRSTUVXYZ 123456");   // A cadeia de caracteres é criada na RAM
	
	for(;;);
}
//====================================================================================================================//
