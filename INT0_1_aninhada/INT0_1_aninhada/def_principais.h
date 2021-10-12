/*
 * def_principais.h
 *
 * Created: 23/08/2020 04:05:11
 *  Author: Diego
 */ 


#ifndef DEF_PRINCIPAIS_H_
#define DEF_PRINCIPAIS_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define set_bit(Y, bit_x) (Y|=(1<<bit_x))
#define clr_bit(Y, bit_x) (Y&=~(1<<bit_x))
#define tst_bit(Y, bit_x) (Y&(1<<bit_x))
#define cpl_bit(Y, bit_x) (Y^=(1<<bit_x))

#define LED0 PD5
#define LED1 PD6
#define LED2 PD7

#endif /* DEF_PRINCIPAIS_H_ */