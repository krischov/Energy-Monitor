/*
 * uart.c
 *
 * Created: 28/08/2020 17:59:57
 *  Author: Sai
 */ 
#include "common.h";
#include "uart.h";

void usart_init(uint16_t BAUD_RATE) {
	UBRR0 =  int (F_OSC/BAUD_RATE * 16) - 1;
	UCSR0A = 0b00100000;
	UCSR0B = 0b00001000;
	UCSR0C = 0b00000110;
}

void usart_transmit(uint8_t data) {
	while ((UCSR0A & 0b00100000) == 0) {
		;
	}
	UDR0 = data;
}
