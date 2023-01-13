/* 
 * File:   servo.h
 * Author:
 * Created on February 11, 2019, 2:08 PM
 */
/*
    Copyright 2022 Michael Jacobs

    Permission is hereby granted, free of charge, to any person obtaining a 
    copy of this software and associated documentation files (the "Software"), 
    to deal in the Software without restriction, including without limitation 
    the rights to use, copy, modify, merge, publish, distribute, sublicense, 
    and/or sell copies of the Software, and to permit persons to whom the 
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included 
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
    DEALINGS IN THE SOFTWARE.
*/


#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/system.h"


#define FCY     30170937UL


#include <libpic30.h>
#include "stddef.h"
#include "motor.h"
#include "process.h"
#include "settings.h"
#include "adc.h"

static MOTOR_MOTION motor2 = MOTOR_NOMOTION;
static MOTOR_MOTION motor1 = MOTOR_NOMOTION;
//static MOTOR_MOTION motor2;



PROBE_LIMIT get_probe2limit(void){
    
    if(LIM2_GetValue() == 0){
        return PROBE_UPLIMIT;
    }else if(LIM3_GetValue() == 0){
        return PROBE_DOWNLIMIT;
    }else return PROBE_NOLIMIT;
    
}

PROBE_LIMIT get_probe1limit(void){
    
    if(LIM1_GetValue() == 0){
        return PROBE_UPLIMIT;
    }else if(LIM4_GetValue() == 0){
        return PROBE_DOWNLIMIT;
    }else return PROBE_NOLIMIT;
}

uint16_t motor_ReadLimits1(void){
    
    uint16_t sws = 0;    
    
    if(LIM1_GetValue() == 0)
        sws = sws | 0x01;
            
    if(LIM4_GetValue() == 0)
        sws = sws | 0x02;
    return sws;    
}

void motor_MoveUptoLimit(void){
    PWM_GENERATOR genNum = PWM_GENERATOR_1;
    
    PWM_OverrideLowDisable(genNum);   
    
    IO_RB10_SetHigh();
    
    while(LIM1_GetValue() == 1);
    
    PWM_OverrideLowEnable(genNum);
    
    __delay_ms(5);
    
    IO_RB10_SetLow();    
}

void motor_MoveDowntoLimit(void){
    
    PWM_GENERATOR genNum = PWM_GENERATOR_1;
    
    PWM_OverrideHighDisable(genNum);   
    
    IO_RB10_SetHigh();
    
    while(LIM4_GetValue() == 1);
    
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

void motor2_Hold(void){
    PWM_GENERATOR genNum = PWM_GENERATOR_2;    
    PWM_OverrideHighEnable(genNum);
    PWM_OverrideLowEnable(genNum);
    motor2 = MOTOR_NOMOTION;
}

void motor1_off(void){
    PWM_GENERATOR genNum = PWM_GENERATOR_1;
    // disable motor drive
    PWM_OverrideHighEnable(genNum);
    PWM_OverrideLowEnable(genNum);
    IO_RB10_SetLow();   
    motor1 = MOTOR_NOMOTION;
}

void motor2_off(void){
    PWM_GENERATOR genNum = PWM_GENERATOR_2;
    // disable motor drive
    PWM_OverrideHighEnable(genNum);
    PWM_OverrideLowEnable(genNum);
    IO_RB11_SetLow();   
    motor2 = MOTOR_NOMOTION;
}

MOTOR_MOTION motor1_isMotion(void){
    return motor1;
}

MOTOR_MOTION motor2_isMotion(void){
    return motor2;
}

void motor1_on(void){
    PWM_GENERATOR genNum = PWM_GENERATOR_1;    
    PWM_OverrideHighEnable(genNum);
    PWM_OverrideLowEnable(genNum);
    IO_RB10_SetHigh();
    motor1 = MOTOR_NOMOTION;    
}


void motor2_on(void){
    PWM_GENERATOR genNum = PWM_GENERATOR_2;    
    PWM_OverrideHighEnable(genNum);
    PWM_OverrideLowEnable(genNum);
    IO_RB11_SetHigh();
    motor2 = MOTOR_NOMOTION;    
}

/*
 * 
 */
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

void motor2_Move(uint16_t val, MOTOR_MOTION motion){
    PWM_GENERATOR genNum = PWM_GENERATOR_2;

    if (motion != motor2) {
        PWM_OverrideHighEnable(genNum);
        PWM_OverrideLowEnable(genNum);
        PWM_DutyCycleSet(genNum, val);
        if (motion == MOTOR_DOWNMOTION) {
            motor2 = MOTOR_DOWNMOTION;
            PWM_OverrideHighDisable(genNum);
        } else {
            motor2 = MOTOR_UPMOTION;
            PWM_OverrideLowDisable(genNum);
        }
    } else
        PWM_DutyCycleSet(genNum, val);
    
}

// set probe position and set zero pressure value
void probe1_SetStartPos(void){
    motor1_on();
    if (get_probe1limit() != PROBE_UPLIMIT) {
        motor1_Move(800, MOTOR_UPMOTION);
    }
    while (get_probe1limit() != PROBE_UPLIMIT);
    motor1_Hold();
    __delay_ms(10);
    motor1_Move(800, MOTOR_DOWNMOTION);
    while (get_probe1limit() == PROBE_UPLIMIT);
    motor1_Hold();

    __delay_ms(100);
    set_p1zeropressure();   
    motor1_off();
}

void probe2_SetStartPos(void){
    motor2_on();
    if (get_probe2limit() != PROBE_UPLIMIT) {
        motor2_Move(800, MOTOR_UPMOTION);
    }
    while (get_probe2limit() != PROBE_UPLIMIT);
    motor2_Hold();
    __delay_ms(10);
    motor2_Move(800, MOTOR_DOWNMOTION);
    while (get_probe2limit() == PROBE_UPLIMIT);
    motor2_Hold();

    __delay_ms(100);
    set_p2zeropressure();   
    motor2_off();
}





