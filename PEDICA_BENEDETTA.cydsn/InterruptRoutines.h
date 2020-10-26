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
    #define BYTE_TO_SEND 4
    #define BUFFER_SIZE 1+BYTE_TO_SEND+1
    
    uint8 Led_level;
    
    CY_ISR_PROTO(ISR_UART);
    CY_ISR_PROTO(ISR_ADC);
    
    char DataBuffer[BUFFER_SIZE];
    
    volatile uint8 PacketReadyFlag;
     
#endif

/* [] END OF FILE */
