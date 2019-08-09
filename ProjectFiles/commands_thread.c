/*
 * commands_thread.c
 *
 *  Created on: Apr 24, 2019
 *      Author: joel
 */

/* Includes */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

/* POSIX Header Files */
#include <semaphore.h>

/* Driver Header Files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>

/* Board Header Files */
#include "Board.h"

/* Local Header Files */
#include "callbacks.h"
#include "led_thread.h"
#include "uart_thread.h"

void *commandsThread(void *arg0)
{

}
