/* ========================================
*   \file main.c
*   \Main file for Assignment 04- Smart Lamp prototype
*   In this main file all the devices are initialized,
*   the header and the tail of the message sent are defined 
*   and the message is transmitted.
*
*   \author Benedetta Pedica 
* ========================================
*/
#include "project.h"
#include "InterruptRoutines.h"

int main(void)
{
    CyGlobalIntEnable; 
    
    ADC_DelSig_Start();
    Timer_Start();
    UART_Start();
    PWM_Red_Led_Start();
    
    timer_clock_Start();
    Clock_PWM_Start();    
    
    isr_UART_StartEx(ISR_UART);
    isr_ADC_StartEx(ISR_ADC); 
    
    //HEADER and TAIL are set up
    DataBuffer[0] = HEADER; 
    DataBuffer[BUFFER_SIZE-1] = TAIL;
    
    clock_flag=0;
    SendBytesFlag = 0;  //initialize send flag
    
         
    for(;;)
    {
         if((SendBytesFlag==1)&&(clock_flag==1))
        {
            UART_PutArray(DataBuffer,BUFFER_SIZE);  //transmit the bytes
            clock_flag= 0; 
        }
      
    }
}





/* [] END OF FILE */
