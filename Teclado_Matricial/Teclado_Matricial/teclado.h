/*
 * teclado.h
 *
 * Created: 06/07/2021 09:46:43
 *  Author: diego
 */ 


#ifndef TECLADO_H_
#define TECLADO_H_

#include "def_principais.h"

#define LINHA	PIND   // Registrador para a leitura das linhas
#define COLUNA	PORTD  // Registrador para a escrita das colunas

unsigned char ler_teclado();

#endif /* TECLADO_H_ */