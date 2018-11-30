/* ***************************************************************** */
/* File name:        display_hal.c                                   */
/* File description: Configure 4 7segments display.		     		 */
/*                   												 */
/* Authors names:    Paulo Lage, Frederic Devloo                     */
/* Creation date:    26mar2018                                       */
/* Revision date:    02abr2018                                       */
/* ***************************************************************** */


#include "cooler_hal.h"
#include "../KL25Z/es670_peripheral_board.h"



void cooler_init(void){
    /* un-gate port clock*/
	SIM_SCGC5 |= SIM_SCGC5_PORTA(CGC_CLOCK_ENABLED);

    /* set pin as gpio */
    PORTA_PCR13 = PORT_PCR_MUX(COOLER_DATA_ALT);


    /* inicializa os registradores para cada pino */
    GPIOA_PDDR |= GPIO_PDDR_PDD(COOLER_DATA_DIR);
}

void cooler_setMax(void){
	GPIOA_PSOR = GPIO_PSOR_PTSO( (0x01U << COOLER_DATA_PIN) );
}
