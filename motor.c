





#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/system.h"


#define FCY     30170937UL


#include <libpic30.h>
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

void motor_MoveUptoLimit(void){
    PWM_GENERATOR genNum = PWM_GENERATOR_1;
    
    PWM_OverrideLowDisable(genNum);   
    
    IO_RB10_SetHigh();
    
    while(IO_RA4_GetValue() == 0);
    
    PWM_OverrideLowEnable(genNum);
    
    __delay_ms(5);
    
    IO_RB10_SetLow();
    
}

void motor_MoveDowntoLimit(void){
    
    PWM_GENERATOR genNum = PWM_GENERATOR_1;
    
    PWM_OverrideHighDisable(genNum);   
    
    IO_RB10_SetHigh();
    
    while(IO_RB8_GetValue() == 0);
    
    PWM_OverrideHighEnable(genNum);
    
    __delay_ms(5);
    
    IO_RB10_SetLow();     
    
}

void motor_MoveUp(void){
    
    PWM_GENERATOR genNum = PWM_GENERATOR_1;
    
    PWM_OverrideLowDisable(genNum);   
    
    IO_RB10_SetHigh();        
}


void motor_MoveDown(void){
    
    PWM_GENERATOR genNum = PWM_GENERATOR_1;
    
    PWM_OverrideHighDisable(genNum);   
    
    IO_RB10_SetHigh();    
}

void motor_Hold(void){
    PWM_GENERATOR genNum = PWM_GENERATOR_1;
    
    PWM_OverrideHighEnable(genNum);
    PWM_OverrideLowEnable(genNum);
}



