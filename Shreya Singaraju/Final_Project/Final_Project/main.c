/*
 * Final_Project.c
 *
 * Created: 20/10/2020 18:07:58
 * Author : Sai
 */ 

#include "common.h"
#include "display.h"


volatile uint16_t adc_vs[20];
volatile uint16_t adc_is[20];
volatile float v_vs[20];
volatile float v_is[20];
volatile uint8_t flag = 0;
volatile uint8_t adc_count = 0;
volatile bool sampleFinished = false;

int main(void)
{	
	adc_init();
	timer_init();
	usart_init(BAUDRATE);
	interrupt0_enable();
	timer2_init();
	Segment_Init();
	Disp_Init();
	sei();
	while (1) {
		if (sampleFinished == true) {
			adc_read_voltage();
			adc_read_current();
			usart_transmit_voltage((float) calculate_rms_voltage(v_vs) * (float) 10);
			Disp_Set((float) calculate_rms_voltage(v_vs) * (float) 10);
			usart_transmit_current((float) calculate_rms_current(v_is) * (float) 1000 * (float) sqrt(2));
			usart_transmit_power((float)calculate_power(v_vs, v_is) * (float) 100);
		}
	}
}
