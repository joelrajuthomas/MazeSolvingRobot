/*
 * motors.c
 *
 *  Created on: Apr 24, 2019
 *      Author: joel
 */


#include <MOTORS.h>
#include "ti/devices/msp432p4xx/driverlib/gpio.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "uart_thread.h"
#include <ti/drivers/ADC.h>
#include <ti/drivers/PWM.h>
#include <ti/drivers/pwm/PWMTimerMSP432.h>
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

pthread_t        motor_handler;
char buffer[20];

void pwminitialize()
{

      PWM_Handle pwm;
      PWM_Handle pwm2;
      PWM_Params pwmParams;
      uint32_t   dutyValue;

      // Initialize the PWM driver.
      PWM_init();

      // Initialize the PWM parameters
      PWM_Params_init(&pwmParams);
      pwmParams.idleLevel = PWM_IDLE_LOW;      // Output low when PWM is not running
      pwmParams.periodUnits = PWM_PERIOD_HZ;   // Period is in Hz
      pwmParams.periodValue = 1e6;             // 1MHz
      pwmParams.dutyUnits = PWM_DUTY_FRACTION; // Duty is in fractional percentage
      pwmParams.dutyValue = 0;                 // 0% initial duty cycle

      // Open the PWM instance
      pwm = PWM_open(Board_PWM0, &pwmParams);
      pwm2 = PWM_open(Board_PWM1, &pwmParams);


      if (pwm == NULL) {
          // this means our pin didnt open
          while (1);
      }
//      sprintf (buffer, "%d\n\r", adc0);
//      putString(buffer);

      PWM_start(pwm);                          // start PWM with 0% duty cycle
      sprintf (buffer, "%d\n\r", pwm);
      putString(buffer);


      dutyValue = (uint32_t) (((uint64_t) PWM_DUTY_FRACTION_MAX * 37) / 100);
      PWM_setDuty(pwm, dutyValue);  // set duty cycle to 37%

      //pwmParams.idleLevel = PWM_IDLE_HIGH;

}

void *motors(void *arg0)
{
    pwminitialize();

    while(1)
    {

    }
}
