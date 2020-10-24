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
extern volatile float adcVoltage;
extern volatile float adcCurrent;

ISR(ADC_vect) {
	if (ADMUX == 0b01000000 && adc_count < 20) {
		//usart_transmit_current(456);
		v_vs[adc_count] = adc_read_voltage();
		adc_count++;
	}
	else if (ADMUX == 0b01000001 && adc_count < 20) {
		//usart_transmit_current(999);
		v_is[adc_count] = adc_read_current();
		adc_count++;
	}
	
	TIFR0 |= (1 << TOV0);
}

void adc_init() {
	ADMUX = 0b01000000;
	ADCSRA = 0b11101011;
	ADCSRB = 0b00000100;
}


float adc_read_voltage(){
	//ADMUX &= 0xF0; //Clear channel selection
	//ADMUX |= channel; //Set the channel to convert
	//ADCSRA |= (1 << ADSC); //Starting an ADC conversion
	adcVoltage =  ((float)( ADC * 5) / (float) 1024 - 2.1) / (float) (0.0454016298);
	/*while ((ADCSRA & (1 << ADIF)) == 0) {
		;
	}*/
	return adcVoltage; 
}

float adc_read_current(){
	//ADMUX &= 0xF0; //Clear channel selection
	//ADMUX |= channel; //Set the channel to convert
	ADCSRA |= (1 << ADSC); //Starting an ADC conversion
	adcCurrent = (float) ((ADC * 5) / 1024 - 2.1) / (float) (1.145454545);
	return adcCurrent;
}
 /*
uint32_t adc_convert(uint16_t value){
	
	float dc_voltage_mv;
	uint32_t voltage;
	dc_voltage_mv = ((float) value * 5)/1024;
	voltage = dc_voltage_mv*100;
	return voltage;
}*/

 