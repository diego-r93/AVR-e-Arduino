/*
 * TC0_PWMs.c
 *
 * Created: 06/07/2021 16:22:56
 * Author : diego
 */ 

#define F_CPU	16000000UL
#include <avr/io.h>

int main(void)
{
    DDRD = 0b0110000;	// Pinos OC0B e OC0A (PD5 e PD6) como sa�da
	PORTD = 0b10011111;	// Zera as sa�das e hailita pull-ups nos pinos n�o utilizados
	
	// MODO CTC
	TCCR0A  = 0b01010010;	// Habilita OC0A e OC0B para trocar de estado na igualdade de compara��o
	TCCR0B = 0b00000001;	// Liga TC0 com prescaler = 1
	OCR0A = 200;			// M�ximo valor de contagem
	OCR0B = 100;			// Deslocamento de OC0B em rela��o a OC0A
    while (1) 
    {
    }
}

