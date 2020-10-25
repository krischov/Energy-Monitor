/*
 * calculations.h
 *
 * Created: 21/10/2020 21:26:18
 *  Author: Sai
 */ 


#ifndef CALCULATIONS_H_
#define CALCULATIONS_H_

float calculate_rms_voltage(float *v_vs);
float calculate_rms_current(float *v_is);
float calculate_power(float*v_vs, float *v_is);
float power_factor(uint16_t pfTimer); 

#endif /* CALCULATIONS_H_ */