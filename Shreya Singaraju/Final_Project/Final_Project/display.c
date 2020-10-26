
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
int patterns[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

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


static volatile uint16_t DispNo = 0;
static volatile uint8_t DispPos = 1;


static volatile uint8_t ones = 0;
static volatile uint8_t tens = 0;
static volatile uint8_t hundreds = 0;
static volatile uint8_t thousands = 0;


uint8_t bit_pattern = 0;

uint8_t segmentDisp(uint8_t num){

	return patterns[num];
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
	thousands = val/1000;
	hundreds = (val/100)%10;
	tens = (val/10)%10;
	ones = (val)%10;
	
	
}



//Render a single digit value (val) on the display at position (pos)
//Even though these variables can be derived from the global DispNo and DispPos it
//is helpful for utility if they are provided as function arguments
void Disp_Send(uint8_t val, uint8_t pos){
	
	//1. Construct the bit pattern to turn on the segments needed to
	// display number stored in val
	//2. Send the bit pattern to the shift-register as in Q2.2
	//3. Disable all digits
	//4. Latch the output by toggling SH_ST pin
	//5. Now, depending on the value of pos, enable the correct digit
	// (i.e. set Ds1, Ds2, Ds3 and Ds4 appropriately)
	
	SH_CP_OFF;
	SH_ST_OFF;
	
	DS1OFF;
	DS2OFF;
	DS3OFF;
	DS4OFF;
	
	
	bit_pattern = segmentDisp(val);
	
	for(int bit_position = 7; bit_position>=0; bit_position--){
		
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
	
	
}


//Send the next digit to Disp_Send() (call this function from a timer ISR)
void Disp_ScanNext(){

	uint8_t digit = 0;
	DispPos--;
	
	if(DispPos == 0){
		DispPos = 4;
		digit = ones;
	}
	else if(DispPos == 3){
		digit = tens;
	}
	else if(DispPos == 2){
		digit = hundreds;
	}
	else if(DispPos == 1 ){
		digit = thousands;
	}
	
	Disp_Send(digit, DispPos);
	
}
