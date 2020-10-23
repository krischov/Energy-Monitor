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


ISR(ADC_vect) {
	if (ADMUX == 0b01000000) {
		v_vs = adc_read();
	}
	else if (ADMUX == 0b01000001) {
		v_is = adc_read();
	}
	TIFR0 = 0b00000001;
}


/*
void adc_init() {
	ADMUX = 0b01000000;
	ADCSRA = 0b10111110; // WHEN CONVERSION COMPLETE, CHANGES CHANNEL
	ADCSRB = 0b00000100;
}
*/

void adc_init() {
	ADMUX = 0b01000000;
	ADCSRA = 0b11001011;
	ADCSRB = 0b00000100;
}


 uint16_t adc_read(uint8_t channel){
	 ADMUX &= 0xF0; //Clear channel selection
	 ADMUX |= channel; //Set the channel to convert
	 ADCSRA |= (1 << ADSC); //Starting an ADC conversion
	 return ADC; //Alternatively you can write return ADC;
 }
 
 uint32_t adc_convert(uint16_t value){
	 
	 float dc_voltage_mv;
	 uint32_t voltage;
	 dc_voltage_mv = ((float) value * 5)/1024;
	 voltage = dc_voltage_mv*100;
	 return voltage;
 }
 
 