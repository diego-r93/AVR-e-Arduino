/*
 * Sonar.c
 *
 * Created: 07/07/2021 06:03:33
 * Author : diego
 */ 

//====================================================================================================================//
//										PROGRAMA PARA TESTE DO M�DULO SONAR HC-SR04
//====================================================================================================================//

#include "def_principais.h"
#include "LCD.h"

#define DISPARO	PB1

unsigned int Inicio_Sinal, Distancia;
PROGMEM const char mensagem1[] = "Distanc =     cm\0";
PROGMEM const char mensagem2[] = "xxx\0";

//--------------------------------------------------------------------------------------------------------------------//
ISR(TIMER1_CAPT_vect)	// Interrup��o por captura do valor do TCNT1
{
	cpl_bit(TCCR1B, ICES1);	// Troca a borda de captura do sinal
	
	if (!tst_bit(TCCR1B, ICES1))	// L� o valor de contagem do TC1 na borda de subida do sinal
		Inicio_Sinal = ICR1;	// Salva a primeira contagem para determinar a largura do pulso
	else
		Distancia = (ICR1 - Inicio_Sinal)/58/2;	/* Agora ICR1 tem o valor do TC1 na borda de descida do sinal,
												   ent�o calcula a dist�ncia */
}

//--------------------------------------------------------------------------------------------------------------------//
int main(void)
{
    unsigned char digitos[tam_vetor];	// Declara��o da vari�vel para armazenagem dos d�gitos
	DDRD = 0xFF;
	DDRB = 0b00000010;	// Somente o pino de disparo como sa�da (PB1), captura no PB0 (ICP1)
	PORTB = 0b11111101;
	
	TCCR1B = (1<<ICES1) | (1<<CS11);	// TC1 com prescaler = 8, captura na borda de subida
	TIMSK1 = 1<<ICIE1;	// Habilita a interrup��o por captura
	sei();
	
	inic_LCD_4bits();
	escreve_LCD_Flash(mensagem1);
	
    while (1) 
    {
		// Pulso de disparo
		set_bit(PORTB, DISPARO);
		_delay_us(10);
		clr_bit(PORTB, DISPARO);
		
		cmd_LCD(0x8A, 0);
		if (Distancia < 431)	// Se o pulso for menor que 25 ms, mostra o valor da dist�ncia
		{
			ident_num(Distancia, digitos);
			cmd_LCD(digitos[2], 1);
			cmd_LCD(digitos[1], 1);
			cmd_LCD(digitos[0], 1);
			
		}
		else
			escreve_LCD_Flash(mensagem2);
		
		_delay_ms(50);	// M�nimo tempo para uma nova medida de dist�ncia	
    }
}
//====================================================================================================================//
