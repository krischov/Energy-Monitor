/*
 * adc.c
 *
 * Created: 21/10/2020 00:52:03
 *  Author: Sai
 */ 
#include "adc.h"
#include <avr/io.h>
extern volatile float v_vs[20];
extern volatile float v_is[20];
extern volatile uint8_t flag;
extern volatile uint8_t flag2;
extern volatile uint8_t channel;
extern volatile uint8_t adc_count;

ISR(ADC_vect) {
	if (ADMUX == 0b01000000 && adc_count < 20) {
		usart_transmit_current(456);
		v_vs[adc_count] = adc_read();
	}
	else if (ADMUX == 0b01000001 && adc_count < 20) {
		usart_transmit_current(999);
		v_is[adc_count] = adc_read();
	}
	adc_count++;
	TIFR0 |= (1 << TOV0);
}

void adc_init() {
	ADMUX = 0b01000000;
	ADCSRA = 0b01111011;
	ADCSRB = 0b00000100;
}


float adc_read(){
	//ADMUX &= 0xF0; //Clear channel selection
	//ADMUX |= channel; //Set the channel to convert
	ADCSRA |= (1 << ADSC); //Starting an ADC conversion
	return ((float) (ADC * 500)/1024); 
}
 /*
uint32_t adc_convert(uint16_t value){
	
	float dc_voltage_mv;
	uint32_t voltage;
	dc_voltage_mv = ((float) value * 5)/1024;
	voltage = dc_voltage_mv*100;
	return voltage;
}*/

 