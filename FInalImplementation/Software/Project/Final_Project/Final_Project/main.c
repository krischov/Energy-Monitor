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
#include "uart.h"
#include "common.h"
#include "adc.h"
#include "timer.h"
#include "display.h"
#include "calculations.h"

volatile uint8_t channel = 0b01000000;
volatile float v_vs[20];
volatile float v_is[20];
volatile uint16_t RMSVoltage;
volatile uint16_t PeakCurrent;
volatile uint16_t Power;

int main(void)
{	
	//float v_vs[20];
	//float v_is[20];
	adc_init();
	timer_init();
	
	usart_init(BAUDRATE); //initializes uart with baud rate of BAUDRATE value
	while (1) {
		usart_transmit_voltage(RMSVoltage); //calls function to transmit RMSVoltage value
		usart_transmit_current(PeakCurrent); //calls function to transmit PeakCurrent value
		usart_transmit_power(Power); //calls function to transmit Power value
		_delay_ms(1000); //sets a delay for 1 second

	}
}
