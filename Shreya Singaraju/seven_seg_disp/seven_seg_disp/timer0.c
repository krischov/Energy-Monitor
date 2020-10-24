
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

ISR(TIMER0_COMPA_vect) {
	
	Disp_ScanNext();
}


void timer0_init()
{
	TCCR0A = 0b00000010; // Initializes TCCR0A Register to CTC mode
	TCCR0B = 0b00000011; // Initializes TCCR0B Register to CTC mode, sets prescaler
	TIMSK0 = 0b00000010; //Enable output compare match A interrupt
	OCR0A = 124; // Sets 124 as value to count to (period of 10ms)
}

