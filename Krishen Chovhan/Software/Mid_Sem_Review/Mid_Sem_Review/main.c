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
	usart_init(BAUDRATE);
    while (1) {
		usart_transmit_voltage(RMSVoltage);
		usart_transmit_current(PeakCurrent);
		usart_transmit_power(power);
		_delay_ms(1000);

	}
}