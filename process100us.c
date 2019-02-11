/* 
 * File:   process100us.c
 * Author: mjacobs
 *
 * Created on December 12, 2018, 8:56 AM
 */


#include "mcc_generated_files/mcc.h"
#include "dualmotor.h"
#include "motor.h"





void loop100us(void){
    
    //IO_RC3_Toggle(); 
    MOTOR_MOTION mm = motor_isMotion();
    if(mm == MOTOR_UPMOTION){
        if(IO_RA4_GetValue())
            motor_Off();
    }
    else if(mm == MOTOR_DOWNMOTION){        
    if(IO_RB8_GetValue())
        motor_Off();
    }
}