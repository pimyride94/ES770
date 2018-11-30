/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


/* ***************************************************************** */
/* File name:        main.c                                          */
/* File description: This is the main function of lab01.		     */
/*                   												 */
/* Authors names:    Paulo Lage, Frederic Devloo                     */
/* Creation date:    26mar2018                                       */
/* Revision date:    13abr2018                                       */
/* ***************************************************************** */



#include "Timer_Package/mcg_hal.h"
#include "Timer_Package/util.h"
#include "KL25Z/es670_peripheral_board.h"
#include "Peripheral_package/buzzer_hal.h"
#include "Peripheral_package/ledswi_hal.h"
#include "Peripheral_package/display_hal.h"
#include "Debug_Package/debugUart.h"
#include "Peripheral_package/lcd_hal.h"
#include "Peripheral_package/tc_hal.h"
#include "Peripheral_package/cooler_hal.h"
#include "Peripheral_package/timer_counter.h"
#include "State_Package/cmdmachine_hal.h"
#include "Heater/timer.h"
#include "Heater/adc.h"
#include "Controller_Package/pid.h"
#include "Controller_Package/pid.h"

#include "Motor/motorPWM.h"
#include "Sensores_Linha/adc.h"

/* system includes */
#include "fsl_debug_console.h"
#include "fsl_device_registers.h"
#include <stdint.h>
#include <stdio.h>
#include "fsl_os_abstraction.h"


/* defines */
#define CYCLIC_EXECUTIVE_PERIOD         1000 * 30/// 100 /* 1000000 micro seconds */


/* globals */
volatile unsigned int uiFlagNextPeriod = 0;         /* cyclic executive flag */




/* ************************************************ */
/* Method name:        main_cyclicExecuteIsr        */
/* Method description: cyclic executive interrupt   */
/*                     service routine              */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void main_cyclicExecuteIsr(void)
{
    /* set the cyclic executive flag */
    uiFlagNextPeriod = 1;
}


int main(void){

	double valores[5];
	double val_sensor[5];
	double pond;
	double delta_vel;
	int teste;
	int i, j=0;
	double velDir,velEsq, retorno;
	uint8_t *maxval[5];
	CAL_SENSOR coco;
	PID_DATA pidData1;

	mcg_clockInit();
	adc_init(_8BIT);
	init_calib(&coco);

	motor_init();

	calib(&coco);

	init_motorEsquerdo_TPM1AsPWM();

	pid_init(&pidData1);

	tc_installLptmr0(CYCLIC_EXECUTIVE_PERIOD, main_cyclicExecuteIsr);


	while(1u){
		/* WAIT FOR CYCLIC EXECUTIVE PERIOD */
		val_sensor[0]= adc_read(ADC_0);
		val_sensor[1]= adc_read(ADC_1);
		val_sensor[2]= adc_read(ADC_2);
		val_sensor[3]= adc_read(ADC_3);
		val_sensor[4]= adc_read(ADC_4);

		//Incremento da variavel j a cada vez q os 5 sensores estao sobre a linha branca
		if(val_sensor[0]<3 && val_sensor[1]<3 && val_sensor[2]<3 && val_sensor[3]<3 && val_sensor[4]<3) j++;

		//Valor medido foi em torno de 380 somando todos cruzamentos e a passagem da primeira vez
		if(j>400){
			motor_setPWM(0,0);
			while(1==1);
		}

		//Normaliza o valor dos sensores de 0-100
		for(i=0;i<5;i++){
			if(val_sensor[i]>coco.maxVal[i]) val_sensor[i]=coco.maxVal[i];
			valores[i]=(val_sensor[i]/coco.maxVal[i])*100;
		}

		//Pondera o valor dos sensores para saber onde esta a linha
		pond = (valores[2]*0 + valores[1]*(-1) + valores[0]*(-2) + valores[3]*1 +valores[4]*2)/(valores[2] + valores[1] + valores[0] + valores[3] +valores[4]);

		//Chamada do controlador
		retorno = pidControl(&pidData1, pond, 0, 100000);

		//Multiplica por 1000 para ajustar para o valor de TPM1_MOD (26600 representa 100% de Duty Cycle)
		delta_vel=retorno*1000;

		//Transforma pra inteiro
		teste = (int)delta_vel;

		//Como cada roda esta com um torque diferente, os valores de Duty Cycle pra mesma velocidade sao diferentes
		velEsq = 10000-teste;
		if(velEsq<0) velEsq=0;

		velDir = 14000+teste;
		if(velDir<0) velDir=0;

		//Seta o motor
		motor_setPWM(velEsq,velDir);


		while(!uiFlagNextPeriod);
			uiFlagNextPeriod = 0;

	}
	return 0;
}



////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
