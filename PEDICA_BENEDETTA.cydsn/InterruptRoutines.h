/* ========================================
 *
 * File .h where the MACROs for isr are declared
 *
 * ========================================
*/
#ifndef __INTERRUPT_ROUTINES_H
    #define __INTERRUPT_ROUTINES_H

    #include "cytypes.h"
    #include "stdio.h"
     
    CY_ISR_PROTO(ISR_UART); 
    CY_ISR_PROTO(ISR_ADC);
    
   
#endif

/* [] END OF FILE */
