





#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/system.h"


#define FCY     30170937UL


#include <libpic30.h>
#include "stddef.h"
#include "motor.h"

static uint8_t fmotorupmotion = 0;
static uint8_t fmotordownmotion = 0;

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
    fmotorupmotion = 1;    
    PWM_OverrideLowDisable(genNum);    
    IO_RB10_SetHigh();        
}

void motor_MoveDown(void){
    
    PWM_GENERATOR genNum = PWM_GENERATOR_1;
    fmotordownmotion = 1;    
    PWM_OverrideHighDisable(genNum);       
    IO_RB10_SetHigh();    
}

void motor_Hold(void){
    PWM_GENERATOR genNum = PWM_GENERATOR_1;    
    PWM_OverrideHighEnable(genNum);
    PWM_OverrideLowEnable(genNum);
    fmotorupmotion = 0;
    fmotordownmotion = 0;
}

void motor_Off(void){
    PWM_GENERATOR genNum = PWM_GENERATOR_1;
    // disable motor drive
    PWM_OverrideHighEnable(genNum);
    PWM_OverrideLowEnable(genNum);
    IO_RB10_SetLow();   
    fmotorupmotion = 0;
    fmotordownmotion = 0;
}
MOTOR_MOTION motor_isMotion(void){
    if(fmotorupmotion)
        return MOTOR_UPMOTION;
    else if(fmotordownmotion)
        return MOTOR_DOWNMOTION;
    else
        return MOTOR_NOMOTION;
}



