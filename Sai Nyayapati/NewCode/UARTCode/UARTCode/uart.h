/*
 * uart.h
 *
 * Created: 31/08/2020 13:45:23
 *  Author: Sai
 */ 


#ifndef UART_H_
#define UART_H_

#include <stdint.h>

void usart_init(uint32_t baudRate);
void usart_transmit_byte(char byte);
void usart_transmit_array(char*msg);
void usart_voltage(uint16_t voltage);
void usart_current(uint16_t current);
void usart_power(uint16_t power);




#endif /* UART_H_ */