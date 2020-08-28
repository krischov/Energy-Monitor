/*
 * Mid_Sem_Review.c
 *
 * Created: 28/08/2020 2:07:58 PM
 * Author : krish
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>

#define RMSVoltage 14.5
#define PeakCurrent 125
#define Power 1.60

int uart_initialise(uint16_t baud_rate){
	UCSR0A |= 0b00000000;
	UCSR0B |= (1 << TXEN0);
	UCSR0C |= (1 << UCSZ01);
	UCSR0C |= (1 << UCSZ00);
	UBRR0 =  800000/(16*baud_rate) - 1 ;
	
}

void usart_transmit(uint8_t data){
	while((UCSR0A & (1<<UDRE0)) == 0){
		;
	}
	UDR0 = data;
}

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

#include <avr/io.h>
#include <util/delay.h>

void usart_init(uint16_t ubrr){
	UCSR0A |= 0b00000000;
	UCSR0B |= (1 << TXEN0);
	UCSR0C |= (1 << UCSZ01);
	UCSR0C |= (1 << UCSZ00);
	UBRR0 =  ubrr;
	
}


void uart_transmit_array(uint16_t Array[]){
	for (uint8_t i = 0; i < 62; i++){
		uint8_t ones = (int)((Array[i]/1)%10);
		uint8_t tens = (int)((Array[i]/10)%10);
		uint8_t hundreds = (int)((Array[i]/100)%10);
		usart_transmit(hundreds + 48);
		usart_transmit(tens + 48);
		usart_transmit(ones + 48);
		usart_transmit(44);
		usart_transmit(32);
	}
}

int main(void){
	

	while(1)
	{
		uart_transmit_array(primeNumbers);
		_delay_ms(500);
	}
	
	
	
}