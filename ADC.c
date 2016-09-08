// ADC.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0
// Last Modified: 4/17/2016
// Student names: Genki Oji and David Yu
// Last modification date: 4/17/2016

#include <stdint.h>
#include "tm4c123gh6pm.h"

// ADC initialization function 
// Input: none
// Output: none
void ADC_Init(void){ 
	//GPIO Specific
	volatile uint32_t delay;
	SYSCTL_RCGCGPIO_R |= 0x10;
	while((SYSCTL_PRGPIO_R&0x10) == 0){};
	GPIO_PORTE_DIR_R &= ~0x04;
	GPIO_PORTE_AFSEL_R |= 0x04;
	GPIO_PORTE_DEN_R &= ~0x04;
	GPIO_PORTE_AMSEL_R |= 0x04;
	//ADC Specific
	SYSCTL_RCGCADC_R |= 0x01;		//turn on ADC0 clock
	delay = SYSCTL_RCGCADC_R;
	delay = SYSCTL_RCGCADC_R;
	delay = SYSCTL_RCGCADC_R;
	delay = SYSCTL_RCGCADC_R;
	ADC0_PC_R = 0x01;						//use 125k Hz clock speed
	ADC0_SSPRI_R = 0x0123;			//Seq 3 is highest priority
	ADC0_ACTSS_R	&= ~0x0008;		//disable sample seq 3
	ADC0_EMUX_R &= ~0xF000;			//seq3 is software trigger;
	ADC0_SSMUX3_R = (ADC0_SSMUX3_R&0xFFFFFFF0) + 1;		//Ain1 (PE2)
	ADC0_SSCTL3_R	= 0x0006;			//no TS0 D0, yes IE0 END0
	ADC0_IM_R &= ~0x0008;				//disable SS3 interrupts
	ADC0_ACTSS_R |= 0x0008;			//enable sample seq 3;
}

//------------ADC_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
uint32_t ADC_In(void){  
	uint32_t result;
	ADC0_PSSI_R = 0x0008;		//initiate SS3
	while((ADC0_RIS_R&0x08)==0){};
	result = ADC0_SSFIFO3_R&0xFFF;		//read 12 bit result
	ADC0_ISC_R = 0x0008;
  return result;
}


