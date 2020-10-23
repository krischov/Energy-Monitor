/*
 * timer.c
 *
 * Created: 21/10/2020 00:52:46
 *  Author: Sai
 */ 
#include "timer.h"

void timer_init() {
	TCCR0A = 0b00000011;
	TCCR0B = 0b00001010;
	OCR0A = 0b01100011;
}
