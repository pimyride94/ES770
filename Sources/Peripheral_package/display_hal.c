/* ***************************************************************** */
/* File name:        display_hal.c                                   */
/* File description: Configure 4 7segments display.		     		 */
/*                   												 */
/* Authors names:    Paulo Lage, Frederic Devloo                     */
/* Creation date:    26mar2018                                       */
/* Revision date:    02abr2018                                       */
/* ***************************************************************** */


#include "ledswi_hal.h"
#include "KL25Z/es670_peripheral_board.h"

#define USING_OPENSDA_DEBUG



void disp_initDSP(void)
{
    /* un-gate port clock*/
    SIM_SCGC5 |= SIM_SCGC5_PORTC(CGC_CLOCK_ENABLED);

    /* set pin as gpio */
    PORTC_PCR0 = PORT_PCR_MUX(DSPA_ALT);
    PORTC_PCR1 = PORT_PCR_MUX(DSPB_ALT);
    PORTC_PCR2 = PORT_PCR_MUX(DSPC_ALT);
    PORTC_PCR3 = PORT_PCR_MUX(DSPD_ALT);
    PORTC_PCR4 = PORT_PCR_MUX(DSPE_ALT);
    PORTC_PCR5 = PORT_PCR_MUX(DSPF_ALT);
    PORTC_PCR6 = PORT_PCR_MUX(DSPG_ALT);
    PORTC_PCR7 = PORT_PCR_MUX(DSPDP_ALT);

    PORTC_PCR13 = PORT_PCR_MUX(DSP1_ALT);
    PORTC_PCR12 = PORT_PCR_MUX(DSP2_ALT);
    PORTC_PCR11 = PORT_PCR_MUX(DSP3_ALT);
    PORTC_PCR10 = PORT_PCR_MUX(DSP4_ALT);

    /* inicializa os registradores para cada pino */
    GPIOC_PDDR |= GPIO_PDDR_PDD(DSPA_DIR_OUTPUT | DSPB_DIR_OUTPUT | DSPC_DIR_OUTPUT | DSPD_DIR_OUTPUT | DSPE_DIR_OUTPUT | DSPF_DIR_OUTPUT | DSPG_DIR_OUTPUT | DSPDP_DIR_OUTPUT | DSP1_DIR_OUTPUT | DSP2_DIR_OUTPUT | DSP3_DIR_OUTPUT | DSP4_DIR_OUTPUT);

}

void seg7_clear(void){
		GPIOC_PCOR |= GPIO_PCOR_PTCO( (0x01U << DSPA_PIN) );
		GPIOC_PCOR |= GPIO_PCOR_PTCO( (0x01U << DSPB_PIN) );
		GPIOC_PCOR |= GPIO_PCOR_PTCO( (0x01U << DSPC_PIN) );
		GPIOC_PCOR |= GPIO_PCOR_PTCO( (0x01U << DSPD_PIN) );
		GPIOC_PCOR |= GPIO_PCOR_PTCO( (0x01U << DSPE_PIN) );
		GPIOC_PCOR |= GPIO_PCOR_PTCO( (0x01U << DSPF_PIN) );
		GPIOC_PCOR |= GPIO_PCOR_PTCO( (0x01U << DSPG_PIN) );
		GPIOC_PCOR |= GPIO_PCOR_PTCO( (0x01U << DSPDP_PIN) );
		GPIOC_PCOR |= GPIO_PCOR_PTCO( (0x01U << DSP1_PIN) );
		GPIOC_PCOR |= GPIO_PCOR_PTCO( (0x01U << DSP2_PIN) );
		GPIOC_PCOR |= GPIO_PCOR_PTCO( (0x01U << DSP3_PIN) );
		GPIOC_PCOR |= GPIO_PCOR_PTCO( (0x01U << DSP4_PIN) );

}




void disp_setDSP(char dispNum, char dispSeg){

	seg7_clear();
	switch(dispSeg){
		case 1:
			GPIOC_PSOR = GPIO_PSOR_PTSO((0x01U << DSP1_PIN));
			break;
		case 2:
			GPIOC_PSOR = GPIO_PSOR_PTSO((0x01U << DSP2_PIN));
			break;
		case 3:
			GPIOC_PSOR = GPIO_PSOR_PTSO((0x01U << DSP3_PIN));
			break;
		case 4:
			GPIOC_PSOR = GPIO_PSOR_PTSO((0x01U << DSP4_PIN));
			break;
		default:
			break;
	}

	switch(dispNum){
		case 1:
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPB_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPC_PIN));
			break;
		case 2:
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPA_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPB_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPD_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPE_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPG_PIN));
			break;
		case 3:
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPA_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPB_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPD_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPC_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPG_PIN));
			break;
		case 4:
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPF_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPG_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPB_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPC_PIN));
			break;

		case 5:
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPA_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPF_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPG_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPC_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPD_PIN));
			break;

		case 6:
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPA_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPF_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPE_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPD_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPC_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPG_PIN));
			break;
		case 7:
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPA_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPB_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPC_PIN));
			break;

		case 8:
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPA_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPB_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPC_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPD_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPE_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPF_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPG_PIN));
			break;
		case 9:
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPA_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPB_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPG_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPF_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPC_PIN));
			break;
		case 0:
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPA_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPB_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPC_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPD_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPE_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPF_PIN));
			break;
		case 'b':
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPC_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPD_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPE_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPF_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPG_PIN));
			break;
		case 'e':
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPA_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPD_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPE_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPF_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPG_PIN));
			break;
		case 'a':
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPA_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPB_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPC_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPE_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPF_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPG_PIN));
			break;
		case 'h':
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPB_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPC_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPE_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPF_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPG_PIN));
			break;
		case 'r':
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPE_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPG_PIN));
			break;
		case 'o':
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPA_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPB_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPC_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPD_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPE_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPF_PIN));
			GPIOC_PSOR |= GPIO_PSOR_PTSO((0x01U << DSPDP_PIN));
			break;
		default:
			break;
	}

}












