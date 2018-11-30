
#include "cmdmachine_hal.h"
#include <stdio.h>
#include "../Peripheral_package/timer_counter.h"
#include "fsl_device_registers.h"
#include "../Timer_Package/mcg_hal.h"
#include "../Timer_Package/util.h"
#include "../KL25Z/es670_peripheral_board.h"
#include "../Peripheral_package/buzzer_hal.h"
#include "../Peripheral_package/ledswi_hal.h"
#include "../Peripheral_package/display_hal.h"
#include "../Debug_Package/debugUart.h"
#include "../Peripheral_package/lcd_hal.h"
#include "../Heater/adc.h"
#include "../Heater/timer.h"
#include "../Controller_Package/pid.h"
#include "../Peripheral_package/tc_hal.h"

//System Includes
#include "fsl_debug_console.h"
#include "fsl_device_registers.h"
#include <stdint.h>
#include <stdio.h>
#include "fsl_os_abstraction.h"


#define MAX 4
//typedef enum state {INIT, L, S, B, LS, LC, B1, B2, B3, H} State;
int buzzNum=0;
int heatNum=0;
double coolerNum;
double pidI;
double pidD;
double pidP;
double dTest=1.001;



void cmd_interpretCMD(State stateActual, char cCmd, PID_DATA *pidData){

	double TEMP;
	static unsigned int uiLedsSave[MAX];
	int iCont=0;

	if(S == stateActual){
		ledswi_initLedSwitch(0,4);
		if(SWITCH_ON==ledswi_getSwitchStatus(cCmd)){

			PUTCHAR('R');
			PUTCHAR('C');

		}
		else{

			PUTCHAR('R');
			PUTCHAR('O');

		}
		ledswi_initLedSwitch(4,0);
		while(0!=uiLedsSave[iCont] && MAX>iCont ){
			ledswi_setLed(iCont);
			iCont++;
		}
	}
	else if(LS == stateActual){
		ledswi_initLedSwitch(4,0);
		ledswi_setLed(cCmd);
		uiLedsSave[cCmd]=1;

	}
	else if(LC == stateActual){
		ledswi_initLedSwitch(4,0);
		ledswi_clearLed(cCmd);
		uiLedsSave[cCmd]=0;
//	}else if(B3 == stateActual){

	}
	else if(P2 == stateActual){
//		if(0 == cCmd) timer_coolerfan_setPWM(0);
//		else if(1 == cCmd) timer_coolerfan_setPWM(25);
//		else if(2 == cCmd) timer_coolerfan_setPWM(50);
//		else if(3 == cCmd) timer_coolerfan_setPWM(75);
//		else if(4 == cCmd) timer_coolerfan_setPWM(100);
//		timer_coolerfan_setPWM(cCmd);
		pidData->ref = coolerNum;
	}
	else if(H1 == stateActual){
//		if(0 == cCmd) timer_changeHeaterPwm(0);
//		else if(1 == cCmd) timer_changeHeaterPwm(25);
//		else if(2 == cCmd) timer_changeHeaterPwm(50);
//		else if(3 == cCmd) timer_changeHeaterPwm(75);
//		else if(4 == cCmd) timer_changeHeaterPwm(100);
		timer_changeHeaterPwm(cCmd);
	}
	else if(GD3 == stateActual){
		TEMP= pidD;
		pidData->dGain = pidD;
	}

	else if(GP3 == stateActual){
		pidData->pGain = pidP;
	}

	else if(GI3 == stateActual){
		pidData->iGain = pidI;
	}


}

