#ifndef SOURCES_MOTORPWM_H_
#define SOURCES_MOTORPWM_H_


#define IN1_PIN                     1U
#define IN1_DIR_OUTPUT              (GPIO_OUTPUT << IN1_PIN)
#define IN1_ALT                     0x01u

#define IN2_PIN                     2U
#define IN2_DIR_OUTPUT              (GPIO_OUTPUT << IN2_PIN)
#define IN2_ALT                     0x01u

void init_motorEsquerdo_TPM1AsPWM(void);

void motor_setPWM(unsigned int uiVelDir,unsigned int uiVelEsq);

void motor_init(void);


#endif /* SOURCES_ADC_H_ */
