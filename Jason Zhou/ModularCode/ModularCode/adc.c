/*
 * adc.c
 *
 * Created: 28/08/2020 6:23:43 PM
 *  Author: wljas
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "adc.h"

// This function configures the ADC to use AVCC as reference and read ADC0 in single conversion mode
void adc_init(void){
	ADMUX = 0b01000000; //AVCC set as reference, ADC0 selected and results are right adjusted
	ADCSRA = 0b10000111; //Set ADEN bit to 1 (enable ADC) and prescaler to 111 (i.e. 128)
	//To improve readability write in the form "ADCSRA = (1<<ADEN) | (7<<ADPS0);"
	ADCSRB = 0b00000000; //Using the single conversion mode (for project you have to use auto trigger mode)
	DIDR0 = 0b00000000; //Buffers are not disabled (for project you may disable the buffers to save power)
}

uint16_t adc_read_channel_single_conversion(uint8_t channel){
	ADMUX &= 0xF0; //Clear channel selection
	ADMUX |= channel; //Set the channel to convert
	ADCSRA |= (1 << ADSC); //Starting an ADC conversion
	while ((ADCSRA & (1 << ADIF)) == 0) { //ADIF bit is checked to see if it is 0
		; //If ADIF bit is not 0, wait until it becomes 0
	}
	return ((ADCL << 0) | (ADCH << 8)); //Alternatively you can write return ADC;
}