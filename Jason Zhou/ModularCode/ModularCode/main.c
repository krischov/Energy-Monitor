/*
 * ModularCode.c
 *
 * Created: 28/08/2020 6:00:51 PM
 * Author : wljas
 */ 

#define F_CPU 800000UL //Defining system clock frequency //Defining system clock frequency
#include <avr/io.h> //Needed for using the macros for register addresses //Needed for using the macros for register addresses
#include <stdio.h> //Needed for printf() //Needed for printf()
#include <util/delay.h> //Needed for using _delay_ms() //Needed for using _delay_ms()
//#include "uart.h" //Including our uart peripheral library //Including our uart peripheral library
#include "adc.h" //Including our adc peripheral library //Including our adc peripheral library

int main(void){

	adc_init(); //Initializing the ADC
	uint32_t dc_voltage_mv = 0; //Initializing variable to hold ADC result
	while (1){
		dc_voltage_mv = ((uint32_t)adc_read_channel_single_conversion(2) * 5000)/1024; //Converting result to mV
		printf("Voltage: %d mV\n\r", (uint16_t)dc_voltage_mv); //Printing the result
		_delay_ms(500); //Repeat every 0.5s
	}
}

