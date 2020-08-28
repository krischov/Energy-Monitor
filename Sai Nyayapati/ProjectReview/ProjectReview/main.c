/*
 * ProjectReview.c
 *
 * Created: 28/08/2020 17:57:04
 * Author : Sai
 */ 

#include <avr/io.h>

/*
 * UART Implementation.c
 *
 * Created: 28/08/2020 14:41:15
 * Author : Sai
 */ 

#include <avr/io.h>

#define F_OSC = 800000;
#define BAUD_RATE = 9600;

void usart_init(uint16_t BAUD_RATE);
void usart_transmit(uint8_t data);

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

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