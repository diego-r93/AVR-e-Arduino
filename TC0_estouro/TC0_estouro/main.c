/*
 * TC0_estouro.c
 *
 * Created: 06/07/2021 15:57:04
 * Author : diego
 */ 

//====================================================================================================================//
//										HABILITANDO A INTERRUPÇÃO POR ESTOURO DO TC0
//====================================================================================================================//

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

#define cpl_bit(Y, bit_x) (Y^=(1<<bit_x))
#define LED	PB5

//--------------------------------------------------------------------------------------------------------------------//
ISR(TIMER0_OVF_vect)	// Interrupção do TC0
{
	cpl_bit(PORTB, LED);
}
//--------------------------------------------------------------------------------------------------------------------//
int main(void)
{
	DDRB = 0b00100000;	// Somente o pino do LED como saída
	PORTB = 0b11011111;	// Apaga  LED e habilita pull-ups nos pinos não utilizados
	
	TCCR0B = (1<<CS02) | (1<<CS00);	// TC0 com prescaler de 1024, a 16 MHz gera uma interrupção a cada 16,384 ms
	
	TIMSK0 = 1<<TOIE0;	// Habilita a interrupção do TC0
	sei();
	 
    while (1) 
    {
    }
}
//====================================================================================================================//

