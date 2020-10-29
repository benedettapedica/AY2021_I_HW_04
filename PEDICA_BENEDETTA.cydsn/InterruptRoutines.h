/* ========================================
 * File .h where all the MACROs are defined,
 * Functions of both ISRs are declared through MACRO,
 * Flags for the clock and for the byte sending are declared,
 * The array of the packet sent is declared.
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
    
    volatile uint8 SendBytesFlag;   //flag=1 when right char is recieved
    volatile uint8 clock_flag;     //flag=1 1 every 100ms (timer interrupt)
     
#endif

/* [] END OF FILE */
