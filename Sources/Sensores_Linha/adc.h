#ifndef SOURCES_ADC_H_
#define SOURCES_ADC_H_

#include "MKL25Z4.h"

#define ADC_0	0	//  PTE20
#define ADC_1	4	//  PTE21
#define ADC_2	3	//  PTE22
#define ADC_3	7	//  PTE23
#define ADC_4	8	//  PTB0
#define ADC_5	9	//  PTB1
#define ADC_6	12	//  PTB2
#define ADC_7	13	//  PTB3
#define ADC_8	14	//  PTC0
#define ADC_9	15	//  PTC1
#define ADC_10 	11	//  PTC2
#define ADC_11 	5	//  PTD1   LED AZUL FRDM-KL25Z


#define _8BIT  0
#define _10BIT 1
#define _12BIT 2
#define _16BIT 3

typedef struct cal_Sensors{
	uint8_t maxVal[5];
	uint8_t minVal[5];
}CAL_SENSOR;


void adc_init(uint8_t res);
uint8_t adc_read(uint8_t ch);
void calib(CAL_SENSOR *calibre_VALUE);
void init_calib(CAL_SENSOR *calibre_VALUE);


#endif /* SOURCES_ADC_H_ */
