/* 
 * File:   servo.h
 * Author: mjacobs
 *
 * Created on February 11, 2019, 2:08 PM
 */

#include "process.h"
#include "servo.h"
#include "motor.h"
#include "settings.h"
#include <stdlib.h>
#include "mcc_generated_files/mcc.h"

const uint16_t SERVOTIME = 70;
const int16_t isumMax = 2000;
const int16_t isumMin = -2000;

static uint16_t servo1trigger = 0;
static uint16_t servo2trigger = 0;

static PID_TEMRS pid1;
static int16_t pressure1setvalue;


void servo_Init(void) {
    pid1.Kp = 150;
    pid1.Ki = 80;
    pid1.Kd = 0;
    pid1.i = 0;
    pid1.d = 0;
    
}

void servo_Trigger(SERVO_MODE m){
    
    if(m == SERVO1 || m == SERVOBOTH){
        //servo1trigger = SERVOTIME; 
        servo1trigger = 1;
        pid1.i = 0;
        pid1.d = 0;
        pressure1setvalue = getP1Pressure();
        PIDVALUE p = getP1Pid();
        pid1.Kp = p.kp;
        pid1.Ki = p.ki;
         
                   
        motor1_On();
        motor1_Move(200, MOTOR_DOWNMOTION);
        //display_
    }
    if(m == SERVO2 || m == SERVOBOTH){
        servo2trigger = SERVOTIME;
    }        
}

void servo1_Stop(void){
    servo1trigger = 0;
    motor1_Hold();
    //display_On();
}

void servo_1Run(int16_t p){
    if(servo1trigger == 0)
        return;
     

    int32_t error = pressure1setvalue - p;
         // test screw hystera here
    
     if(motor1_isMotion() == MOTOR_DOWNMOTION){
         error += 0;
     }
     else{
         error -= 0;
     }
    
    
    pid1.i = error + pid1.i;
    if(pid1.i > isumMax)
        pid1.i = isumMax;
    else if(pid1.i < isumMin)
        pid1.i = isumMin;
    
    int32_t derror = error - pid1.d;
    pid1.d = error;
    /*
    if((error < 130) && (error > -130)){
        servo1trigger--;
        if(servo1trigger == 0){
            motor1_Hold();
        }
        return;
    }    
    */
    int32_t output = (error * pid1.Kp) + (pid1.i * pid1.Ki) + (derror * pid1.Kd);
    
    MOTOR_MOTION m = MOTOR_DOWNMOTION;
    output = (output / 512);
    
    if(output < 0){
        m = MOTOR_UPMOTION;
        output = abs(output);
    }

    if(output > 1300){
        output = 1300;
    }        
    
    motor1_Move(output, m);
       
}

