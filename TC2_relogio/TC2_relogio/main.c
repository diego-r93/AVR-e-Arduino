/*
 * TC2_relogio.c
 *
 * Created: 06/07/2021 16:37:40
 * Author : diego
 */ 

//====================================================================================================================//
//										TC2 COM CRISTAL EXTERO DE 32,768 kHz
//								Rotina para implementar um relógio e piscar um LED
//====================================================================================================================//

#define F_CPU	1000000UL	// Frequência de 1 MHz

#include <avr/io.h>
#include <avr/interrupt.h>

#define cpl_bit(Y, bit_x) (Y^=(1<<bit_x))
#define LED	PB5

volatile unsigned char segundos, minutos, horas;

//--------------------------------------------------------------------------------------------------------------------//
ISR(TIMER2_OVF_vect)	// Entra aqui a cada 1 segundo
{
	cpl_bit(PORTB, LED);	// Pisca o LED
	
	segundos++;
	if (segundos == 60)
	{
		segundos = 0;
		minutos++;
		if (minutos == 60)
		{
			minutos = 0;
			horas++;
			if (horas == 24)
			{
				horas = 0;
			}
		}
	}	
}

//--------------------------------------------------------------------------------------------------------------------//
int main(void)
{
    DDRB = 0b00100000;	// Cristal ext., não importa a config. dos pinos TOSC1 e TOSC2
	PORTB = 0b11011111;	// Pull-ups habilitados nos pinos não utilizados
	
	ASSR = 1<<AS2;	// Habilita o cristal externo para o contador de tempo real
	TCCR2B = (1<<CS22) | (1<<CS20);	/* Prescaler = 128, freq. para o contador = 32.768/128,
									   o que resulta em uma frequência de 256 Hz. Como o
									   contador é de 8 bits, ele conta 256 vezes, resultando em um
									   estouro preciso a cada 1 segundo
									*/
	TIMSK2 = 1<<TOIE2;	// Habilita a interrupção do TC2
	
	sei();	// Habilita a interrupção global
    while (1) 
    {
    }
}
//====================================================================================================================//
