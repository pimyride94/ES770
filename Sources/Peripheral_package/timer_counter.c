#include "../KL25Z/es670_peripheral_board.h"
#include "fsl_tpm_hal.h"

/* ************************************************** */
/* Method name: 	   timer_initTPM1AsPWM        */
/* Method description: configure Timer1 to act as PWM */
/* Input params:	   n/a 			      */
/* Outpu params:	   n/a 		              */
/* ************************************************** */
void timer_initTPM1AsPWM(void)
{
	/* un-gate port clock*/
	SIM_SCGC6 |= SIM_SCGC6_TPM1(CGC_CLOCK_ENABLED); //Enable clock for TPM1

	TPM1_SC |= TPM_SC_CPWMS(0u);   //up counting mode
	TPM1_SC |= TPM_SC_CMOD(1u);   //LPTPM Counter increments on every LPTPM counter clock
	TPM1_SC |= TPM_SC_PS(0u);   //Prescale 1:1

	TPM1_C1SC = TPM_CnSC_MSA(0u)| TPM_CnSC_MSB(1u) | TPM_CnSC_ELSA(0u) | TPM_CnSC_ELSB(1u);

	TPM1_CNT = 0u;
	TPM1_MOD = 100u;

//	TPM1_C1V = TPM_CnV_VAL(100u); //PWM 100%
//	TPM1_C1V = TPM_CnV_VAL(75u); //PWM 75%
//	TPM1_C1V = TPM_CnV_VAL(50u); //PWM 50%
//	TPM1_C1V = TPM_CnV_VAL(25u); //PWM 25%
//	TPM1_C1V = TPM_CnV_VAL(0u); //PWM 0%

}

/* ************************************************ */
/* Method name:        timer_coolerfan_setPWM         */
/* Method description: SET PWM */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void timer_coolerfan_setPWM(int uiVelPWM){
	TPM1_C1V = TPM_CnV_VAL(uiVelPWM);
}



/* ************************************************ */
/* Method name:        timer_coolerfan_init         */
/* Method description: Initialize the cooler device */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void timer_coolerfan_init(void)
{
    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);

    /* set pin as PWM */
    PORTA_PCR13 |= PORT_PCR_MUX(3u);


}

