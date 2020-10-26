/*
* seven_seg_disp.c
*
* Created: 23/10/2020 8:37:51 PM
* Author : shrey
*/

#define F_CPU 800000UL


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "display.h"
#include "timer0.h"

volatile uint16_t counter = 0;

int main(void)
{
	timer2_init();
	Segment_Init();
	Disp_Init();
	
	sei();
	
	while (1)
	{	
		
		if(counter > 9999){
			counter = 0;
		}
		
		Disp_Set(counter);
		counter++;
		_delay_ms(400);

	}
}

