/* ========================================
 *
 * File .c where all used functions are defined
 * here are declared two variables to store the mean value of 10 samples
 *
 * ========================================
*/
#include "Functions.h"
#include "InterruptRoutines.h"

void StartPeripherals() //Start peripherals function
{
    ADC_DelSig_Start();
    Timer_Start();
    timer_clock_Start();
    Clock_PWM_Start();
    PWM_Red_Led_Start();
}

void StopPeripherals()  //Stop peripherals function
{  
    ADC_DelSig_Stop();
    Timer_Stop();
    timer_clock_Stop();
    Clock_PWM_Stop();
    PWM_Red_Led_Stop();
    
}


volatile int32 MeanPhotoValue; 
volatile int32 MeanBrightnessLevel;

void SetValue()
{
    //the sampled values are mediated over 10 samples for more robustness
    MeanPhotoValue= SumValuePhoto/10;
    
    MeanBrightnessLevel= SumBrightnessLevel/10;

    PWM_Red_Led_WriteCompare(MeanBrightnessLevel/257);  //setting duty cycle of the PWM through the potentiometer samples
}

void SendBytes()
{
    //The value is written on the array to send 
    DataBuffer[1]= MeanPhotoValue >> 8;
    DataBuffer[2]= MeanPhotoValue & 0xFF;   
    DataBuffer[3]= MeanBrightnessLevel >> 8;  //putting in the DataBuffer string the value of MSB of brightness level
    DataBuffer[4]= MeanBrightnessLevel & 0xFF;  //putting in the DataBuffer string the value of LSB of brightness level

}


/* [] END OF FILE */
