#include "../KL25Z/es670_peripheral_board.h"
#include "fsl_tpm_hal.h"
#include "motorPWM.h"


void init_motorEsquerdo_TPM1AsPWM(void)
{
	/* un-gate port clock*/
	SIM_SCGC6 |= SIM_SCGC6_TPM1(CGC_CLOCK_ENABLED); //Enable clock for TPM1

    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(MCG_S_OSCINIT0_MASK);  /*OscerCLK*/
    SIM_SOPT4 |= SIM_SOPT4_TPM1CLKSEL(0x00u);

	TPM1_SC |= TPM_SC_CPWMS(0u)| TPM_SC_CMOD(1u)| TPM_SC_PS(0u);   //up counting mode //LPTPM Counter increments on every LPTPM counter clock //Prescale 1:1

	TPM1_C1SC = TPM_CnSC_MSA(0u)| TPM_CnSC_MSB(1u) | TPM_CnSC_ELSA(0u) | TPM_CnSC_ELSB(1u);

	TPM1_C0SC = TPM_CnSC_MSA(0u)| TPM_CnSC_MSB(1u) | TPM_CnSC_ELSA(0u) | TPM_CnSC_ELSB(1u);

	TPM1_CNT = 0u;
	TPM1_MOD = 26660u;



}


void motor_setPWM(unsigned int uiVelDir,unsigned int uiVelEsq){
	TPM1_C1V = TPM_CnV_VAL(uiVelDir);
	TPM1_C0V = TPM_CnV_VAL(uiVelEsq);
}



/* ************************************************ */
/* Method name:        timer_coolerfan_init         */
/* Method description: Initialize the cooler device */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void motor_init(void)
{
    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);

    /* set pin as gpio */
    PORTA_PCR1 = PORT_PCR_MUX(IN1_ALT);
    PORTA_PCR2 = PORT_PCR_MUX(IN2_ALT);

    /* set pin as digital output */
    GPIOA_PDDR |= GPIO_PDDR_PDD(IN1_DIR_OUTPUT);
    GPIOA_PDDR |= GPIO_PDDR_PDD(IN2_DIR_OUTPUT);

    GPIOA_PSOR = GPIO_PSOR_PTSO( (0U << IN1_PIN) );
    GPIOA_PSOR = GPIO_PSOR_PTSO( (0U << IN2_PIN) );

    PORTA_PCR12 |= PORT_PCR_MUX(3u); // motor esquerdo
    PORTA_PCR13 |= PORT_PCR_MUX(3u); // motor direito

}

