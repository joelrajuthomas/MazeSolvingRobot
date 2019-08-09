/*
 * distance.c
 *
 *  Created on: Apr 26, 2019
 *      Author: joel
 */


#include <distance.h>
#include "ti/devices/msp432p4xx/driverlib/gpio.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "uart_thread.h"

#include <ti/drivers/ADC.h>
#include <ti/drivers/PWM.h>
#include <ti/drivers/ADC/ADCMSP432.h>


#include <ti/drivers/GPIO.h>


#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"

#include "Board.h"

/* Standard Includes */
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

pthread_t        distance_handler;

ADC_Handle adc0;
ADC_Handle adc1;
ADC_Handle bottom;

char buffer[20];
void ADCinitialize()
{
    ADC_init();
    ADC_Params ADCparameter;
    ADCparameter.isProtected = false;
    adc0 = NULL;
    adc1 = NULL;
    bottom = NULL;
    adc0 = ADC_open(Board_ADC9, &ADCparameter); //this is pin 4.4 on MSP
    adc1 = ADC_open(Board_ADC10, &ADCparameter); //this is pin 4.3
    bottom = ADC_open(Board_ADC14, &ADCparameter); //pin 6.1
    sprintf (buffer, "%d\n\r", adc0);
    putString(buffer);
    sprintf (buffer, "%d\n\r", adc1);
    putString(buffer);
    sprintf (buffer, "%d\n\r", bottom);
    putString(buffer);
//should give value ~30000 if working

}


void timerINIT(){

//        Timer_Params_init(&timer_params);
//       timer_params.period = ledTogglePeriods[currentColorMode];
//       timer_params.periodUnits = Timer_PERIOD_US;
//       timer_params.timerMode = Timer_CONTINUOUS_CALLBACK;
//       timer_params.timerCallback = blinkTimer_Callback;
//       blinkTimer = Timer_open(Board_TIMER1, &timer_params);
//       if (blinkTimer == NULL) {
//          /* Failed to initialized Timer */
//          while(1);
//       }
//       Timer_start(blinkTimer);

}



//uint16_t ADCVal0;
//uint16_t ADCVal1;
uint_fast16_t ADCVal0;
uint_fast16_t ADCVal1;

uint_fast16_t ADCbottom;

int_fast16_t res;
int_fast16_t res2;

int_fast16_t resbottom;


const TickType_t xDelay = 200 / portTICK_PERIOD_MS;


void *distance(void *arg0){

    ADCinitialize();



    while(1)
    {
        res = ADC_convert(adc0, &ADCVal0);
        res2 = ADC_convert(adc1, &ADCVal1);
        resbottom = ADC_convert(bottom, &ADCbottom);

        vTaskDelay(xDelay);
        if (res == ADC_STATUS_SUCCESS) { //front sensor reading
            //use adcValue
            sprintf (buffer, "\n\rfront: %d\n\r", ADCVal0);
            putString(buffer);
        }

        if (res2 == ADC_STATUS_SUCCESS) {
                    //use adcValue
            sprintf (buffer, "right: %d\n\r", ADCVal1);
            putString(buffer);
         }
        vTaskDelay(xDelay);
        if (resbottom == ADC_STATUS_SUCCESS) {
                            //use adcValue
                    sprintf (buffer, "\n\rbottom: %d\n\r", ADCbottom);
                    putString(buffer);
         }



        //UART_write(uart_handle, ADCVal1, 7);
    }

}
