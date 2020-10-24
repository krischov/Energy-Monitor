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
#include <stdbool.h>
#include "uart.h"
#include "common.h"
#include "interrupt.h"
#include "adc.h"
#include "timer.h"
extern volatile uint8_t flag;
extern volatile uint8_t flag2;
extern volatile uint8_t channel;
extern volatile uint8_t adc_count;
extern volatile bool sampleFinished;

ISR(INT0_vect) {
	if(flag == 0){
		//usart_transmit_current(789);
		//ADCSRA |= (1 << ADEN);
		timer_init();
		flag = 1;
	}
	else if(flag == 1 && adc_count == 20){
		//usart_transmit_current(444);
		//ADCSRA &= ~(1 << ADEN);
		timer_stop_clear();
		interrupt0_disable();
		interrupt1_enable();
		flag = 2;
		adc_count = 0;
		sampleFinished = true;
		
	}
}

ISR(INT1_vect) {
	if(flag == 2){
		//usart_transmit_current(111);
		adc_init();
		ADMUX = 0b01000001;
		//ADCSRA |= (1 << ADEN);
		timer_init();
		flag = 3;
	}
	else if(flag == 3 && adc_count == 20){
	//	usart_transmit_current(420);
		//ADCSRA &= ~(1 << ADEN);
		timer_stop_clear();
		interrupt1_disable();
		flag = 0;
		interrupt0_enable();
		ADMUX = 0b01000000;
		sampleFinished = true;
		adc_count = 0;
		
	}
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