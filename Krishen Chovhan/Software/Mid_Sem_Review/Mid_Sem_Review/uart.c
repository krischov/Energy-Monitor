/*
 * uart.c
 *
 * Created: 28/08/2020 5:59:55 PM
 *  Author: krish
 */ 
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "uart.h"
#include "common.h"

int ones;
int tens;
int hundreds;
int a;

void usart_init(uint32_t baud_rate){
	UCSR0A |= 0b00000000;
	UCSR0B |= (1 << TXEN0);
	UCSR0C |= (1 << UCSZ01);
	UCSR0C |= (1 << UCSZ00);
	UBRR0 =  800000 / (16 * baud_rate) - 1;
	
}

void usart_transmit(char byte){
	while((UCSR0A & (1<<UDRE0)) == 0){
		;
	}
	UDR0 = byte;
}

void usart_transmit_array(char* msg){
	for (uint8_t i = 0; i < strlen(msg); i++) { 
		a = msg[i];   
		usart_transmit(a);
	}
}

void usart_breakdown_ascii(uint16_t number){
	ones = (int)((number/1)%10) + 48;
	tens = (int)((number/10)%10) + 48;
	hundreds = (int)((number/100)%10) + 48;
}

void usart_transmit_voltage(uint16_t Voltage){
	while((UCSR0A & (1<<UDRE0)) == 0){
		;
	}
		usart_breakdown_ascii(Voltage);
		usart_transmit_array("RMS Voltage is: ");
		usart_transmit(hundreds);
		usart_transmit(tens);
		usart_transmit('.');
		usart_transmit(ones);
		usart_transmit_array("\n\r");
}

void usart_transmit_current(uint16_t Current){
	while((UCSR0A & (1<<UDRE0)) == 0){
		;
	}
		usart_breakdown_ascii(Current);
		usart_transmit_array("Peak Current is: ");
		usart_transmit(hundreds);
		usart_transmit(tens);
		usart_transmit(ones);
		usart_transmit_array("\n\r");
}

void usart_transmit_power(uint16_t Power){
	while((UCSR0A & (1<<UDRE0)) == 0){
		;
	}
		usart_breakdown_ascii(Power);
		usart_transmit_array("Power is: ");
		usart_transmit(hundreds);
		usart_transmit('.');
		usart_transmit(tens);
		usart_transmit(ones);
		usart_transmit_array("\n\r");
		usart_transmit_array("\n\r");
}
