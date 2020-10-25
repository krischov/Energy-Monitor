/*
 * adc.c
 *
 * Created: 21/10/2020 00:52:03
 *  Author: Sai
 */ 
#include "adc.h"
#include <avr/io.h>
#include <stdbool.h>
extern volatile float v_vs[20];
extern volatile float v_is[20];
extern volatile uint8_t flag;
extern volatile uint8_t flag2;
extern volatile uint8_t channel;
extern volatile uint8_t adc_count;
extern volatile float adcVoltage;
extern volatile bool sampleFinished;
extern volatile float adcCurrent;

ISR(ADC_vect) {
	if (ADMUX == 0b01000000 && adc_count < 20) {
		v_vs[adc_count] = adc_read_voltage();
		adc_count++;
		sampleFinished = true;
	}
	else if (ADMUX == 0b01000001 && adc_count < 20) {
		v_is[adc_count] = adc_read_current();
		adc_count++;
		if (adc_count == 20) {
			
		} 
	}
	
	TIFR0 |= (1 << TOV0);
}

void adc_init() {
	ADMUX = 0b01000000;
	ADCSRA = 0b11101010;
	ADCSRB = 0b00000011;
}


float adc_read_voltage(){
	adcVoltage =  ((float)(ADC * 5) / (float) 1024 - 2.1) / (float) (0.0454016298);
	return adcVoltage; 
}

float adc_read_current(){
	adcCurrent = (float) ((ADC * 5) / (float) 1024 - 2.1) / (float) (1.146853147);
	return adcCurrent;
}
 

 