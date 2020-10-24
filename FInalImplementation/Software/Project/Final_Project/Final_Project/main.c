/*
 * Final_Project.c
 *
 * Created: 20/10/2020 18:07:58
 * Author : Sai
 */ 

#define F_CPU 800000UL
#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
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
volatile float adcVoltage = 0;
volatile float adcCurrent = 0;
volatile bool sampleFinished = false;

int main(void)
{	
	//float v_vs[20];
	//float v_is[20];
	adc_init();
	timer_init();
	usart_init(BAUDRATE);
	interrupt0_enable();
	sei();
	//float array_vs[10] = {16.18, 6.18, 11.755, 19.02, 20, 19.02, 16.18, 11.755, 6.18, 0};
	
	 //initializes uart with baud rate of BAUDRATE value
	while (1) {
		
		if (sampleFinished == true) {
			cli();
			for (int i = 0; i < 20; i++) {
				
				//int value2 = v_is[i];
				
				usart_transmit_voltage((uint16_t)v_vs[i] * 100);
				//	_delay_ms(500);
				//usart_transmit_voltage(value2);
			}
			sei();
			sampleFinished = false;
			
		}
		
		/*
		float val = calculate_rms_voltage(array_vs, 10);
		usart_transmit_voltage(val*10);
		break;*/
		
	}
}
