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
#include <string.h>


//#define F_OSC 800000UL
//#define BAUD_RATE 9600

int main(void)
	void usart_init(BAUDRATE);
	
	uint8_t count = 0;
	uint8_t dataCount = 0;
	
    char stringArray[3][16];
	char measurements[3][5];
	
	strcpy(stringArray[0], "RMS Voltage is: ");
	strcpy(stringArray[1], "Peak Current is: ");
	strcpy(stringArray[2], "Power is: ");
	
	sprintf(measurements[0], "%.1f", RMSVoltage);
	sprintf(measurements[1], "%d", PeakCurrent);
	sprintf(measurements[2], "%.2f", Power);
	
    while (1) 
    {
		usart_transmit_array(stringArray, count);
		if (dataCount == 2) {
			dataCount = 0;
		}
		for (uint8_t i = dataCount; i < 3; i++) {
			for (uint8_t j = 0; j < 4; j++) {
				usart_transmit_byte(measurements[i][j]);
				if (j == 3) {
					dataCount++;
					break;
				}
			}
			if (dataCount > i) {
				break;
			}
		}
    }
}

