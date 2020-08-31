/*
 * adc.h
 *
 * Created: 31/08/2020 7:21:20 PM
 *  Author: wljas
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void adc_init(void);
uint16_t adc_read_channel_single_conversion(uint8_t channel);



#endif /* ADC_H_ */