/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef __INTERRUPT_ROUTINES_H
    #define __INTERRUPT_ROUTINES_H

    #include "cytypes.h"
    #include "stdio.h"
     
    #define ON 1
    #define OFF 0

    #define THRESHOLD 40000  //threshold value chosen through different experiment with the light

    #define HEADER 0xA0
    #define TAIL 0xC0
   
    #define PHOTORESISTOR 0 //AMux channel used for photoresistor
    #define POTENTIOMETER 1 //AMux channel used for potentiometer
    
    #define ADC_MAX 0   //lower limit of ADC value
    #define ADC_MIN 65535 //upper limit of ADC value

    #define BYTE_TO_SEND 4  //4 bytes used, 2 for the photoresistor and 2 for the potentiometer
    #define BUFFER_SIZE 1+BYTE_TO_SEND+1  //size of the packet to be sent
     
    CY_ISR_PROTO(ISR_UART); 
    CY_ISR_PROTO(ISR_ADC);
    
    uint8_t DataBuffer[BUFFER_SIZE];  //array of the packet that is sent
    
    volatile uint8 SendBytesFlag;
    volatile uint8 clock_flag;
     
#endif

/* [] END OF FILE */
