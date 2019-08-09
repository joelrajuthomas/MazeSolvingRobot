/*
 * commands_thread.h
 *
 *  Created on: Apr 24, 2019
 *      Author: joel
 */
/*
 *  ======== uart_thread.h ========
 */

/* POSIX Header files */
#include <pthread.h>

#include <ti/drivers/UART.h>

#ifndef COMMANDS_THREAD_H_
#define COMMANDS_THREAD_H_

extern pthread_t           uartthread_handler;
extern void *commandsThread(void *arg0);




#endif /* COMMANDS_THREAD_H_ */
