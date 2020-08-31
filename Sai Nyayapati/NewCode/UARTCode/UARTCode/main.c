/*
 * UARTCode.c
 *
 * Created: 31/08/2020 13:44:16
 * Author : Sai
 */ 

#include <stdint.h>
#include <string.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "common.h"
#include "uart.h"

int main(void)
{
	usart_init(BAUDRATE);
	uint16_t voltage = RMSVoltage * 10;
	uint16_t power = Power * 100;
	
	while (1)
    {
		usart_voltage(voltage);
		_delay_ms(1000);
		usart_current(PeakCurrent);
		_delay_ms(1000);
		usart_power(power);
		_delay_ms(1000);
    }
}

