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
#include "Functions.h"

int main(void)
{
    CyGlobalIntEnable; 
    
    UART_Start(); //initializing the UART peripherals
    
    isr_UART_StartEx(ISR_UART);
    isr_ADC_StartEx(ISR_ADC); 
    
    //setting the mediated values variables to zero
    SumValuePhoto=0;  
    SumBrightnessLevel=0;
    
    //HEADER and TAIL are set up
    DataBuffer[0] = HEADER; 
    DataBuffer[BUFFER_SIZE-1] = TAIL;
    
    clock_flag=0;       //initialize clock flag
    SendBytesFlag = 0;  //initialize send flag
    
         
    for(;;)
    {
         if((SendBytesFlag==1)&&(clock_flag==1))
        {
            SetValue();
            SendBytes();
            UART_PutArray(DataBuffer,BUFFER_SIZE);  //transmit the bytes
            clock_flag= 0; 
            SumValuePhoto=0;
            SumBrightnessLevel=0;
        }
      
    }
}





/* [] END OF FILE */
