/*
 * FinalImplemenation.c
 *
 * Created: 31/08/2020 5:52:59 PM
 * Author : shrey
 */ 

#define F_CPU 800000UL
#define RMSVoltage 145
#define PeakCurrent 125
#define Power 160

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

void usart_init(uint16_t ubrr);
void usart_transmit(int data);
void usart_voltage(int value);
void usart_current(int value);
void usart_power(int value);


int main(void)
{
    usart_init(4);
    while (1) 
    {
		usart_voltage(RMSVoltage);	
		usart_current(PeakCurrent);	
		usart_power(Power);	
		_delay_ms(1000); 
    }
}

void usart_init(uint16_t ubrr){
	UCSR0A = 0b00100000;
	UCSR0B = 0b00001000;
	UCSR0C = 0b00000110;
	UBRR0 = ubrr;
}

void usart_transmit(int data){
	while ((UCSR0A & 0b00100000) == 0){
		;
	}
	UDR0 = data;
}

void usart_transmit_char(char* sentence){
	while ((UCSR0A & 0b00100000) == 0){
		;
	}
	UDR0 = *sentence;
}


void usart_voltage(int value){
		int val_1, val_2, val_3;
		val_3 = (value%10) + 48;
		value = value/10;
		val_2 = (value%10) + 48;
		value = value/10;
		val_1 = (value%10) + 48;
		
		usart_transmit_char("R");
		usart_transmit_char("M");
		usart_transmit_char("S");
		usart_transmit_char(" ");
		usart_transmit_char("V");
		usart_transmit_char("o");
		usart_transmit_char("l");
		usart_transmit_char("t");
		usart_transmit_char("a");
		usart_transmit_char("g");
		usart_transmit_char("e");
		usart_transmit_char(" ");
		usart_transmit_char("i");
		usart_transmit_char("s");
		usart_transmit_char(":");
		usart_transmit_char(" ");
		usart_transmit(val_1);
		usart_transmit(val_2);
		usart_transmit(46);
		usart_transmit(val_3);
		usart_transmit_char(" ");
		usart_transmit(13);
}

void usart_current(int value){
	int val_1, val_2, val_3;
	val_3 = (value%10) + 48;
	value = value/10;
	val_2 = (value%10) + 48;
	value = value/10;
	val_1 = (value%10) + 48;


	
		usart_transmit_char("P");
		usart_transmit_char("e");
		usart_transmit_char("a");
		usart_transmit_char("k");
		usart_transmit_char(" ");
		usart_transmit_char("C");
		usart_transmit_char("u");
		usart_transmit_char("r");
		usart_transmit_char("r");
		usart_transmit_char("e");
		usart_transmit_char("n");
		usart_transmit_char("t");
		usart_transmit_char(" ");
		usart_transmit_char("i");
		usart_transmit_char("s");
		usart_transmit_char(":");
		usart_transmit_char(" ");
		usart_transmit(val_1);
		usart_transmit(val_2);
		usart_transmit(val_3);
		usart_transmit_char(" ");
		usart_transmit(13);
}

void usart_power(int value){
	int val_1, val_2, val_3;
	val_3 = (value%10) + 48;
	value = value/10;
	val_2 = (value%10) + 48;
	value = value/10;
	val_1 = (value%10) + 48;
	
			usart_transmit_char("P");
			usart_transmit_char("o");
			usart_transmit_char("w");
			usart_transmit_char("e");
			usart_transmit_char("r");
			usart_transmit_char(" ");
			usart_transmit_char("i");
			usart_transmit_char("s");
			usart_transmit_char(":");
			usart_transmit_char(" ");
			
			usart_transmit(val_1);
			usart_transmit(46);
			usart_transmit(val_2);
			usart_transmit(val_3);
			usart_transmit_char(" ");
			usart_transmit(13);
		}