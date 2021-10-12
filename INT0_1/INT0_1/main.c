/*
 * INT0_1.c
 *
 * Created: 23/08/2020 02:51:07
 * Author : Diego
 */ 

//====================================================================================================================//
//				 HABILITANDO AS INTERRUPÇÕES INT0 E INT1 POR TRANSIÇÃO E NÍVEL, RESPECTIVAMENTE
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
	DDRB = 0b00100000;    // Somente pino do LED como saída
	PORTB = 0b11011111;   // Desliga o LED e habilita pull-ups
	
	UCSR0B = 0x00;
	
	EICRA = 1<<ISC01;				 // Interrupções externas: INT0 na borda de descida, INT1 no nível zero
	EIMSK = (1<<INT1) | (1<<INT0);   // Habilita as duas interrupções
	sei();							 // Habilita interrupções globais, ativando o bit I do SREG
	
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

