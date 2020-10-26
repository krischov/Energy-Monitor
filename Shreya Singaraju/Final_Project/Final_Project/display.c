
/*
* display.c
*
* Created: 26/10/2020 2:20:28 PM
*  Author: shrey
*/


/*
* display.c
*
* Created: 23/10/2020 8:38:29 PM
*  Author: shrey
*/
#define F_CPU 800000UL

#include "display.h"
#include "timer.h"
#include <avr/io.h>
#include <util/delay.h>


//Define macros for seven segment bit patterns
#define SET0 0b00111111;
#define SET1 0b00000110;
#define SET2 0b01011011;
#define SET3 0b01001111;
#define SET4 0b01100110;
#define SET5 0b01101101;
#define SET6 0b01111101;
#define SET7 0b00000111;
#define SET8 0b01111111;
#define SET9 0b01101111;

//Define macros for seven segment bit patterns
//int patterns[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

//Define macros for turning digit displays on and off
#define DS1ON PORTD &= ~(1<<PIND4);
#define DS1OFF PORTD |= (1<<PIND4);

#define DS2ON PORTD &= ~(1<<PIND5);
#define DS2OFF PORTD |= (1<<PIND5);

#define DS3ON PORTD &= ~(1<<PIND6);
#define DS3OFF PORTD |= (1<<PIND6);

#define DS4ON PORTD &= ~(1<<PIND7);
#define DS4OFF PORTD |= (1<<PIND7);

//Define macros for toggling SH_CP and SH_ST
#define TOGGLE_SH_CP PORTC ^= (1<<PINC3);
#define TOGGLE_SH_ST PORTC ^= (1<<PINC5);

//Define macros for turning SH_CP, SH_ST and SH_DS on and off
#define SH_CP_ON PORTC |= (1<<PINC3);
#define SH_CP_OFF PORTC &= ~(1<<PINC3);

#define SH_ST_ON PORTC |= (1<<PINC5);
#define SH_ST_OFF PORTC &= ~(1<<PINC5);

#define SH_DS_ON PORTC |= (1<<PINC4);
#define SH_DS_OFF PORTC &= ~(1<<PINC4);


volatile uint16_t DispNo = 0;
volatile uint8_t DispPos = 1;


volatile uint8_t ones1 = 0;
volatile uint8_t tens1 = 0;
volatile uint8_t hundreds1 = 0;
volatile uint8_t thousands1 = 0;

extern int flagdisp;


uint8_t bit_pattern = 0;

uint8_t segmentDisp(uint8_t num){

	//return patterns[num];
	
	switch (num){
		case 0:
		bit_pattern = SET0;
		break;
		case 1:
		bit_pattern = SET1;
		break;
		case 2:
		bit_pattern = SET2;
		break;
		case 3:
		bit_pattern = SET3;
		break;
		case 4:
		bit_pattern = SET4;
		break;
		case 5:
		bit_pattern = SET5;
		break;
		case 6:
		bit_pattern = SET6;
		break;
		case 7:
		bit_pattern = SET7;
		break;
		case 8:
		bit_pattern = SET8;
		break;
		case 9:
		bit_pattern = SET9;
		break;
	}
	return bit_pattern;
}

void Disp_Init(void){
	
	
	DDRC |= (1 << 3) | (1 << 4) | (1 << 5); //set SH_CP, SH_DS, SH_ST as outputs
	DDRD |= (1 << 4) | (1 << 5) |(1 << 6) |(1 << 7); //set Ds1, Ds2, Ds3, Ds4 as outputs
	
}

//initializes segment display (initially digit one is on and all others are off)
void Segment_Init(void){
	
	DS1ON;
	DS2OFF;
	DS3OFF;
	DS4OFF;
	
}

//Sets the value to be displayed across the four digits
//This is better than sharing the global variable between files
void Disp_Set(uint16_t val){
	
	DispNo = val;
	thousands1 = val/1000;
	hundreds1 = (val/100)%10;
	tens1 = (val/10)%10;
	ones1 = (val)%10;
	
}



//Render a single digit value (val) on the display at position (pos)
//Even though these variables can be derived from the global DispNo and DispPos it
//is helpful for utility if they are provided as function arguments
void Disp_Send(uint8_t val, uint8_t pos){
	
	SH_CP_OFF;
	SH_ST_OFF;
	
	DS1OFF;
	DS2OFF;
	DS3OFF;
	DS4OFF;
	
	
	if(pos == 1){
		DS1ON;
	}
	else if(pos == 2){
		DS2ON;
	}
	else if(pos == 3){
		DS3ON;
	}
	else if (pos == 4){
		DS4ON;
	}
	
	
	for(int bit_position = 7; bit_position>=0; bit_position--){
		
		bit_pattern = segmentDisp(val);
		if((bit_pattern & (1 << bit_position)) == (1 << bit_position)){
			SH_DS_ON;
			TOGGLE_SH_CP;
		}
		
		else {
			SH_DS_OFF;
			TOGGLE_SH_CP;
		}
		
		TOGGLE_SH_CP;
	}
	
	TOGGLE_SH_ST;

	
	
}


//Send the next digit to Disp_Send() (call this function from a timer ISR)
void Disp_ScanNext(){
	
		uint8_t digit = 0;
		
		if(DispPos == 0){
			DispPos = 4;
			digit = ones1;
		}
		else if(DispPos == 3){
			digit = tens1;
		}
		else if(DispPos == 2){
			digit = hundreds1;
		}
		else if(DispPos == 1 ){
			digit = thousands1;
		}
		
		Disp_Send(digit, DispPos);
		DispPos--;
	
}
