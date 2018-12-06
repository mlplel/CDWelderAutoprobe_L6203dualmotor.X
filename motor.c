





#include "mcc_generated_files/pin_manager.h"
#include "stddef.h"
#include "motor.h"






uint16_t motor_ReadLimits1(void){
    
    uint16_t sws = 0;    
    
    if(IO_RA4_GetValue() == 1)
        sws = sws | 0x01;
            
    if(IO_RB8_GetValue() == 1)
        sws = sws | 0x02;
    return sws;
    
}






