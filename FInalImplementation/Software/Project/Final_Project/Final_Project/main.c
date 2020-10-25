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
volatile uint16_t RMSVoltage;
volatile uint16_t PeakCurrent;
volatile uint16_t Power;
volatile uint8_t flag = 0;
volatile uint8_t flag2 = 0;
volatile uint8_t adc_count = 0;
volatile bool sampleFinished = false;




int main(void)
{	
	DDRB = 0xFF;
	adc_init();
	timer_init();
	usart_init(BAUDRATE);
	interrupt0_enable();
	sei();
	while (1) {
		if (sampleFinished = true) {
			adc_read_voltage();
			adc_read_current();
			float voltage_rms = (float) calculate_rms_voltage(v_vs) * (float) 10;
			usart_transmit_voltage(voltage_rms);
			float current_rms = calculate_rms_current(v_is);
			usart_transmit_current(current_rms*1000);
			float Power = calculate_power(v_vs, v_is);
			usart_transmit_power(Power*100);
		}
	}
}
