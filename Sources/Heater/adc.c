#include "../KL25Z/es670_peripheral_board.h"




#define ADC0_SC1A_COCO (ADC0_SC1A >> 7)




/* ************************************************** */
/* Method name: 	   adc_initADCModule          */
/* Method description: configure ADC module           */
/* Input params:	   n/a 			      */
/* Outpu params:	   n/a 			      */
/* ************************************************** */
void adc_initADCModule(void)
{
   /* un-gate port clock*/
   SIM_SCGC6 |= SIM_SCGC6_ADC0(CGC_CLOCK_ENABLED);	//Enable clock for ADC

   /* un-gate port clock*/
   SIM_SCGC5 |= SIM_SCGC5_PORTE(CGC_CLOCK_ENABLED);

   /* set pin as ADC In */
   PORTE_PCR20 |= PORT_PCR_MUX(0u);   //Voltage Sensor
   PORTE_PCR21 |= PORT_PCR_MUX(0u);   //Temperature Sensor

   ADC0_CFG1 |= (ADC_CFG1_ADICLK(1u) | ADC_CFG1_MODE(0u) | ADC_CFG1_ADLSMP(0u) | ADC_CFG1_ADIV(0u) | ADC_CFG1_ADLPC(0u));

   /*
   ADC_CFG1_ADICLK(x)// bus/2 cloc	k selection
   ADC_CFG1_MODE(x)  // 8-bit Conversion mode selection
   ADC_CFG1_ADLSMP(x)// Short sample time configuration
   ADC_CFG1_ADIV(x)  // Clock Divide Select (Divide by 1)
   ADC_CFG1_ADLPC(x) // Normal power Configuration
   */

   ADC0_SC2 |= (ADC_SC2_REFSEL(0u) | ADC_SC2_DMAEN(0u) | ADC_SC2_ACFE(0u) | ADC_SC2_ADTRG(0u));

   /*
   ADC_SC2_REFSEL(x)// reference voltage selection - external pins
   ADC_SC2_DMAEN(x) // dma disabled
   ADC_SC2_ACREN(x) // dont care - range function
   ADC_SC2_ACFGT(x) // dont care - 0 -> Less than, 1 -> Greater Than
   ADC_SC2_ACFE(x)  // compare function disabled
   ADC_SC2_ADTRG(x) // When software trigger is selected, a conversion is initiated following a write to SC1A
   ADC_SC2_ADACT(x) // HW-set indicates if a conversion is being held, is cleared when conversion is done
   */

   ADC0_CFG2 |= (ADC_CFG2_ADLSTS(0u) | ADC_CFG2_ADHSC(0u) | ADC_CFG2_ADACKEN(0u) | ADC_CFG2_MUXSEL(0u));

   /*
   ADC_CFG2_ADLSTS(x)  // default time
   ADC_CFG2_ADHSC(x)   // normal conversion sequence
   ADC_CFG2_ADACKEN(x) // disable adack clock
   ADC_CFG2_MUXSEL(x)  // select 'a' channels
   */

}


/* ************************************************** */
/* Method name: 	   adc_initConvertion             */
/* Method description: init a conversion from D to A  */
/* Input params:	   n/a 							  */
/* Outpu params:	   n/a 							  */
/* ************************************************** */
void adc_initConvertion(uint32_t ch)
{
   ADC0_SC1A &= (ADC_SC1_ADCH(ch) | ADC_SC1_DIFF(0u) | ADC_SC1_AIEN(0u));

   /*
    *
   ADC_SC1_COCO(x) // conversion complete flag HW-set
   ADC_SC1_AIEN(x) // conversion complete interrupt disables	
   ADC_SC1_DIFF(x) // selects single-ended convertion
   ADC_SC1_ADCH(x) // selects channel, view 3.7.1.3.1 ADC0 Channel Assignment ADC0_SE4a from datasheet
   */
}

/* ************************************************** */
/* Method name: 	   adc_isAdcDone              */
/* Method description: check if conversion is done    */
/* Input params:	   n/a 		              */
/* Outpu params:	   n/a 			      */
/* ************************************************** */
int adc_isAdcDone(void)
{
	int iA;
	if(ADC0_SC1A_COCO) // watch complete convertion flag
		iA= 1; // if the conversion is complete, return 1
	else
		iA= 0; // if the conversion is still taking place, return 0

	return iA;
}

/* ************************************************** */
/* Method name: 	   adc_getConvertionValue     */
/* Method description: retrieve converted value       */
/* Input params:	   n/a 			      */
/* Outpu params:	   n/a 			      */
/* ************************************************** */
int adc_getConvertionValue(void)
{
   return ADC0_RA; // return the register value that keeps the result of convertion
}

