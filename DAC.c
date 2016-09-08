// dac.c
// This software configures DAC output
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 8/25/2014 
// Last Modified: 3/6/2015 
// Section 1-2pm     TA: Wooseok Lee
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

#include <stdint.h>
#include "tm4c123gh6pm.h"
// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data

// **************DAC_Init*********************
// Initialize 6-bit DAC, called once 
// Input: none
// Output: none
// Port B Pins 0-5
void DAC_Init(void){
	unsigned long volatile delay;
	SYSCTL_RCGCGPIO_R |= 0x02;
	delay = SYSCTL_RCGCGPIO_R;
	GPIO_PORTB_AMSEL_R &= ~0x0F;	//clears bits 0-3 for no analog
	GPIO_PORTB_PCTL_R = 0x00000000;
	GPIO_PORTB_DIR_R |=	0x0F;			//make bits PB3-0 outputs
	GPIO_PORTB_AFSEL_R &= ~0x0F;	//disable alt function for pins 0-3
	GPIO_PORTB_DEN_R |= 0x0F;			//enable digital I/O on PB0-0
}

// **************DAC_Out*********************
// output to DAC
// Input: 6-bit data, 0 to 63 
// Output: none
void DAC_Out(uint32_t data){
	GPIO_PORTB_DATA_R = data;
}

