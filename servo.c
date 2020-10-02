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
static PID_TEMRS pid2;
//static int16_t pressure1setvalue;


void servo_Init(void) {
    pid1.Kp = 150;
    pid1.Ki = 80;
    pid1.Kd = 0;
    pid1.i = 0;
    pid1.d = 0;
    
}

void servo_trigger(SERVO_MODE m){
    
    if(m == SERVO1 || m == SERVOBOTH){
        //servo1trigger = SERVOTIME; 
        servo1trigger = 1;
        pid1.i = 0;
        pid1.d = 0;
        // pressure1setvalue = getP1Pressure();
        PIDVALUE p = get_P1pid();
        pid1.Kp = p.kp;
        pid1.Ki = p.ki;
         
                   
        motor1_on();
        motor1_Move(200, MOTOR_DOWNMOTION);
        //display_
    }
    if(m == SERVO2 || m == SERVOBOTH){
        servo2trigger = 1;
        pid2.i = 0;
        pid2.d = 0;
        // pressure1setvalue = getP1Pressure();
        PIDVALUE p = get_P2pid();
        pid2.Kp = p.kp;
        pid2.Ki = p.ki;
         
                   
        motor2_on();
        motor2_Move(200, MOTOR_DOWNMOTION);
    }        
}

void servo1_run(int16_t p){
    if(servo1trigger == 0)
        return;     

    int32_t error = getP1Pressure() - p;
      
    pid1.i = error + pid1.i;
    if(pid1.i > isumMax)
        pid1.i = isumMax;
    else if(pid1.i < isumMin)
        pid1.i = isumMin;
    
 
    /*
    if((error < 130) && (error > -130)){
        servo1trigger--;
        if(servo1trigger == 0){
            motor1_Hold();
        }
        return;
    }    
    */
    int32_t output = (error * pid1.Kp) + (pid1.i * pid1.Ki);
    //int32_t output = (error * pid1.Kp);
    MOTOR_MOTION m = MOTOR_DOWNMOTION;
    output = (output / 512);
    
    if(output < 0){
        m = MOTOR_UPMOTION;
        output = abs(output);
        if(get_probe1limit() == PROBE_UPLIMIT){
            m = MOTOR_DOWNMOTION;
            output = 0;
        }
    }
    if(output > 1300){
        output = 1300;
    }        
    
    motor1_Move(output, m);
       
}


void servo1_stop(void){
    servo1trigger = 0;
    motor1_Hold();
}

void servo2_run(int16_t p){
    if(servo2trigger == 0)
        return;     

    int32_t error = getP2Pressure() - p;
      
    pid2.i = error + pid2.i;
    if(pid2.i > isumMax)
        pid2.i = isumMax;
    else if(pid2.i < isumMin)
        pid2.i = isumMin;
    

    /*
    if((error < 130) && (error > -130)){
        servo1trigger--;
        if(servo1trigger == 0){
            motor1_Hold();
        }
        return;
    }    
    */
    int32_t output = (error * pid2.Kp) + (pid2.i * pid2.Ki);
    //int32_t output = (error * pid2.Kp);
    MOTOR_MOTION m = MOTOR_DOWNMOTION;
    output = (output / 512);
    
    if(output < 0){
        m = MOTOR_UPMOTION;
        output = abs(output);
        if(get_probe2limit() == PROBE_UPLIMIT){
            m = MOTOR_DOWNMOTION;
            output = 0;
        }
    }
    if(output > 1300){
        output = 1300;
    }        
    
    motor2_Move(output, m);       
}


void servo2_stop(void){
    servo2trigger = 0;
    motor2_Hold();
}
