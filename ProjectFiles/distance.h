/*
 * distance.h
 *
 *  Created on: Apr 26, 2019
 *      Author: joel
 */
#include <pthread.h>

#include <ti/drivers/ADC.h>
#include <ti/drivers/ADC/ADCMSP432.h>
#include <ti/drivers/UART.h>

extern UART_Handle uart_handle;

#ifndef DISTANCE_H_
#define DISTANCE_H_
extern pthread_t        distance_handler;



extern void *distance(void *arg0);


#endif /* DISTANCE_H_ */
