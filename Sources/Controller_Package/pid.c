/*
 * pid.c
 *
 *  Created on: 18/06/2018
 *      Author: aluno
 */

#include "KL25Z/es670_peripheral_board.h"
#include "pid.h"
#include "Timer_Package/mcg_hal.h"
#include "Timer_Package/util.h"
#include "Peripheral_package/timer_counter.h"


double pidControl(PID_DATA *pidData, double actualValue, double refValue, double maxValue){

	double auxP, auxI, auxD;
	double err, diff, temp;

	if(refValue>maxValue) refValue=maxValue;
	err = refValue - actualValue;
	auxP = pidData->pGain*err;
	pidData->errSum += err;
	auxI = pidData->iGain*pidData->errSum;
	diff = pidData->preValue - actualValue;
	pidData->preValue = actualValue;
	auxD = pidData->dGain*diff;
	if(pidData->preValue==actualValue) auxD=0;
	temp = auxP+auxD+auxI;

	//if(temp<=0) temp=0;


	return(temp);


}





void pid_init(PID_DATA *pidData){
	int i=0;
	pidData->pGain=40;
	pidData->dGain=9;
	pidData->iGain=0;
	pidData->preValue=0;
	pidData->errSum=0;

	for(i=1;i<=10000;i++){
		util_genDelay10ms;
	}

}
