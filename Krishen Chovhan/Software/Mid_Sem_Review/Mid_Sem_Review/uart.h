/*
 * uart.h
 *
 * Created: 28/08/2020 6:00:15 PM
 *  Author: krish
 */ 


#ifndef UART_H_
#define UART_H_

usart_init(uint16_t baud_rate);
usart_transmit(uint8_t data);

#endif /* UART_H_ */