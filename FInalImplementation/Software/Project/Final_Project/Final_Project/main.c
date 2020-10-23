/*
 * Final_Project.c
 *
 * Created: 20/10/2020 18:07:58
 * Author : Sai
 */ 

#define F_CPU 800000UL
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "common.h"
#include "adc.h"
#include "timer.h"
#include "display.h"
#include "calculations.h"
#include "interrupt.h"

volatile uint8_t channel = 0b01000000;
volatile float v_vs[20];
volatile float v_is[20];
volatile uint16_t RMSVoltage;
volatile uint16_t PeakCurrent;
volatile uint16_t Power;
volatile uint8_t flag = 0;
volatile uint8_t flag2 = 0;
volatile uint8_t adc_count = 0;

int main(void)
{	
	//float v_vs[20];
	//float v_is[20];
	adc_init();
	timer_init();
	usart_init(BAUDRATE);
	interrupt0_enable();
	sei();
	
	 //initializes uart with baud rate of BAUDRATE value
	while (1) {
		cli();
		sei();
		//usart_transmit_voltage(123); //calls function to transmit RMSVoltage value
		//usart_transmit_current(123); //calls function to transmit PeakCurrent value
		//usart_transmit_power(123); //calls function to transmit Power value
		//_delay_ms(1000); //sets a delay for 1 second
		for (int i = 0; i < 20; i++) {
			int value = v_vs[i];
			int value2 = v_is[i];
			usart_transmit_voltage(value);
			_delay_ms(500);
			usart_transmit_current(value2);  
		}
		break;
	}
}
