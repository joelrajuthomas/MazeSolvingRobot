/*
 * motors.h
 *
 *  Created on: Apr 24, 2019
 *      Author: joel
 */
#include <pthread.h>

#include <ti/drivers/UART.h>
#include <ti/drivers/ADC.h>
#include <ti/drivers/PWM.h>
#include <ti/drivers/pwm/PWMTimerMSP432.h>
#include <ti/drivers/ADC/ADCMSP432.h>
#include <ti/drivers/UART.h>

extern UART_Handle uart_handle;

#ifndef ADC_THREAD_H_
#define ADC_THREAD_H_



extern pthread_t        motor_handler;



extern void *motors(void *arg0);



#endif /* ADC_THREAD_H_ */
