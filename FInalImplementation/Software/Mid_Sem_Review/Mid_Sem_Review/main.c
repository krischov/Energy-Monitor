/*
 * Mid_Sem_Review.c
 *
 * Created: 28/08/2020 2:07:58 PM
 * Author : krish
 */ 

#define F_CPU 800000
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h> 
#include "uart.h"
#include "common.h"


int main(void)
{
	usart_init(BAUDRATE); //initialises uart with baudrate of BAUDRATE value
    while (1) {
		usart_transmit_voltage(RMSVoltage); //calls function to transmit RMSVoltage value
		usart_transmit_current(PeakCurrent); //calls function to transmit PeakCurrent value
		usart_transmit_power(Power); //calls function to transmit Power value
		_delay_ms(1000); //sets a delay for 1 second 

	}
}