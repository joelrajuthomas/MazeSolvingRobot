/*
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== uart_thread.c ========
 */

/* Includes */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "ti/devices/msp432p4xx/driverlib/gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"

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

/* Global Variables */
volatile int bytesReceived = 7;     // Keeps track of # UART bytes received
volatile char start[5];             // Receives 'START' keyword
volatile int ack = 0;               // Track acknowledgment sent to GUI
volatile int32_t receiveFreq = 0;   // Receives LED blink frequency from GUI
char receiveByte, ackByte = 'A';


pthread_t uartthread_handler;

/*
 *  ======== mainThread ========
 */
void UartInit(){

        UART_Params uartParams;
    /* Define UART parameters*/
        UART_Params_init(&uartParams);
        uartParams.writeDataMode = UART_DATA_BINARY;
        uartParams.readDataMode = UART_DATA_BINARY;
        uartParams.readReturnMode = UART_RETURN_FULL;
        uartParams.readEcho = UART_ECHO_OFF;
        uartParams.baudRate = 115200;

        uart_handle = UART_open(Board_UART1, &uartParams);
}

void runcmd(char *cmd)
{
    if (strcmp(cmd, "red") == 0)
    {
        GPIO_toggleOutputOnPin(2, 1 << 0);
        putString("\r\n");
        UART_write(uart_handle, "toggling red", 13);
    } else if(strcmp(cmd, "blue") == 0) {
        GPIO_toggleOutputOnPin(2, 1 << 2);
        putString("\r\n");
        UART_write(uart_handle, "toggling blue", 14);
    } else if(strcmp(cmd, "green") == 0){
        GPIO_toggleOutputOnPin(2, 1 << 1);
        putString("\r\n");
        UART_write(uart_handle, "toggling green", 15);
    }
//    else if(strcmp(cmd, "distance") == 0){
//
//    }


}

void getChar(char *out){
    UART_read(uart_handle, out, 1);
}

void putChar(char input){
    UART_write(uart_handle, &input, 1);
}

int length(char *string){
    int i = 0;
    while(string[i] != '\0')
    {
        i++;
    }
    return i;
}

void putString(char *string){
    UART_write(uart_handle, string, length(string));
}

void *uartThread(void *arg0)
{
    LedMsg msg;
    int rc;
    int32_t receiveByteArray[4] = {-1, -1, -1, -1};

    /* Call driver init functions */
    GPIO_init();
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setOutputLowOnPin(2, 1 << 0); // port 1 shifted by the pin number (0)

    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setOutputLowOnPin(2, 1 << 1); // port 1 shifted by the pin number (0)

    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2);
    GPIO_setOutputLowOnPin(2, 1 << 2); // port 1 shifted by the pin number (0)


    Timer_init();

    if (uart_handle == NULL) {
        /* UART_open() failed */
        while (1);
    }

    char input;
    int i;
    char in[11];


    while (1) //this while loop controls showing our typing in serial terminal and stores it in string 'in' for the ""switch case""
    {
        i=-1;
        putString("\r\n");
        do{
            getChar(&input);
            putChar(input);
            if(input == '\b' && i >= 0) {
                putString('\b');
                i--;
            } else if (input == '\b'){
                i = -1;
            } else {
                i++;
                in[i] = input;
            }
        }while(input != '\r' && i < 10);
        in[i] = '\0';

        runcmd(in); //starts my "switch case for commands"
    }


        /* Receive/Set color and frequency of LED */


}
