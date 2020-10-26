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

    ADC_DelSig_Start();
    
    UART_Start();
    
    isr_ADC_StartEx(ISR_ADC);
    isr_UART_StartEx(ISR_UART);
    
    PacketReadyFlag = 0;
    ADC_DelSig_StartConvert();
    Clock_PWM_Start();

    for(;;)
    {
        if(PacketReadyFlag==1)
        {
            UART_PutString(DataBuffer);
            PacketReadyFlag = 0;
                        
        }
    }
}





/* [] END OF FILE */
