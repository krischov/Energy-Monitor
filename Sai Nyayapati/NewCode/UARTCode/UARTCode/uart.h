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
void usart_voltage(int voltage);
void usart_current(int current);
void usart_power(uint16_t power);
void usart_transmit_digit(int digit); 



#endif /* UART_H_ */