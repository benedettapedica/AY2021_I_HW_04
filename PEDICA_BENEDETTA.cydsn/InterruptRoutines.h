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

#define ON 1
#define OFF 0

#define THRESHOLD 50000

#define HEADER 0xA0
#define TAIL 0xC0

#define PHOTORESISTOR 0 //AMux channel used for photoresistor
#define POTENTIOMETER 1 //AMux channel used for potentiometer

#ifndef __INTERRUPT_ROUTINES_H
    #define __INTERRUPT_ROUTINES_H

    #include "cytypes.h"
    #include "stdio.h"
    
    #define BYTE_TO_SEND 4  //4 bytes used, 2 for the photoresistor and 2 for the potentiometer
    #define BUFFER_SIZE 1+BYTE_TO_SEND+1
     
    CY_ISR_PROTO(ISR_UART);
    CY_ISR_PROTO(ISR_ADC);
    
    uint8_t DataBuffer[BUFFER_SIZE];
    
    volatile uint8 SendBytesFlag;
    volatile uint8 clock_flag;
    volatile uint8 PacketReadyFlag;
     
#endif

/* [] END OF FILE */
