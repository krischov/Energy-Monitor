/*
 * Final_Project.c
 *
 * Created: 20/10/2020 18:07:58
 * Author : Sai
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
	usart_init(BAUDRATE); //initialises uart with baud rate of BAUDRATE value
	while (1) {
		usart_transmit_voltage(RMSVoltage); //calls function to transmit RMSVoltage value
		usart_transmit_current(PeakCurrent); //calls function to transmit PeakCurrent value
		usart_transmit_power(Power); //calls function to transmit Power value
		_delay_ms(1000); //sets a delay for 1 second

	}
}
