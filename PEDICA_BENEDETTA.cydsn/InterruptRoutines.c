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
int32 value_mV;
char char_received;  //to sign in it the recieved character 
uint8 SendBytesFlag = 0;  //internal variable
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
    }

CY_ISR(ISR_ADC)
{
    Timer_ReadStatusRegister();
    clock_flag=1;
    if(SendBytesFlag==1)
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
        value_mV = ADC_DelSig_CountsTo_mVolts(value_photo);
  
        //The value is written on the array to send 
        DataBuffer[1]=value_photo>>8;
        DataBuffer[2]=value_photo & 0xFF;        
        
        if(value_mV < THRESHOLD)  //if luminosity of the room goes below a threshold 
        {
            ADC_DelSig_StopConvert();
            AMux_Select(POTENTIOMETER);     //switch AMux to channel of Potentiometer  
            ADC_DelSig_StartConvert(); 
            brightness_level= ADC_DelSig_Read32(); //sample from Potentiometer the value of brightness
              if(brightness_level < 0)
              brightness_level = 0;
              if(brightness_level > 65535)
              brightness_level = 65535;
            
           brightness_level=(brightness_level*255)/65535;  
           PWM_Red_Led_Start();
           PWM_Red_Led_WriteCompare(brightness_level); //the value sampled by potentiometer is used to set the duty cycle of the PWM to change intensity
        
        //The value is written again on the array to send   
        DataBuffer[3] = brightness_level >> 8;
        DataBuffer[4] = brightness_level & 0xFF;
        }
        else
        {
            PWM_Red_Led_Stop();
            PWM_Red_Led_WriteCompare(0);
        }  
        PacketReadyFlag = 1;    
    }
    if (SendBytesFlag==0)
    {
        PWM_Red_Led_WriteCompare(0);
    }
}



/* [] END OF FILE */
