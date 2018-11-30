#include "../KL25Z/es670_peripheral_board.h"
#include "adc.h"



#define ADC0_SC1A_COCO (ADC0_SC1A >> 7)


void adc_init(uint8_t res){
	// Enable clocks
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK; // ADC 0 clock

	// Configure ADC
	ADC0_CFG1 = 0; // Reset register

	ADC0_CFG1 |= (ADC_CFG1_MODE(res) | // resolução da conversão
	            ADC_CFG1_ADICLK(0) | // Input Bus Clock
	            ADC_CFG1_ADIV(1));	 // Clock divide by 2

	ADC0_SC3 = 0; // Reset SC3 // Calibraçãooo

	ADC0_SC1A |= ADC_SC1_ADCH(31); // Disable module
}


uint8_t adc_read(uint8_t ch){
	ADC0_SC1A = ch ;//& ADC_SC1_ADCH_MASK; //Write to SC1A to start conversion
	while(ADC0_SC2 & ADC_SC2_ADACT_MASK); // Conversion in progress
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK)); // Run until the conversion is complete
	return ADC0_RA;
}


void init_calib(CAL_SENSOR *calibre_VALUE){
	int i;

	for(i=0;i<5;i++){
		calibre_VALUE->maxVal[i]= 0;
		calibre_VALUE->minVal[i]= 100;
	}
}

void calib(CAL_SENSOR *calibre_VALUE){
	int i=0,j;
	uint8_t valores[5]={0,0,0,0,0} ;

	while(i<500000){
	valores[0]= adc_read(ADC_0);
	valores[1]= adc_read(ADC_1);
	valores[2]= adc_read(ADC_2);
	valores[3]= adc_read(ADC_3);
	valores[4]= adc_read(ADC_4);

	for(j=0;j<5;j++){
		if(valores[j]>=calibre_VALUE->maxVal[j]) calibre_VALUE->maxVal[j] = valores[j];
		if(valores[j]<=calibre_VALUE->minVal[j]) calibre_VALUE->minVal[j] = valores[j];
	}
	i++;
	}
}
