/*
 * uart.c
 *
 * Created: 20/10/2020 18:09:36
 *  Author: Sai
 */ 
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "uart.h"
#include "common.h"

int ones;
int tens;
int hundreds;


void usart_init(uint32_t baud_rate){ // This function sets the initial values of the registers in the microcontroller.
	UCSR0A |= 0b00000000; //setting bit 5 in register UCSR0A to zero
	UCSR0B |= (1 << TXEN0); //setting bit 3 in register UCSR0B to 1
	UCSR0C |= (1 << UCSZ01); //setting bit 2 in register UCSR0C to 1
	UCSR0C |= (1 << UCSZ00); //setting bit 1 in register UCSR0C to 1
	UBRR0 =  800000 / (16 * baud_rate) - 1; //UBRR register calculation for baud rate.
	
}

void usart_transmit(char byte){ //This function transmits a character into UDR0
	while((UCSR0A & (1<<UDRE0)) == 0){ //waits for UDRE0 to set to 1 before transmitting character into UDR0
		;
	}
	UDR0 = byte;
}

void usart_transmit_array(char* msg){ //This function transmits a string of characters into UDR0
	for (uint8_t i = 0; i < strlen(msg); i++) { //loops through a string of characters
		usart_transmit(msg[i]); //calls the usart_transmit() function to transmit each individual character in the string
	}
}

void usart_breakdown_ascii(uint16_t number){ //This function converts uint16_t numbers into ascii values
	ones = ((number/1)%10) + 48; //Adds the number 48 to uint16_t values based on ascii table
	tens = ((number/10)%10) + 48;
	hundreds = ((number/100)%10) + 48;
}

void usart_transmit_voltage(uint16_t Voltage){ //This function transmits the RMS Voltage value into UDR0
	usart_breakdown_ascii(Voltage); //Converts the RMS Voltage value into ascii
	usart_transmit_array("RMS Voltage is: "); //Transmits the character sentence into UDR0
	usart_transmit(hundreds); //Obtains the 'tens' digit of the voltage value
	usart_transmit(tens); //Obtains the 'ones' digit of the voltage value
	usart_transmit('.'); //Transmits a decimal point
	usart_transmit(ones);//Obtains the 'tenths' digit of the voltage value
	usart_transmit_array("\n\r"); //transmits a new line
}

void usart_transmit_current(uint16_t Current){ //This function transmits the Peak Current value into UDR0
	usart_breakdown_ascii(Current); //Converts the current value into ascii
	usart_transmit_array("Peak Current is: "); //Transmits the character sentence into UDR0
	usart_transmit(hundreds); //Obtains the 'hundreds' digit of the voltage value
	usart_transmit(tens); //Obtains the 'tens' digit of the voltage value
	usart_transmit(ones); //Obtains the 'ones' digit of the voltage value
	usart_transmit_array("\n\r"); //transmits a new line
}

void usart_transmit_power(uint16_t power){ //This function transmits the Power value into UDR0
	usart_breakdown_ascii(power); //Converts the power value into ascii
	usart_transmit_array("Power is: "); //Transmits the character sentence into UDR0
	usart_transmit(hundreds); //Obtains the 'ones' digit of the voltage value
	usart_transmit('.'); //Transmits a decimal point
	usart_transmit(tens); //Obtains the 'tenths' digit of the voltage value
	usart_transmit(ones); //Obtains the 'hundredths' digit of the voltage value
	usart_transmit_array("\n\r"); //transmits a new line
	usart_transmit_array("\n\r"); //transmits a new line
}