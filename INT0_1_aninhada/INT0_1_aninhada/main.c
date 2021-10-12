/*
 * INT0_1_aninhada.c
 *
 * Created: 24/08/2020 03:37:23
 * Author : diego
 */ 

//====================================================================================================================//
//										INTERRUPÇÃO INT1 INTERROMPENDO A INT0
//====================================================================================================================//

#include "def_principais.h"

ISR(INT0_vect);
ISR(INT1_vect);

//--------------------------------------------------------------------------------------------------------------------//

int main(void)
{
	DDRD = 0b11000000;
	PORTD = 0xFF;
	
	UCSR0B = 0x00;
	
	EICRA = 0x00;                      // Interrupções externas INT0 e INT1 no nível zero.
	EIMSK = (1<<INT1) | (1<<INT0);     // Habilita as duas interrupções
	
	while (1)                    // Pisca o LED numa velocidade muito grande (visualmente fica ligado)
		cpl_bit(PORTD, LED2);
}
//--------------------------------------------------------------------------------------------------------------------//

ISR(INT0_vect)   // Interrupção externa 0, quando o botão é pressionado o LED pisca
{
	unsigned char sreg;
	
	sreg = SREG;            // Salva SREG porque a interrupção pode alterar o seu valor
	
	clr_bit(EIMSK, INT0);   // Desabilita INT0 para que ele não chame a si mesmo
	sei();                  // Habilita interrupção geral, agora INT1 pode interromper INT0
	
	cpl_bit(PORTD, LED1);   // Pisca led a cada 300 ms
	_delay_ms(300);
	
	set_bit(EIMSK, INT0);   // Habilita novamente a interrupção INT0
	
	SREG = sreg;            // Restaura o valor de SREG que pode ter sido alterado
}
//--------------------------------------------------------------------------------------------------------------------//

ISR(INT1_vect)   // Interrupção externa 1, mantendo o botão pressionado o LED pisca
{
	cpl_bit(PORTD, LED1);    // Pisca o LED a cada 200ms
	_delay_ms(200);
}

