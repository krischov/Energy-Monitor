/*
 * interrupt.c
 *
 * Created: 23/10/2020 3:52:08 PM
 *  Author: krish
 */ 

#include "common.h"

extern volatile uint8_t flag;
extern volatile uint8_t adc_count;
extern volatile bool sampleFinished;
volatile uint16_t pfTimer = 0;

ISR(INT0_vect) {
	sampleFinished = false;
	if(flag == 0){
		timer_init();
		flag = 1;
		timer1_init();
	}
	else if(flag == 1 && adc_count == 20){
		interrupt0_disable();
		timer_stop_clear();
		flag = 2;
		adc_count = 0;
		interrupt1_enable();
	}
}

ISR(INT1_vect) {
	if(flag == 2){
		timer_init();
		ADMUX = 0b01000001;
		flag = 3;
	}
	else if(flag == 3 && adc_count == 20){
		interrupt1_disable();
		timer1_stop();
		pfTimer = TCNT1;
		TCNT1 = 0;
		timer_stop_clear();
		flag = 0;
		ADMUX = 0b01000000;
		adc_count = 0;
		sampleFinished = true;
		interrupt0_enable();
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