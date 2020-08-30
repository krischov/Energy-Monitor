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
#include "common.h"

#define F_OSC = 800000;
#define BAUD_RATE = 9600;



int main(void)
{
	int count = 0;
    char stringArray[3][17];
	
	strcpy(stringArray[0], "RMS Voltage is:");
	strcpy(stringArray[1], "Peak Current is:");
	strcpy(stringArray[2], "Power is:");
	
	
	
    while (1) 
    {
		usart_transmit_array(char stringArray);
		usart_transmit_byte(char  );
    }
}

