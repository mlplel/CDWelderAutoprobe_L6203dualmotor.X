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
//static int16_t isumMax = 2000;
//static int16_t isumMin = -2000;
//static int16_t maxout = 1300;

static uint16_t servo1trigger = 0;
static uint16_t servo2trigger = 0;

static PID_TEMRS pid1;
static PID_TEMRS pid2;
static int16_t perror1 = 0;
static int16_t perror2 = 0;
static MOTOR_MOTION mm1 = MOTOR_DOWNMOTION;
static MOTOR_MOTION mm2 = MOTOR_DOWNMOTION;
//static int16_t pressure1setvalue;
PRESSET ps1, ps2;



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
        perror1 = 0;
        mm1 = MOTOR_DOWNMOTION;
        // pressure1setvalue = getP1Pressure();
        //PIDVALUE p = get_P1pid();
        ps1 = getP1();
        pid1.Kp = ps1.kp;
        pid1.Ki = ps1.ki;
        pid1.Kd = ps2.kd;
         
                   
        motor1_on();
        motor1_Move(200, MOTOR_DOWNMOTION);
        //display_
    }
    if(m == SERVO2 || m == SERVOBOTH){
        servo2trigger = 1;
        pid2.i = 0;
        pid2.d = 0;
        perror2 = 0;
        mm2 = MOTOR_DOWNMOTION;
        // pressure1setvalue = getP1Pressure();
        //PIDVALUE p = get_P2pid();
        ps2 = getP2();
        pid2.Kp = ps2.kp;
        pid2.Ki = ps2.ki;
        pid2.Kd = ps2.kd;
         
                   
        motor2_on();
        motor2_Move(200, MOTOR_DOWNMOTION);
    }        
}

void servo1_run(int16_t p){
    static uint16_t itime = 0;
 //   static uint16_t dtime = 0;
    static uint16_t otime = 0;
    
    if(servo1trigger == 0)
        return; 
    
    if(otime != 0){
        otime--;
        pid1.i = 0;
        return;
    }
   
    int32_t error = ps1.pressure - p;
    
    if (itime == 0) {
        pid1.i = error + pid1.i;
        if (pid1.i > ps1.imax)
            pid1.i = ps1.imax;
        else if (pid1.i < (0 - ps1.imax))
            pid1.i = (0 - ps1.imax);
        itime = 3;
    }
    
    /*
    if(dtime == 0){
        pid1.d = error - perror1;
        perror1 = error;
        dtime = 3;
    }
    */
    /*
    if((error < 130) && (error > -130)){
        servo1trigger--;
        if(servo1trigger == 0){
            motor1_Hold();
        }
        return;
    }    
    */
    int32_t output = (error * pid1.Kp) + (pid1.i * pid1.Ki); // + (pid1.d * pid1.Kd);
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
    if(mm1 != m){
        otime = 20;
        mm1 = m;
        output = 0;
    }
    if(output > ps1.outlimit){
        output = ps1.outlimit;
        itime++;
    }        
    
    motor1_Move(output, m);
    itime--;
    //dtime--;
       
}


void servo1_stop(void){
    servo1trigger = 0;
    motor1_Hold();
}

void servo2_run(int16_t p){
    static uint16_t itime = 0;
 //   static uint16_t dtime = 0;
    static uint16_t otime = 0;
    
    if(servo2trigger == 0)
        return;   
    
    if(otime != 0){
        otime--;
        pid2.i = 0;
        return;
    }

    int32_t error = ps2.pressure - p;

    if (itime == 0) {
        pid2.i = error + pid2.i;
        if (pid2.i > ps2.imax)
            pid2.i = ps2.imax;
        else if (pid2.i < (0 - ps2.imax))
            pid2.i = (0 - ps2.imax);
        itime = 3;
    }

    /*
    if(dtime == 0){
        pid2.d = error - perror2;
        perror2 = error;
        dtime = 3;
    }
     */
    /*
    if((error < 130) && (error > -130)){
        servo1trigger--;
        if(servo1trigger == 0){
            motor1_Hold();
        }
        return;
    }    
    */
    int32_t output = (error * pid2.Kp) + (pid2.i * pid2.Ki); // + (pid2.d * pid2.Kd);
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
    if(mm2 != m){
        otime = 20;
        mm2 = m;
        output = 0;
    }
    if(output > ps2.outlimit){
        output = ps2.outlimit;
        itime++;
    }        
    
    motor2_Move(output, m);    
    itime--;
   // dtime--;
}


void servo2_stop(void){
    servo2trigger = 0;
    motor2_Hold();
}
