/*
 * uart.h
 *
 * Created: 28/08/2020 18:00:07
 *  Author: Sai
 */ 


#ifndef UART_H_
#define UART_H_

#include <stdint.h>

void usart_init(uint16_t BAUD_RATE);
void usart_transmit_byte(uint8_t byte);
void usart_transmit_array(char*data);




#endif /* UART_H_ */