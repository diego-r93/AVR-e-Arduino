/*
 * Blink.c
 *
 * Created: 23/08/2020 20:29:27
 * Author : Diego
 */ 

//====================================================================================================================//

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define set_bit(Y, bit_x) (Y|=(1<<bit_x))

#define clr_bit(Y, bit_x) (Y&=~(1<<bit_x))

#define tst_bit(Y, bit_x) (Y&(1<<bit_x))

#define cpl_bit(Y, bit_x) (Y^=(1<<bit_x))

#define LED PB5


//--------------------------------------------------------------------------------------------------------------------//

int main(void)
{
	DDRB = 0xFF;
	
    while (1) 
    {
		set_bit(PORTB, LED);
		_delay_ms(500);
		clr_bit(PORTB, LED);
		_delay_ms(500);
    }
}
//====================================================================================================================//
