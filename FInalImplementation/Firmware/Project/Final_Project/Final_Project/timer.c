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
	//initialize Timer0 in CTC mode, Pre-scaler 8, Interrupt trigger on Counter0 overflow, period of 1ms
	TCCR0A = 0b00000010;
	TCCR0B = 0b00000010;
	OCR0A = 99;
	TIMSK0 = 0b00000010;
}

void timer_stop_clear(){
	//stops Timer0 and clears timer counter
	TCCR0B = 0b00000000;
	TCNT0 = 0;
}

void timer1_init() {
	//initialize Timer1 in normal mode, Pre-scaler 8
	TCCR1A = 0b00000000;
	TCCR1B = 0b00000010;
}

void timer1_stop() {
	//stops Timer1
	TCCR1B = 0b00000000;
}