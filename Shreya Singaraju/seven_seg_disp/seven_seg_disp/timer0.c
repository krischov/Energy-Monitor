
/*
* timer0.c
*
* Created: 23/10/2020 9:19:10 PM
*  Author: shreya
*/

#define F_CPU 800000UL

#include "timer0.h"
#include "display.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

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

