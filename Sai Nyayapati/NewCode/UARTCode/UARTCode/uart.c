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
	UCSR0A = 0b00100000;
	UCSR0B = 0b00001000;
	UCSR0C = 0b00000110;
}

void usart_transmit_byte(char byte) {
	while ((UCSR0A & 0b00100000) == 0) {
		;
	}
	UDR0 = byte;
}

void usart_transmit_array(char* msg){
	for (uint8_t i = 0; i < strlen(msg); i++){
		usart_transmit_byte(msg[i]);
	}
}
void usart_voltage(char* voltage) {
	usart_transmit_array("RMS Voltage is: ");
	usart_transmit_array(voltage);
	usart_transmit_array(", ");
	
}
void usart_current(char* current) {
	usart_transmit_array("Peak current is: ");
	usart_transmit_array(current);
	usart_transmit_array(", ");
	
}
void usart_power(char* power) {
	usart_transmit_array("Power is: ");
	usart_transmit_array(power);
	usart_transmit_array(", ");
	
}
