/*
 * uart.c
 *
 * Created: 28/08/2020 5:59:55 PM
 *  Author: krish
 */ 


void usart_init(uint16_t ubrr){
	UCSR0A |= 0b00000000;
	UCSR0B |= (1 << TXEN0);
	UCSR0C |= (1 << UCSZ01);
	UCSR0C |= (1 << UCSZ00);
	UBRR0 =  ubrr;
	
}


void usart_transmit(uint8_t data){
	while((UCSR0A & (1<<UDRE0)) == 0){
		;
	}
	UDR0 = data;
}