/* ========================================
 *
 * File .c defining the two interrupt service routine
 * In the ADC isr the channel of the potentiometer is 
 * selected only if the condition on the threshold is true
 * Threshold chosen after different experiments with level of light
 *
 * ========================================
*/
#include "InterruptRoutines.h"
#include "project.h"

int32 value_photo;   //to sign in it the photoresistor sample
uint8 char_received;  //to sign in it the recieved character 
int32 brightness_level; //to sign in it the potentiometer sample

CY_ISR(ISR_UART)
{
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
    char_received = UART_GetChar();
    switch(char_received)  //setting flags based on UART command received
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
    clock_flag=1;
    
    if (SendBytesFlag==1) 
    {
        ADC_DelSig_StopConvert();
        AMux_Select(PHOTORESISTOR); //select channel of photoresistor
        ADC_DelSig_StartConvert();
        value_photo = ADC_DelSig_Read32();  //saving sampled value
                
        //values are normalized in the allowed range
        if(value_photo < ADC_MIN)
            value_photo = ADC_MIN;
        if(value_photo > ADC_MAX)
            value_photo = ADC_MAX;

        //The value is written on the array to send 
        DataBuffer[1]=value_photo>>8;
        DataBuffer[2]=value_photo & 0xFF;     
        
        if (value_photo <= THRESHOLD)  //if we go below a certain threshold
         {
            ADC_DelSig_StopConvert();
            AMux_Select(POTENTIOMETER);     //switch AMux to channel of Potentiometer  
            ADC_DelSig_StartConvert();
            
            brightness_level= ADC_DelSig_Read32(); //sample from Potentiometer the value of brightness
        
            if(brightness_level < ADC_MIN)
            brightness_level = ADC_MIN;
            if(brightness_level > ADC_MAX)
            brightness_level = ADC_MIN;
   
            DataBuffer[3]= brightness_level>>8;  //putting in the DataBuffer string the value of MSB of brightness level
            DataBuffer[4]= brightness_level & 0xFF;  //putting in the DataBuffer string the value of LSB of brightness level
            
            PWM_Red_Led_WriteCompare((brightness_level)/257); //divide by 257 to rescale because ADC is 16bit but PWM is 8bit
            
        }
        
        else 
        {
            PWM_Red_Led_WriteCompare(0);  //if condition of the threshold is not true, turn off the LED 
            DataBuffer[3]= 0x00;          //passing to UART 0 value
            DataBuffer[4]= 0x00; 
        }
      
}
    else
    {
        PWM_Red_Led_WriteCompare(0);
    }
}
/* [] END OF FILE */