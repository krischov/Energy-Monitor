/*
 * timer.c
 *
 * Created: 21/10/2020 00:52:46
 *  Author: Sai
 */ 
#define F_CPU 800000UL
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "timer.h"

void timer_init() {
	TCCR0A = 0b00000011;
	TCCR0B = 0b00001010;
	OCR0A = 0b01100011;
}

void timer_stop_clear(){
	TCCR0A = 0b00000000;
	TCCR0B = 0b00000000;
	OCR0A = 0b00000000;
}