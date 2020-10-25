/*
 * timer.c
 *
 * Created: 21/10/2020 00:52:46
 *  Author: Sai
 */ 
#include "common.h"

ISR (TIMER0_COMPA_vect) {
	
}
void timer_init() {
	TCCR0A = 0b00000010;
	TCCR0B = 0b00000010;
	OCR0A = 99;
	TIMSK0 = 0b00000010;
}

void timer_stop_clear(){
	TCCR0B = 0b00000000;
	TCNT0 = 0;
}

void timer1_init() {
	TCCR1A = 0b00000000;
	TCCR1B = 0b00000010;
}

void timer1_stop() {
	TCCR1B = 0b00000000;
}