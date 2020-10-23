/*
 * adc.h
 *
 * Created: 21/10/2020 00:52:31
 *  Author: Sai
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef ADC_H_
#define ADC_H_

void adc_init();
uint16_t adc_read(uint8_t channel);
uint32_t adc_convert(uint16_t value);

#endif /* ADC_H_ */