/* ========================================
 *
 * File .h where all the MACROs are defined,
 * Flags for the clock and for the byte sending are declared,
 * The array of the packet sent is declared.
 * Two int32 variables are declared to be used to mediate the value
 * sampled by the photoresistor (SumValuePhoto) and the potentiometer
 * (SumBrightnessLevel) for a more robust measurement.
 *
 * ========================================
*/
#include "project.h"
#include "InterruptRoutines.h"
     
#define ON 1
#define OFF 0

#define THRESHOLD 30000  //threshold value chosen through different experiment with the light

#define HEADER 0xA0
#define TAIL 0xC0

#define PHOTORESISTOR 0 //AMux channel used for photoresistor
#define POTENTIOMETER 1 //AMux channel used for potentiometer

#define ADC_MIN 0   //lower limit of ADC value
#define ADC_MAX 65535 //upper limit of ADC value


#define BYTE_TO_SEND 4  //4 bytes used, 2 for the photoresistor and 2 for the potentiometer
#define BUFFER_SIZE 1+BYTE_TO_SEND+1  //size of the packet to be sent


uint8_t DataBuffer[BUFFER_SIZE];  //array of the packet that is sent


volatile uint8 SendBytesFlag;   //flag=1 when right char is recieved

volatile uint8 clock_flag;     //flag=1 1 every 100ms (timer interrupt)


int32 SumValuePhoto; //variable used to sum the sample of potentiometer

int32 SumBrightnessLevel;


void StartPeripherals(void); 

void StopPeripherals(void);

void SendBytes(void);



/* [] END OF FILE */
