/*
 * interrupt.c
 *
 * Created: 23/10/2020 3:52:08 PM
 *  Author: krish
 */ 

#define F_CPU 800000UL
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "common.h"
#include "adc.h"



ISR(INT0_vect) {
	if(flag == 0 && flag2 == 0){
		ADCSRA |= (1 << ADATE);
		timer_init();
		flag++;
	}
	else if(flag == 1 && flag2 == 1){
		ADCSRA &= ~(1 << ADATE);
		timer_stop_clear();
		flag++;
		interrupt0_disable();
		interrupt1_enable();
		channel = 0b01000001;
	}
	flag2++;
}

ISR(INT1_vect) {
	if(flag == 2 && flag2 == 2){
		ADCSRA |= (1 << ADATE);
		timer_init();
		flag++;
	}
	else if(flag == 3 && flag2 == 3){
		ADCSRA &= ~(1 << ADATE);
		timer_stop_clear();
		flag++;
		interrupt1_disable();
		channel = 0b01000000;
	}
	flag2++;
}

void interrupt0_enable(){
	EICRA = 0b00000011;
	EIMSK |= (1 << INT0);
}

void interrupt1_enable(){
	EICRA = 0b00001100;
	EIMSK |= (1 << INT1);
}

void interrupt0_disable(){
	EICRA = 0b00000000;
	EIMSK = 0b00000000;
}

void interrupt1_disable(){
	EICRA = 0b00000000;
	EIMSK = 0b00000000;
}