#ifndef __print_scan_h__
#define __print_scan_h__

#include <stdio.h>
#include "../Controller_Package/pid.h"

typedef enum state {INIT, L, S, B, LS, LC, B1, B2, P, P1, P2, H, H1, G, GI, GI1, GI2, GI3, GP, GP1, GP2, GP3, GD, GD1, GD2, GD3} State;

void cmd_interpretCMD(State stateActual, char cCmd, PID_DATA *pidData);

State cmd_machine(State stateCurr, char cCmd, PID_DATA *pidData);

void cmd_commandAceptted(void);

void cmd_commandError(void);

void cmd_ledswi_clearAndInnitedAllLed(void);

#endif /* SOURCES_CMDMACHINE_HAL_H_ */
