/*
 * uart.h
 *
 * Created: 28/08/2020 18:00:07
 *  Author: Sai
 */ 


#ifndef UART_H_
#define UART_H_

void usart_init(uint16_t BAUD_RATE);
void usart_transmit(uint8_t data);




#endif /* UART_H_ */