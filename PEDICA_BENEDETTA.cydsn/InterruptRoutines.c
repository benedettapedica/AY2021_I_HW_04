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

int32 value_photo;
char char_received;  //to sign in it the recieved character 
int32 brightness_level;

CY_ISR(ISR_UART)
{
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
    char_received = UART_GetChar();
    switch(char_received)  //setting flags based on UART command
    {
        case 'B':
        case 'b':
            SendBytesFlag = 1;
            Blue_LED_Write(ON);   //begin sampling sensors, onboard LED on
            break;
        
        case 'S':
        case 's':
            SendBytesFlag = 0;
            Blue_LED_Write(OFF);  //stop sampling sensors, onboard LED off
            break;  
        
        default:
            break;
    }
  }
}
    

CY_ISR(ISR_ADC)
{
    Timer_ReadStatusRegister();
    
    if (SendBytesFlag==1)
    {
        ADC_DelSig_StopConvert();
        AMux_Select(PHOTORESISTOR);   //select channel of photoresistor
        ADC_DelSig_StartConvert();
        value_photo = ADC_DelSig_Read32();  //saving sampled value
        //values are normalized in the allowed range
        if(value_photo < 0)
            value_photo = 0;
        if(value_photo > 65535)
            value_photo = 65535;

        //The value is written on the array to send 
        DataBuffer[1]=value_photo>>8;
        DataBuffer[2]=value_photo & 0xFF;     
        
        if (value_photo <= 25000)
         {
            ADC_DelSig_StopConvert();
            AMux_Select(POTENTIOMETER);     //switch AMux to channel of Potentiometer  
            ADC_DelSig_StartConvert(); 
            
            brightness_level= ADC_DelSig_Read32(); //sample from Potentiometer the value of brightness
        
            if(brightness_level < 0)
            brightness_level = 0;
            if(brightness_level > 65535)
            brightness_level = 65535;
       
   
            DataBuffer[3]= brightness_level>>8;
            DataBuffer[4]= brightness_level & 0xFF; 
            
            PWM_Red_Led_WriteCompare(brightness_level/257);
            
        }
        
        else 
        {
            PWM_Red_Led_WriteCompare(0);
            DataBuffer[3]= 0x00;
            DataBuffer[4]= 0x00; 
        }
      
    PacketReadyFlag = 1;    //flag used to send the packet
}
    else
    {
        PWM_Red_Led_WriteCompare(0);
    }
}
/* [] END OF FILE */