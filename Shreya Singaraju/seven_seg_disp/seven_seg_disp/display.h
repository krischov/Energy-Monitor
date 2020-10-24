
/*
 * display.h
 *
 * Created: 23/10/2020 8:38:39 PM
 *  Author: shrey
 */ 

#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <avr/io.h>

uint8_t segmentDisp(uint8_t num);
void Disp_Init(void);
void Segment_Init(void);
void Disp_Set(uint16_t val);
void Disp_Send(uint8_t val, uint8_t pos);
void Disp_ScanNext();

#endif