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
#include "Functions.h"

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
            StartPeripherals();
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
    clock_flag=1;
    
    Timer_ReadStatusRegister();  //bringing the interrupt line low
    
    if (SendBytesFlag==1) 
    {
        AMux_Select(PHOTORESISTOR); //select channel of photoresistor
        
        value_photo = ADC_DelSig_Read32();  //saving sampled value
                
        //values are normalized in the allowed range
        if(value_photo < ADC_MIN)
            value_photo = ADC_MIN;
        if(value_photo > ADC_MAX)
            value_photo = ADC_MAX;
        
        SumValuePhoto= SumValuePhoto+value_photo; //used to do a cumulative sum of the sample and then mediate them

        
        if (value_photo <= THRESHOLD)  //if we go below a certain threshold
         {
            AMux_Select(POTENTIOMETER);     //switch AMux to channel of Potentiometer  
                     
            brightness_level= ADC_DelSig_Read32(); //sample from Potentiometer the value of brightness
        
            if(brightness_level < ADC_MIN)
            brightness_level = ADC_MIN;
            if(brightness_level > ADC_MAX)
            brightness_level = ADC_MIN;
            
            SumBrightnessLevel= SumBrightnessLevel+brightness_level;  //again mediating the value obtained for more robustness
            
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
        StopPeripherals();  //if letter s is inserted, stop all the peripherals 
    }
}
/* [] END OF FILE */