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
         if((SendBytesFlag)&&(clock_flag))
        {
            UART_PutArray(DataBuffer,BUFFER_SIZE);
            clock_flag= 0;
        }
      
    }
}





/* [] END OF FILE */
