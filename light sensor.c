

// BIOS header files
//----------------------------------------
//#include <xdc/std.h>                        //mandatory - have to include first, for BIOS types
//#include <ti/sysbios/BIOS.h>                //mandatory - if you call APIs like BIOS_start()
//#include <xdc/runtime/Log.h>                //needed for any Log_info() call
//#include <xdc/cfg/global.h>                 //header file for statically defined objects/handles
//Header Files
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "inttypes.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/adc.h"

double charge1 = 0.0;
double charge2 = 0.0;

int main(void)
{
        SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
        uint32_t ui32ADC0Value[4];
        uint32_t ui32ADC1Value[4];
//    // Enable the GPIO port that is used for the sensor port

      SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
      ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
      ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH0);
      ADCSequenceStepConfigure(ADC0_BASE, 0, 1, ADC_CTL_CH0);
      ADCSequenceStepConfigure(ADC0_BASE, 0, 2, ADC_CTL_CH0);
      ADCSequenceStepConfigure(ADC0_BASE, 0, 3, ADC_CTL_CH0|ADC_CTL_IE|ADC_CTL_END);
      ADCSequenceEnable(ADC0_BASE, 0);

      SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
      ADCSequenceConfigure(ADC1_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
      ADCSequenceStepConfigure(ADC1_BASE, 1, 0, ADC_CTL_CH1);
      ADCSequenceStepConfigure(ADC1_BASE, 1, 1, ADC_CTL_CH1);
      ADCSequenceStepConfigure(ADC1_BASE, 1, 2, ADC_CTL_CH1);
      ADCSequenceStepConfigure(ADC1_BASE, 1, 3, ADC_CTL_CH1|ADC_CTL_IE|ADC_CTL_END);
      ADCSequenceEnable(ADC1_BASE, 1);

//      ADCSequenceStepConfigure(ADC0_BASE, 0, 4, ADC_CTL_CH1);
//      ADCSequenceStepConfigure(ADC0_BASE, 0, 5, ADC_CTL_CH1);
//      ADCSequenceStepConfigure(ADC0_BASE, 0, 6, ADC_CTL_CH1);
//      ADCSequenceStepConfigure(ADC0_BASE, 0, 7, ADC_CTL_CH1|ADC_CTL_IE|ADC_CTL_END);
//      ADCSequenceEnable(ADC0_BASE, 0);

    while (1) { // allows program to run forever. Used for debugging

     ADCIntClear(ADC0_BASE, 0);
     ADCIntClear(ADC1_BASE, 1);
     ADCProcessorTrigger(ADC0_BASE, 0);
     ADCProcessorTrigger(ADC1_BASE, 1);
     while(! ADCIntStatus(ADC0_BASE, 0, false))
     {
     }
     while(! ADCIntStatus(ADC1_BASE, 1, false))
          {
          }
     ADCSequenceDataGet(ADC0_BASE, 0, ui32ADC0Value);
     ADCSequenceDataGet(ADC1_BASE, 1, ui32ADC1Value);
    charge1 = (ui32ADC0Value[0]+ui32ADC0Value[1]+ui32ADC0Value[2]+ui32ADC0Value[3])/4;
    charge2 = (ui32ADC1Value[0]+ui32ADC1Value[1]+ui32ADC1Value[2]+ui32ADC1Value[3])/4;
    }

}
