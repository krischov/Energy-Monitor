/*
 * calculations.c
 *
 * Created: 21/10/2020 21:26:09
 *  Author: Sai
 */ 

#include "common.h"

extern volatile uint16_t pfTimer;

float calculate_rms_voltage(volatile float *v_vs){
	float coefficient = (float)1 / ((float) 20/1000);
	float v_vs_squared_total = 0;
	for(unsigned int i = 0; i < 20; i++){
		v_vs_squared_total += v_vs[i] * v_vs[i];
	}
	v_vs_squared_total = v_vs_squared_total * (float)1/1000 * coefficient;
	return (float) sqrt(v_vs_squared_total);
}

float calculate_rms_current(volatile float *v_is){
	float coefficient = (float)1 / ((float) 20/1000);
	float v_is_squared_total = 0;
	for(unsigned int i = 0; i < 20; i++){
		v_is_squared_total += v_is[i] * v_is[i];
	}
	v_is_squared_total = v_is_squared_total * (float)1/1000 * coefficient;
	return (float) sqrt(v_is_squared_total);
}

float calculate_power(volatile float *v_vs, volatile float *v_is) {
	float coefficient = (float) 1 / (float) 20;
	float totalPower = 0;
	for (int i = 0; i < 20; i++) {
		totalPower += v_vs[i] * v_is[i];
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