State cmd_machine(State stateCurr, char cCmd,PID_DATA *pidData){
	
	double TEMP;
	switch (stateCurr){
		case INIT:
			if('L'==cCmd) return L;
			else if('S'==cCmd) return S;
			else if('B'==cCmd) return B;
			else if('P'==cCmd) return P;
			else if('H'==cCmd) return H;
			else if('G'==cCmd) return G;
			else{
				cmd_commandError();
				return INIT;
			}
			
		case L:
			if('S'==cCmd) return LS;
			else if('C'==cCmd) return LC;
			else{
				cmd_commandError();
				return INIT;
			}
			
		case S:
			cCmd= cCmd - 48;
			if(0<cCmd && 5>cCmd){
				cmd_commandAceptted();
				cmd_interpretCMD(stateCurr, cCmd, pidData);
			}

			else cmd_commandError();
			
			return INIT;

		case LS:
			cCmd= cCmd - 48;
			if(0<cCmd && 5>cCmd){
				cmd_commandAceptted();
				cmd_interpretCMD(stateCurr, cCmd, pidData);
			}
			else cmd_commandError();

			return INIT;
			
		case LC:
			cCmd= cCmd - 48;
			if(0<cCmd && 5>cCmd){
				cmd_commandAceptted();
				cmd_interpretCMD(stateCurr, cCmd, pidData);
			}
			else cmd_commandError();

			return INIT;
			
		case B:
			cCmd= cCmd - 48;
			if(0<=cCmd && 9>=cCmd){
				buzzNum= cCmd*100;
				return B1;
			}
			else{
				buzzNum=0;
				cmd_commandError();
				return INIT;
			}
			
		case B1:
			cCmd= cCmd - 48;
			if(0<=cCmd && 9>=cCmd){
				buzzNum= buzzNum + cCmd*10;
				return B2;
			}
			else{
				buzzNum=0;
				cmd_commandError();
				return INIT;
			}
			
		case B2:
			cCmd= cCmd - 48;
			if(0<=cCmd && 9>=cCmd){
				buzzNum= buzzNum + cCmd;
				cmd_commandAceptted();
				cmd_interpretCMD(stateCurr, buzzNum, pidData);
				return INIT;
			}
			else{
				buzzNum=0;
				cmd_commandError();
				return INIT;
			}
			
		case P:
			cCmd= cCmd - 48;
			if(0<=cCmd && 1>=cCmd){
				coolerNum = cCmd*100;
				return P1;
			}
			else{
				cmd_commandError();
				return INIT;
			}
		case P1:
			cCmd= cCmd - 48;
			if(0<=cCmd && 9>=cCmd && coolerNum!=100){
				coolerNum = coolerNum + cCmd*10;
				return P2;
			}
			else if(coolerNum==100 && cCmd==0){
				return P2;
			}
			else{
				cmd_commandError();
				coolerNum=0;
				return INIT;
			}
		case P2:
			cCmd= cCmd - 48;
			if(0<=cCmd && 9>=cCmd && coolerNum!=100){
				coolerNum = coolerNum + cCmd;

				cmd_commandAceptted();
				cmd_interpretCMD(stateCurr, coolerNum, pidData);
				coolerNum=0;
				return INIT;
			}
			else if(coolerNum==100 && cCmd==0){
				cmd_commandAceptted();
				cmd_interpretCMD(stateCurr, coolerNum, pidData);
				coolerNum=0;
				return INIT;
			}
			else{
				cmd_commandError();
				coolerNum=0;
				return INIT;
			}
		case H:
			cCmd= cCmd - 48;
			if(0<=cCmd && 5>=cCmd){
				heatNum = cCmd*10;
				return H1;
			}
			else{
				cmd_commandError();
				return INIT;
			}
		case H1:
			cCmd= cCmd - 48;
			if(0<=cCmd && 9>=cCmd && heatNum!=50){
				cmd_commandAceptted();
				heatNum = heatNum + cCmd;
				cmd_interpretCMD(stateCurr, heatNum, pidData);
				heatNum=0;
				return INIT;
			}
			else if(heatNum==50 && cCmd==0){
				cmd_commandAceptted();
				cmd_interpretCMD(stateCurr, heatNum, pidData);
				heatNum=0;
				return INIT;
			}
			else{
				cmd_commandError();
				heatNum=0;
				return INIT;
			}
		case G:
			if('I'==cCmd) return GI;
			if('D'==cCmd) return GD;
			if('P'==cCmd) return GP;
			else{
				cmd_commandError();
				return INIT;
			}
		case GI:
			cCmd= cCmd - 48;
			if(0<=cCmd && 9>=cCmd){
				pidI = cCmd;
				return GI1;
			}
			else{
				cmd_commandError();
				return INIT;
			}
		case GI1:
			cCmd= cCmd - 48;
			if(0<=cCmd && 9>=cCmd){
				pidI = pidI + cCmd/10;
				return GI2;
			}
			else{
				cmd_commandError();
				pidI = 0;
				return INIT;
			}
		case GI2:
			cCmd= cCmd - 48;
			if(0<=cCmd && 9>=cCmd){
				pidI = pidI + cCmd/100;
				return GI3;
			}
			else{
				cmd_commandError();
				pidI = 0;
				return INIT;
			}
		case GI3:
			cCmd= cCmd - 48;
			if(0<=cCmd && 9>=cCmd){
				cmd_commandAceptted();
				pidI = pidI + cCmd/1000;
				cmd_interpretCMD(stateCurr, (char)pidI, pidData);
				return INIT;
			}
			else{
				cmd_commandError();
				pidI = 0;
				return INIT;
			}

		case GP:
			cCmd= cCmd - 48;
			if(0<=cCmd && 9>=cCmd){
				pidP = cCmd;
				return GP1;
			}
			else{
				cmd_commandError();
				return INIT;
			}
		case GP1:
			cCmd= cCmd - 48;
			if(0<=cCmd && 9>=cCmd){
				pidP = pidP + cCmd/10.0;
				return GP2;
			}
			else{
				cmd_commandError();
				pidP = 0;
				return INIT;
			}
		case GP2:
			cCmd= cCmd - 48;
			if(0<=cCmd && 9>=cCmd){
				pidP = pidP + cCmd/100.0;
				return GP3;
			}
			else{
				cmd_commandError();
				pidP = 0;
				return INIT;
			}
		case GP3:
			cCmd= cCmd - 48;
			if(0<=cCmd && 9>=cCmd){
				cmd_commandAceptted();
				pidP = pidP + cCmd/1000.0;
				cmd_interpretCMD(stateCurr, (char)pidP, pidData);
				return INIT;
			}
			else{
				cmd_commandError();
				pidP = 0;
				return INIT;
			}

		case GD:
			cCmd= cCmd - 48;
			if(0<=cCmd && 9>=cCmd){
				pidD = (double)cCmd;
				return GD1;
			}
			else{
				cmd_commandError();
				return INIT;
			}
		case GD1:
			cCmd= cCmd - 48;
			if(0<=cCmd && 9>=cCmd){
				TEMP=(cCmd/10.0);
				pidD = pidD + TEMP;
				return GD2;
			}
			else{
				cmd_commandError();
				pidD = 0;
				return INIT;
			}
		case GD2:
			cCmd= cCmd - 48;
			if(0<=cCmd && 9>=cCmd){
				TEMP=cCmd/100.0;
				pidD = pidD + TEMP;
				return GD3;
			}
			else{
				cmd_commandError();
				pidD = 0;
				return INIT;
			}
		case GD3:
			cCmd= cCmd - 48;
			if(0<=cCmd && 9>=cCmd){
				cmd_commandAceptted();
				TEMP=cCmd/1000.0;
				pidD = pidD + TEMP;
				TEMP=pidD;
				cmd_interpretCMD(stateCurr, (char)pidD, pidData);
				return INIT;
			}
			else{
				cmd_commandError();
				pidD = 0;
				return INIT;
			}
	}
	
	//return INIT;

}

void cmd_commandAceptted(void){
	debugUart_init();
	PUTCHAR('A');
	PUTCHAR('C');
	PUTCHAR('K');

	return;
}

void cmd_commandError(void){
	debugUart_init();
	PUTCHAR('E');
	PUTCHAR('R');
	PUTCHAR('R');

	return;
}

void cmd_ledswi_clearAndInnitedAllLed(void){
	debugUart_init();
	ledswi_initLedSwitch(4,0);
	ledswi_clearLed(1);
	ledswi_clearLed(2);
	ledswi_clearLed(3);
	ledswi_clearLed(4);

	return;
}

void cmd_putStringSerial(char sWord[]){
	int iCont;
	for(iCont=0;iCont<15;iCont++){
		PUTCHAR(sWord[iCont]);
	}
	PUTCHAR(13);
	PUTCHAR(10);
}

