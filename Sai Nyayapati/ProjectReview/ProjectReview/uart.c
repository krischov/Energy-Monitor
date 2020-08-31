/*
 * uart.c
 *
 * Created: 28/08/2020 17:59:57
 *  Author: Sai
 */ 
#include "common.h"
#include "uart.h"

#include <stdint.h>
#include <string.h>
#include <avr/io.h>
#include <stdio.h>

void usart_init(uint16_t baudRate) {
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

void usart_transmit_array(char data[3][16], int count) {
	if (count ==  2) {
		count = 0;
	}
	for (uint8_t i = count; i < 3; i++) {
		for (uint8_t j = 0; j < strlen(data[i]); j++) {
			char value = data[i][j];
			usart_transmit_byte(value);
			if (j == (strlen(data[i] - 1 ))){
				count++;
			}
			if (count > i) {
				break;
			}
		}
		if (count > i) {
			break;
		}
	}
}
