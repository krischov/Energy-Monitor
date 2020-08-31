/*
 * uart.c
 *
 * Created: 31/08/2020 13:45:10
 *  Author: Sai
 */ 
#include <stdint.h>
#include <string.h>
#include <avr/io.h>
#include <stdio.h>

#include "common.h"
#include "uart.h"

void usart_init(uint32_t baudRate) {
	UBRR0 =  800000 / (16 * baudRate) - 1;
	UCSR0A |= 0b00000000;
	UCSR0B |= (1 << TXEN0);
	UCSR0C |= (1 << UCSZ01);
	UCSR0C |= (1 << UCSZ00);
}

void usart_transmit_byte(char byte) {
	while ((UCSR0A & 0b00100000) == 0) {
		;
	}
	UDR0 = byte;
}
void usart_transmit_array(char*msg){
	for (uint8_t i = 0; i < strlen(msg); i++){
		usart_transmit_byte(msg[i]);
	}
}
void usart_voltage(uint16_t voltage) {
	usart_transmit_array("RMS Voltage is: ");
	usart_transmit_byte(voltage/100 + 48);
	usart_transmit_byte((voltage/10)%10 + 48);
	usart_transmit_byte('.');
	usart_transmit_byte((voltage%10) + 48);
	usart_transmit_array("\n\r");
}
void usart_current(uint16_t current) {
	usart_transmit_array("Peak current is: ");
	usart_transmit_byte(current/100 + 48);
	usart_transmit_byte((current/10)%10 + 48);
	usart_transmit_byte(current%10 + 48);
	usart_transmit_array("\n\r");	
}
void usart_power(uint16_t power) {
	usart_transmit_array("Power is: ");
	usart_transmit_byte(power/100 + 48);
	usart_transmit_byte('.');
	usart_transmit_byte((power/10)%10 + 48);
	usart_transmit_byte((power%10) + 48);
	usart_transmit_array("\n\r");
	usart_transmit_array("\n\r");	
}
