/* File name:        tc_hal.c                                        */
/* File description: This file has a couple of useful functions to   */
/*                   timer and counter hardware abstraction layer    */
/*                                                                   */
/* Author name:      dloubach                                        */
/* Creation date:    23out2015                                       */
/* Revision date:    25fev2016                                       */
/* ***************************************************************** */

#include "tc_hal.h"
#include "../KL25Z/es670_peripheral_board.h"

/* system includes */
#include "fsl_lptmr_driver.h"

#include "fsl_clock_manager.h"
#include "fsl_port_hal.h"
#include "fsl_gpio_hal.h"
#include "../Peripheral_package/lcd_hal.h"


unsigned int uValesq, uValAntigoesq=0;
unsigned int uValdir, uValAntigodir=0;


#define FlagC2  (TPM0_C2SC >> 7)
#define FlagC3  (TPM0_C3SC >> 7)


/* LPTMR configurations */
lptmr_user_config_t lptmrConfig =
{
    .timerMode              = kLptmrTimerModeTimeCounter,
    .freeRunningEnable      = false,
    .prescalerEnable        = true,
    .prescalerClockSource   = kClockLptmrSrcLpoClk,
    .prescalerValue         = kLptmrPrescalerDivide2,
    .isInterruptEnabled     = true,
};

/* LPTMR driver state information */
lptmr_state_t lptmrState;

void tc_init(void){


	/* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTE(CGC_CLOCK_ENABLED);  /*Ungate portE*/
    SIM_SCGC6 |= SIM_SCGC6_TPM0(CGC_CLOCK_ENABLED);	  /*Ungate TPM0*/


    /* set pin clckext */
    PORTE_PCR30 = PORT_PCR_MUX(3U); // esq
    PORTE_PCR29 = PORT_PCR_MUX(3U);  // dir


    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(MCG_S_OSCINIT0_MASK);  /*OscerCLK*/



    TPM0_SC |= TPM_SC_PS(0x00U);
    TPM0_SC |= TPM_SC_CMOD(0x02U); /*SINTAXE MODULO_REGISTRADOR_CAMPO*/
    TPM0_SC |= TPM_SC_CPWMS(0x00u);/*Up counting mode*/

    TPM0_C2SC = TPM_CnSC_MSA(0u)| TPM_CnSC_MSB(0u) | TPM_CnSC_ELSA(1u) | TPM_CnSC_ELSB(0u) | TPM_CnSC_CHIE(1u);
    TPM0_C3SC = TPM_CnSC_MSA(0u)| TPM_CnSC_MSB(0u) | TPM_CnSC_ELSA(1u) | TPM_CnSC_ELSB(0u) | TPM_CnSC_CHIE(1u);



//	SIM_SCGC6 |= SIM_SCGC6_TPM0(CGC_CLOCK_ENABLED);			// Un-gate TPM0 clock
//	SIM_SCGC5 |= SIM_SCGC5_PORTE(CGC_CLOCK_ENABLED);		// Un-gate PORTE clock
//
//	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0b10); 					// Select TPM Source OSCERCLK clock
//
//	PORTE_PCR29 |= PORT_PCR_MUX(0b011u);					// Configure PTE29 as FTM0_CH2
//	PORTE_PCR30 |= PORT_PCR_MUX(0b011u);					// Configure PTE30 as FTM0_CH3
//
//	TPM0_SC &= ~TPM_SC_CPWMS(1);							// Increase counting
//	TPM0_SC |= TPM_SC_CMOD(0b01) | TPM_SC_PS(0b111);		// LPTPM counter increments on rising edge of LPTPM_EXTCLK & preescaler = 128
//	TPM0_CNT = 0;											// Reset counter
//
//	TPM0_C2SC &= ~(TPM_CnSC_MSB(1) | TPM_CnSC_ELSB(1));
//	TPM0_C2SC |= TPM_CnSC_MSA(0) | TPM_CnSC_ELSA(1) | TPM_CnSC_CHIE(1);
//
//	TPM0_C3SC &= ~(TPM_CnSC_MSB(1) | TPM_CnSC_ELSB(1));
//	TPM0_C3SC |= TPM_CnSC_MSA(0) | TPM_CnSC_ELSA(1) | TPM_CnSC_CHIE(1);
//
//	NVIC_EnableIRQ(TPM0_IRQn);





}


void TPM0_IRQHandler(void){
	if(FlagC2){
		uValesq= TPM0_CNT;
	}
	else if(FlagC3){

	}
	TPM0_C2SC |= TPM_CnSC_CHF(0u);
	TPM0_C3SC |= TPM_CnSC_CHF(0u);

}


double tc_SensorRPS_esq(void){
	double dTempEsq;
	int depEsq;
	//char word[15];

	depEsq = TPM0_CNT;


	dTempEsq = depEsq/20.0;

//	sprintf(word, "%d rot/s", dep);
//	lcd_setCursor(0,8);
//
//	lcd_writeString(word);

	TPM0_CNT = 0x00;


	return dTempEsq;
}

double tc_SensorRPS_dir(void){
	double dTempDir;
	int depDir;
	//char word[15];

	depDir = TPM2_CNT;


	dTempDir = depDir/20.0;

//	sprintf(word, "%d rot/s", dep);
//	lcd_setCursor(0,8);
//
//	lcd_writeString(word);

	TPM2_CNT = 0x00;

	return dTempDir;
}



/* LPTMR IRQ handler that would cover the same name's APIs in startup code */
/* Do not edit this part */
void LPTMR0_IRQHandler(void)
{
    LPTMR_DRV_IRQHandler(0U);
}



/* dummy code for hardware debug purpose */
void tc_testDelaySetup(void)
{
    CLOCK_SYS_EnablePortClock(PORTE_IDX);
    PORT_HAL_SetMuxMode(PORTE, 0u, kPortMuxAsGpio);
    GPIO_HAL_SetPinDir(PTE, 0u, kGpioDigitalOutput);
    GPIO_HAL_ClearPinOutput(PTE, 0u);
}
/* dummy code for hardware debug purpose */
void tc_TestDelay(void)
{
    static char cTest = 0;

    if(!cTest)
        GPIO_HAL_ClearPinOutput(PTE, 0u);
    else
        GPIO_HAL_SetPinOutput(PTE, 0u);

    cTest ^= 1u;
}
/* dummy code for hardware debug purpose */
void tc_lptmrCallBack(void)
{
    tc_TestDelay();
}


/* ************************************************ */
/* Method name:        tc_installLptmr              */
/* Method description: Low power timer 0            */
/*                     initialization and start     */
/* Input params:       uiTimeInUs:                  */
/*                     time in micro seconds        */
/*                     tUserCallback:               */
/*                     function pointer to be called*/
/*                     when counter achieves        */
/*                     uiTimeInUs                   */
/* Output params:      n/a                          */
/* ************************************************ */
void tc_installLptmr0(uint32_t uiTimeInUs, lptmr_callback_t tUserCallback)
{
    /* Initialize LPTMR */
    LPTMR_DRV_Init(LPTMR0_IDX, &lptmrState, &lptmrConfig);

    /* Set timer period for TMR_PERIOD micro seconds */
    LPTMR_DRV_SetTimerPeriodUs(LPTMR0_IDX, uiTimeInUs);

    /* Install interrupt call back function for LPTMR */
    LPTMR_DRV_InstallCallback(LPTMR0_IDX, tUserCallback);

    /* Start LPTMR */
    LPTMR_DRV_Start(LPTMR0_IDX);
}
