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
#include "InterruptRoutines.h"
#include "project.h"

#define ON 1
#define OFF 0

int32 value_digit;
int32 value_mV;
char char_received;  //to sign in it the recieved character 
uint8 SendBytesFlag = 0;  //internal variable


CY_ISR(ISR_UART)
{
    char_received = UART_GetChar();
    switch(char_received)  //setting flags based on UART command
    {
        case 'B':
        case 'b':
            SendBytesFlag = 1;
            Blue_LED_Write(ON);   //begin sampling sensors
            Timer_Start();
            break;
        case 'S':
        case 's':
            SendBytesFlag = 0;
            Blue_LED_Write(OFF);  //stop sampling sensors
            Timer_Stop();
            break;  
        default:
            break;
    }
}


CY_ISR(ISR_ADC)
{
    Timer_ReadStatusRegister();
    if(SendBytesFlag==1)
    {
        value_digit = ADC_DelSig_Read32();
        if(value_digit < 0)
            value_digit = 0;
        if(value_digit > 65535)
            value_digit = 65535;
        value_mV = ADC_DelSig_CountsTo_mVolts(value_digit);
        
        if(value_mV < 1500) //we choose a brightness treshold
        {
            Led_level=0;
        }
        else
        {
            Led_level=1;
        }      
        
        sprintf(DataBuffer, "Sample: %ld mV\r\n", value_mV);
        PacketReadyFlag = 1;
    }
}



/* [] END OF FILE */
