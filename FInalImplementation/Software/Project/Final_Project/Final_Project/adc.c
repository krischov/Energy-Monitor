/*
 * adc.c
 *
 * Created: 21/10/2020 00:52:03
 *  Author: Sai
 */ 
#include "adc.h"
#include <avr/io.h>
extern volatile uint16_t adc_vs[20];
extern volatile uint16_t adc_is[20];
extern volatile float v_vs[20];
extern volatile float v_is[20];
extern volatile uint8_t flag;
extern volatile uint8_t flag2;
extern volatile uint8_t channel;
extern volatile uint8_t adc_count;


ISR(ADC_vect) {
	if (ADMUX == 0b01000000 && adc_count < 20) {
		adc_vs[adc_count] = ADC;
		adc_count++;
	}
	else if (ADMUX == 0b01000001 && adc_count < 20) {
		adc_is[adc_count] = ADC;
		adc_count++;
	}
	TIFR0 |= (1 << TOV0);
}

void adc_init() {
	ADMUX = 0b01000000;
	ADCSRA = 0b11101010;
	ADCSRB = 0b00000011;
}


void adc_read_voltage(){
	for (uint8_t i = 0; i < 20; i++) {
		float adc_val = (float) adc_vs[i];
		v_vs[i] = ((float)(adc_val * 5) / (float) 1024 - 2.1) / (float) (0.0454016298);
	}
}

void adc_read_current(){
	for (uint8_t i = 0; i < 20; i++) {
		float adc_val = (float) adc_is[i];
		v_is[i] = (float) ((adc_val * 5) / (float) 1024 - 2.1) / (float) (1.146853147);
	}
}
 