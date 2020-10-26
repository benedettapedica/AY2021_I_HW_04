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
#define THRESHOLD 2000 //we choose a brightness treshold

int32 value_photo;
int32 value_mV;
char char_received;  //to sign in it the recieved character 
uint8 SendBytesFlag = 0;  //internal variable
int32 brightness_level;

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
        ADC_DelSig_StopConvert();
        AMux_Select(0); //select channel of photoresistor
        ADC_DelSig_StartConvert();
        value_photo = ADC_DelSig_Read32();
        if(value_photo < 0)
            value_photo = 0;
        if(value_photo > 65535)
            value_photo = 65535;
        value_mV = ADC_DelSig_CountsTo_mVolts(value_photo);
  
        DataBuffer[1]=value_photo>>8;
        DataBuffer[2]=value_photo & 0xFF;        
        
        if(value_mV < THRESHOLD) 
        {
            ADC_DelSig_StopConvert();
            AMux_Select(1);            
            ADC_DelSig_StartConvert(); 
            brightness_level= ADC_DelSig_Read32();
              if(brightness_level < 0)
              brightness_level = 0;
              if(brightness_level > 65535)
              brightness_level = 65535;
           brightness_level=(brightness_level*255)/65535;
           PWM_Red_Led_Start();
           PWM_Red_Led_WriteCompare(brightness_level);
           
        DataBuffer[3] = brightness_level >> 8;
        DataBuffer[4] = brightness_level & 0xFF;
        }
        else
        {
            PWM_Red_Led_Stop();
            PWM_Red_Led_WriteCompare(0);
        }  
        
        sprintf(DataBuffer, "Sample: %ld mV \r\n", value_mV);
        PacketReadyFlag = 1;    
    }
    if (SendBytesFlag==0)
    {
        PWM_Red_Led_WriteCompare(0);
    }
}



/* [] END OF FILE */
