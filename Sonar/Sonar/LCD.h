/*
 * LCD.h
 *
 * Created: 21/08/2020 19:49:12
 *  Author: Diego
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "def_principais.h"

#define DADOS_LCD      PORTD    // 4 bits de dados do LCD no PORTD
#define nibble_dados   1        /* 0 para via de dados do LCD nos 4 LSBs do PORT 
							    empregado (Px0-D4, Px1-D5, Px2-D6, Px3-D7).
								   1 para via de dados do LCD nos 4 MSBs do PORT
							    empregado (Px4-D4, Px5-D5, Px6-D6, Px7-D7)
								*/

#define CONTR_LCD     PORTD     // Pinos de controle
#define RS            PD2       // Pino de instrução ou dados
#define E             PD3       // Pino de enable do LCD

#define tam_vetor     3         // Número de digitos individuais para a conversão por ident_num()
#define conv_ascii    48        // 48 se ident_num() deve retornar um número no formato ASCII (0 para formato normal)

#define pulso_enable() _delay_us(1); set_bit(CONTR_LCD, E); _delay_us(1); clr_bit(CONTR_LCD, E); _delay_us(45)

void cmd_LCD(unsigned char, char cd);
void inic_LCD_4bits();
void escreve_LCD(char *c);
void escreve_LCD_Flash(const char *c);
void ident_num(unsigned int valor, unsigned char *disp);
 
#endif /* LCD_H_ */