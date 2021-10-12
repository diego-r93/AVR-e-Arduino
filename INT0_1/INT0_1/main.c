/*
 * INT0_1.c
 *
 * Created: 23/08/2020 02:51:07
 * Author : Diego
 */ 

//====================================================================================================================//
//				 HABILITANDO AS INTERRUP��ES INT0 E INT1 POR TRANSI��O E N�VEL, RESPECTIVAMENTE
//====================================================================================================================//

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define set_bit(Y, bit_x) (Y|=(1<<bit_x))
#define clr_bit(Y, bit_x) (Y&=~(1<<bit_x))
#define tst_bit(Y, bit_x) (Y&(1<<bit_x))
#define cpl_bit(Y, bit_x) (Y^=(1<<bit_x))

#define LED PB5

ISR(INT0_vect);
ISR(INT1_vect);

//--------------------------------------------------------------------------------------------------------------------//

int main(void)
{
	DDRD = 0x00;          // PORTD entrada
	PORTD = 0xFF;         // Pull-ups habilitados
	DDRB = 0b00100000;    // Somente pino do LED como sa�da
	PORTB = 0b11011111;   // Desliga o LED e habilita pull-ups
	
	UCSR0B = 0x00;
	
	EICRA = 1<<ISC01;				 // Interrup��es externas: INT0 na borda de descida, INT1 no n�vel zero
	EIMSK = (1<<INT1) | (1<<INT0);   // Habilita as duas interrup��es
	sei();							 // Habilita interrup��es globais, ativando o bit I do SREG
	
	while (1);    
}
//--------------------------------------------------------------------------------------------------------------------//

ISR(INT0_vect)
{
	cpl_bit(PORTB, LED);
}
//--------------------------------------------------------------------------------------------------------------------//

ISR(INT1_vect)
{
	cpl_bit(PORTB, LED);
	_delay_ms(200);
}
//====================================================================================================================//

