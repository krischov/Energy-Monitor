/*
 * calculations.c
 *
 * Created: 21/10/2020 21:26:09
 *  Author: Sai
 */ 

#include "common.h"

extern volatile uint16_t pfTimer;
extern volatile float energy[20];
extern volatile uint8_t energy_count;
extern float total_energy;

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
	float pf = (((float) pfTimer * (float) 0.00001) - (float) 0.2) * (float) 18000;
	return (float) cos(pf * 0.01745329252);
}

float calculate_energy(volatile float *v_vs, volatile float *v_is) {
	float power_value = (calculate_power(v_vs, v_is) * 0.02) / (float) 60;
	return power_value;
}