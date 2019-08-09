/*
 * light.c
 *
 *  Created on: Apr 24, 2019
 *      Author: joel
 */



#include <heartbeat.h>
#include "ti/devices/msp432p4xx/driverlib/gpio.h"
#include <ti/drivers/GPIO.h>

#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"

#include "Board.h"

pthread_t        heartbeat_handler;

void *heartbeat(void *arg0){

    const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(1, 1 << 0); // port 1 shifted by the pin number (0)

    while(1)
    {
        GPIO_toggleOutputOnPin(1, 1 << 0);// (shifted by pin number (0))
        vTaskDelay(xDelay);
    }

}
