/*
 * common.h
 *
 * Created: 21/10/2020 00:54:12
 *  Author: Sai
 */ 


#ifndef COMMON_H_
#define COMMON_H_


#define F_CPU 800000UL
#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>

#include "uart.h"
#include "common.h"
#include "adc.h"
#include "timer.h"
#include "display.h"
#include "calculations.h"
#include "interrupt.h"

#define BAUDRATE 9600




#endif /* COMMON_H_ */