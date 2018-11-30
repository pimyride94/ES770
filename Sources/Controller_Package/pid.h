/*
 * pid.h
 *
 *  Created on: 18/06/2018
 *      Author: aluno
 */


#ifndef SOURCES_CONTROLLER_PACKAGE_PID_H_
#define SOURCES_CONTROLLER_PACKAGE_PID_H_

typedef struct PID_DATA{
	double pGain;
	double dGain;
	double iGain;
	double preValue;
	double errSum;
	double ref;
}PID_DATA;

double pidControl(PID_DATA *pidData, double actualValue, double refValue, double maxValue);
void pid_init(PID_DATA *pidData);

#endif /* SOURCES_CONTROLLER_PACKAGE_PID_H_ */
