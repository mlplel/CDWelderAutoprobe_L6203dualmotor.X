/* 
 * File:   servo.h
 * Author: mjacobs
 *
 * Created on February 11, 2019, 2:08 PM
 */


#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/system.h"


#define FCY     30170937UL


#include <libpic30.h>
#include "stddef.h"
#include "motor.h"
#include "process.h"
#include "settings.h"

static MOTOR_MOTION motor1;
//static MOTOR_MOTION motor2;

PROBE_LIMIT probe1_GetLimit(void){
    
    if(IO_RA4_GetValue() == 0){
        return PROBE_UPLIMIT;
    }else if(IO_RB8_GetValue() == 0){
        return PROBE_DOWNLIMIT;
    }else return PROBE_NOLIMIT;
}

uint16_t motor_ReadLimits1(void){
    
    uint16_t sws = 0;    
    
    if(IO_RA4_GetValue() == 0)
        sws = sws | 0x01;
            
    if(IO_RB8_GetValue() == 0)
        sws = sws | 0x02;
    return sws;    
}

void motor_MoveUptoLimit(void){
    PWM_GENERATOR genNum = PWM_GENERATOR_1;
    
    PWM_OverrideLowDisable(genNum);   
    
    IO_RB10_SetHigh();
    
    while(IO_RA4_GetValue() == 1);
    
    PWM_OverrideLowEnable(genNum);
    
    __delay_ms(5);
    
    IO_RB10_SetLow();    
}

void motor_MoveDowntoLimit(void){
    
    PWM_GENERATOR genNum = PWM_GENERATOR_1;
    
    PWM_OverrideHighDisable(genNum);   
    
    IO_RB10_SetHigh();
    
    while(IO_RB8_GetValue() == 1);
    
    PWM_OverrideHighEnable(genNum);
    
    __delay_ms(5);
    
    IO_RB10_SetLow();     
}

void motor_MoveUp(void){
    
    PWM_GENERATOR genNum = PWM_GENERATOR_1;
    motor1 = MOTOR_UPMOTION;    
    PWM_OverrideLowDisable(genNum);    
    IO_RB10_SetHigh();        
}

void motor_MoveDown(void){
    
    PWM_GENERATOR genNum = PWM_GENERATOR_1;
    motor1 = MOTOR_DOWNMOTION;    
    PWM_OverrideHighDisable(genNum);       
    IO_RB10_SetHigh();    
}

void motor1_Hold(void){
    PWM_GENERATOR genNum = PWM_GENERATOR_1;    
    PWM_OverrideHighEnable(genNum);
    PWM_OverrideLowEnable(genNum);
    motor1 = MOTOR_NOMOTION;
}

void motor1_Off(void){
    PWM_GENERATOR genNum = PWM_GENERATOR_1;
    // disable motor drive
    PWM_OverrideHighEnable(genNum);
    PWM_OverrideLowEnable(genNum);
    IO_RB10_SetLow();   
    motor1 = MOTOR_NOMOTION;
}

MOTOR_MOTION motor1_isMotion(void){
    return motor1;
}

void motor1_On(void){
    PWM_GENERATOR genNum = PWM_GENERATOR_1;    
    PWM_OverrideHighEnable(genNum);
    PWM_OverrideLowEnable(genNum);
    IO_RB10_SetHigh();
    motor1 = MOTOR_NOMOTION;    
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

    if (nmm != motor1) {
        PWM_OverrideHighEnable(genNum);
        PWM_OverrideLowEnable(genNum);
        PWM_DutyCycleSet(genNum, r);
        if (nmm == MOTOR_DOWNMOTION) {
            motor1 = MOTOR_DOWNMOTION;
            PWM_OverrideHighDisable(genNum);
        } else {
            motor1 = MOTOR_UPMOTION;
            PWM_OverrideLowDisable(genNum);
        }
    } else
        PWM_DutyCycleSet(genNum, r);    
}

void motor1_Move(uint16_t val, MOTOR_MOTION motion){
    PWM_GENERATOR genNum = PWM_GENERATOR_1;

    if (motion != motor1) {
        PWM_OverrideHighEnable(genNum);
        PWM_OverrideLowEnable(genNum);
        PWM_DutyCycleSet(genNum, val);
        if (motion == MOTOR_DOWNMOTION) {
            motor1 = MOTOR_DOWNMOTION;
            PWM_OverrideHighDisable(genNum);
        } else {
            motor1 = MOTOR_UPMOTION;
            PWM_OverrideLowDisable(genNum);
        }
    } else
        PWM_DutyCycleSet(genNum, val);
    
}

// set probe position and set zero pressure value
void probe1_SetStartPos(void){
    
    if (probe1_GetLimit() != PROBE_UPLIMIT) {
        motor1_On();
        motor1_Move(800, MOTOR_UPMOTION);
    }
    while (probe1_GetLimit() != PROBE_UPLIMIT);
    motor1_On();
    motor1_Move(600, MOTOR_DOWNMOTION);
    while (probe1_GetLimit() == PROBE_UPLIMIT);
    motor1_Hold();

    __delay_ms(100);
    setP1ZeroPressure();   
    motor1_Off();
}


