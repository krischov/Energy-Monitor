/*
 * calculations.c
 *
 * Created: 21/10/2020 21:26:09
 *  Author: Sai
 */ 

#include <math.h>
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
	
	/*for (int i = 0; i < 19; i++) {
		float holdValue  = currentArray[i+1];
		currentArray[i] = holdValue;
		if (i == 18) {
			currentArray[19] = hold_0;
		}
	}*/
	float coefficient = (float) 1 / (float) 20;
	float totalPower = 0;
	for (int i = 0; i < 19; i++) {
		totalPower += (float) v_vs[i] * (float) v_is[i];
	}
	return (float) totalPower * (float) coefficient;
}

float power_factor (float phaseTimer) {
	float pf = (float) cos ((float) (phaseTimer * (float) 1/100000 * (float) 360) * (float) 50); 
	return pf;
}
//float calculate_energy

