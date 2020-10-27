/* ========================================
*   \file main.c
*   \Main file for Assignment 04- Smart Lamp prototype
*
*
*
*   \author Benedetta Pedica 
* ========================================
*/
#include "project.h"
#include "InterruptRoutines.h"
#include "stdio.h"


int main(void)
{
    CyGlobalIntEnable; 
    
    //HEADER and TAIL are set up
    DataBuffer[0] = HEADER; 
    DataBuffer[BUFFER_SIZE-1] = TAIL;

    ADC_DelSig_Start();
    
    UART_Start();
    
    Clock_PWM_Start();
    
    isr_ADC_StartEx(ISR_ADC);
    isr_UART_StartEx(ISR_UART);
    
    PacketReadyFlag = 0;  //initialize send flag
    ADC_DelSig_StartConvert();  //starting conversion of the ADC
   
    for(;;)
    {
        if(PacketReadyFlag==1 && clock_flag==1)
        {
            UART_PutArray(DataBuffer, BUFFER_SIZE);
            PacketReadyFlag = 0;          
        }
    }
}





/* [] END OF FILE */
