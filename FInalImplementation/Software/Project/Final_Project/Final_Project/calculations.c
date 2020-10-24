/*
 * calculations.c
 *
 * Created: 21/10/2020 21:26:09
 *  Author: Sai
 */ 

#include <math.h>
float calculate_rms_voltage(float *v_vs, float sample_size){
	float coefficient = (float)1 / ((float)sample_size/1000);
	float v_vs_squared_total = 0;
	float v_vs_squared_total_xTsample = 0;
	float v_rms_squared = 0;
	float v_rms = 0;
	for(unsigned int i = 0; i < sample_size; i++){
		v_vs_squared_total += v_vs[i] * v_vs[i];
	}
	v_vs_squared_total_xTsample = v_vs_squared_total * (float)1/1000;
	v_rms_squared = v_vs_squared_total_xTsample * coefficient;
	v_rms = sqrt(v_rms_squared);
	return v_rms;
}

float calculate_rms_current(float *v_is, float sample_size){
	float coefficient = (float)1 / ((float)sample_size/1000);
	float v_is_squared_total = 0;
	float v_is_squared_total_xTsample = 0;
	float v_rms__current_squared = 0;
	float i_rms = 0;
	for(unsigned int i = 0; i < sample_size; i++){
		v_is_squared_total += v_is[i] * v_is[i];
	}
	v_is_squared_total_xTsample = v_is_squared_total * (float)1/1000;
	v_rms__current_squared = v_is_squared_total_xTsample * coefficient;
	i_rms = sqrt(v_rms__current_squared);
	return i_rms;
}
