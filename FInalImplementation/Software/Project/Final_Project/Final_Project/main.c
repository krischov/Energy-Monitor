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
#include <math.h>
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
volatile bool enableADC = true;
volatile bool powerCalc = false;
volatile float phaseTimer = 0;

int main(void)
{	
	DDRB = 0xFF;
	//float v_vs[20];
	//float v_is[20];
	adc_init();
	timer_init();
	usart_init(BAUDRATE);
	interrupt0_enable();
	sei();
	while (1) {
		
		 if (sampleFinished == true) {
				
			
				usart_transmit_voltage(calculate_rms_voltage(v_vs)*10);
				//usart_transmit_current(v_is[i] * 1000);
				float RMSCurrent = calculate_rms_current(v_is); 
				usart_transmit_current(calculate_rms_current(v_is)*1000);
				float powerFactor = power_factor(phaseTimer);
				//if (powerCalc == true) {
					float Power = (float) calculate_power(v_vs, v_is);// * (float) powerFactor;
					usart_transmit_power(Power);
				//}
				
			sampleFinished = false;
			enableADC = true;
		} 
	}
}
