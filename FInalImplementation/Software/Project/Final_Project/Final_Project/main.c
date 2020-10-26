/*
 * Final_Project.c
 *
 * Created: 20/10/2020 18:07:58
 * Author : Sai
 */ 

#include "common.h"

volatile uint16_t adc_vs[20];
volatile uint16_t adc_is[20];
volatile float v_vs[20];
volatile float v_is[20];
volatile float energy[20];
volatile uint8_t energy_count = 0;
volatile uint8_t flag = 0;
volatile uint8_t adc_count = 0;
volatile bool sampleFinished = false;
float total_energy = 0;

int main(void)
{	
	adc_init();
	timer_init();
	usart_init(BAUDRATE);
	interrupt0_enable();
	sei();
	while (1) {
		if (sampleFinished == true) {
			adc_read_voltage();
			adc_read_current();
			usart_transmit_voltage((float) calculate_rms_voltage(v_vs) * (float) 10);
			usart_transmit_current((float) calculate_rms_current(v_is) * (float) 100 * (float) sqrt(2));
			usart_transmit_power((float)calculate_power(v_vs, v_is) * (float) 100);
			total_energy += calculate_energy(v_vs, v_is);
			usart_transmit_energy((total_energy*100));
		}
	}
}
