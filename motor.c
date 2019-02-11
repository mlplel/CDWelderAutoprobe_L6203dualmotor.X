





#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/system.h"


#define FCY     30170937UL


#include <libpic30.h>
#include "stddef.h"
#include "motor.h"

static MOTOR_MOTION mm = MOTOR_NOMOTION;

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
    mm = MOTOR_UPMOTION;    
    PWM_OverrideLowDisable(genNum);    
    IO_RB10_SetHigh();        
}

void motor_MoveDown(void){
    
    PWM_GENERATOR genNum = PWM_GENERATOR_1;
    mm = MOTOR_DOWNMOTION;    
    PWM_OverrideHighDisable(genNum);       
    IO_RB10_SetHigh();    
}

void motor_Hold(void){
    PWM_GENERATOR genNum = PWM_GENERATOR_1;    
    PWM_OverrideHighEnable(genNum);
    PWM_OverrideLowEnable(genNum);
    mm = MOTOR_NOMOTION;
}

void motor_Off(void){
    PWM_GENERATOR genNum = PWM_GENERATOR_1;
    // disable motor drive
    PWM_OverrideHighEnable(genNum);
    PWM_OverrideLowEnable(genNum);
    IO_RB10_SetLow();   
    mm = MOTOR_NOMOTION;
}
MOTOR_MOTION motor_isMotion(void){
    return mm;
}

void motor_On(void){
    PWM_GENERATOR genNum = PWM_GENERATOR_1;    
    PWM_OverrideHighEnable(genNum);
    PWM_OverrideLowEnable(genNum);
    IO_RB10_SetHigh();
    mm = MOTOR_NOMOTION;    
}

// motor_Move  +v motor moves down. -v motor moves up
// should never get a 0;
void motor_Move(int8_t v){
    PWM_GENERATOR genNum = PWM_GENERATOR_1;
    MOTOR_MOTION nmm = MOTOR_DOWNMOTION;
    int16_t r = v;
    
    // extract direction and scale
    if(v < 0){
        nmm = MOTOR_UPMOTION;
        r = ~v;
        r = r+1;
    }
    r = (r*8) + 400;

    if (nmm != mm) {
        PWM_OverrideHighEnable(genNum);
        PWM_OverrideLowEnable(genNum);
        PWM_DutyCycleSet(genNum, r);
        if (nmm == MOTOR_DOWNMOTION) {
            mm = MOTOR_DOWNMOTION;
            PWM_OverrideHighDisable(genNum);
        } else {
            mm = MOTOR_UPMOTION;
            PWM_OverrideLowDisable(genNum);
        }
    } else
        PWM_DutyCycleSet(genNum, r);    
}

void motor_Run(uint16_t val, MOTOR_MOTION motion){
    PWM_GENERATOR genNum = PWM_GENERATOR_1;

    if (motion != mm) {
        PWM_OverrideHighEnable(genNum);
        PWM_OverrideLowEnable(genNum);
        PWM_DutyCycleSet(genNum, val);
        if (motion == MOTOR_DOWNMOTION) {
            mm = MOTOR_DOWNMOTION;
            PWM_OverrideHighDisable(genNum);
        } else {
            mm = MOTOR_UPMOTION;
            PWM_OverrideLowDisable(genNum);
        }
    } else
        PWM_DutyCycleSet(genNum, val);
    
}


