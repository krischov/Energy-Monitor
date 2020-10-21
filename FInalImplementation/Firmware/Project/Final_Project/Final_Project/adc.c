/*
 * adc.c
 *
 * Created: 21/10/2020 00:52:03
 *  Author: Sai
 */ 
#include "adc.h"

void adc_init() {
	ADMUX = 0b01000000;
	ADCSRA = 0b10100101;
	ADCSRB = 0b00000001;
	DIDR0 = 0b00000000;
}

 uint16_t adc_read(uint8_t channel){
	 ADMUX &= 0xF0; //Clear channel selection
	 ADMUX |= channel; //Set the channel to convert
	 ADCSRA |= (1 << ADSC); //Starting an ADC conversion
	 while ((ADCSRA & (1 << ADIF)) == 0) { //ADIF bit is checked to see if it is 0
		 ; //If ADIF bit is not 0, wait until it becomes 0
	 }
	 return ((ADCL << 0) | (ADCH << 8)); //Alternatively you can write return ADC;
 }
 
 uint32_t adc_convert(uint16_t value){
	 
	 float dc_voltage_mv;
	 uint32_t voltage;
	 dc_voltage_mv = ((float) value * 5)/1024;
	 voltage = dc_voltage_mv*100;
	 return voltage;
 }
 
 