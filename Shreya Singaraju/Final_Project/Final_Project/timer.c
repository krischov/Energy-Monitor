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


ISR(TIMER2_COMPA_vect) {
	
	Disp_ScanNext();
}


void timer2_init()
{
	TCCR2A = 0b00000010; // Initializes TCCR0A Register to CTC mode
	TCCR2B = 0b00000011; // Initializes TCCR0B Register to CTC mode, sets prescaler
	TIMSK2 = 0b00000010; //Enable output compare match A interrupt
	OCR2A = 124; // Sets 124 as value to count to (period of 10ms)
}
