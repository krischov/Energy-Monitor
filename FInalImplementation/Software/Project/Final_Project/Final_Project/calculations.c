/*
 * calculations.c
 *
 * Created: 21/10/2020 21:26:09
 *  Author: Sai
 */ 
#include <math.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>
#include "uart.h"
#include "adc.h"
#include "timer.h"
#include "display.h"
#include "calculations.h"
#include "interrupt.h"

extern volatile uint16_t pfTimer;
float calculate_rms_voltage(float *v_vs){
	float coefficient = (float)1 / ((float) 20/1000);
	float v_vs_squared_total = 0;
	float v_vs_squared_total_xTsample = 0;
	float v_rms_squared = 0;
	float v_rms = 0;
	for(unsigned int i = 0; i < 20; i++){
		v_vs_squared_total += v_vs[i] * v_vs[i];
	}
	v_vs_squared_total_xTsample = v_vs_squared_total * (float)1/1000;
	v_rms_squared = v_vs_squared_total_xTsample * coefficient;
	v_rms = sqrt(v_rms_squared);
	return v_rms;
}

float calculate_rms_current(float *v_is){
	float coefficient = (float)1 / ((float)20/1000);
	float v_is_squared_total = 0;
	float v_is_squared_total_xTsample = 0;
	float v_rms__current_squared = 0;
	float i_rms = 0;
	for(unsigned int i = 0; i < 20; i++){
		v_is_squared_total += v_is[i] * v_is[i];
	}
	v_is_squared_total_xTsample = v_is_squared_total * (float)1/1000;
	v_rms__current_squared = v_is_squared_total_xTsample * coefficient;
	i_rms = sqrt(v_rms__current_squared);
	return i_rms;
}

float calculate_power(float *v_vs, float *v_is) {
	float hold_0 = v_is[0];
	float currentArray[20];
	
	for (int i = 0; i < 20; i++) {
		currentArray[i] = v_is[i];
	}
	float coefficient = (float) 1 / (float) 20;
	float totalPower = 0;
	for (int i = 0; i < 20; i++) {
		totalPower += v_vs[i] * currentArray[i];
	}
	float powerFactor = power_factor(pfTimer);
	return (float) totalPower * coefficient * powerFactor;
}
float power_factor (uint16_t pfTimer) {
	float pf_0 = (float) pfTimer * (float) 0.00001;
	float pf_1 = pf_0 - (float) 0.02;
	float pf_2 = pf_1 * (float) 18000;
	return (float) cos(pf_2 * 0.01745329252);
}

//float calculate_energy

