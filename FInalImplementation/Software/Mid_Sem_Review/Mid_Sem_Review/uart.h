/*
 * uart.h
 *
 * Created: 28/08/2020 6:00:15 PM
 *  Author: krish
 */ 



#ifndef UART_H_
#define UART_H_

void usart_init(uint32_t baud_rate);
void usart_transmit(char data);
void usart_transmit_array(char* msg);
void usart_breakdown_ascii(uint16_t number);
void usart_transmit_voltage(uint16_t Voltage);
void usart_transmit_current(uint16_t Current);
void usart_transmit_power(uint16_t power);

#endif /* UART_H_ */