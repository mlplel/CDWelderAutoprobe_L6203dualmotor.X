/* 
 * File:   servo.h
 * Author: mjacobs
 *
 * Created on February 11, 2019, 2:08 PM
 */

#include "adc.h"
#include "process.h"
#include "servo.h"
#include "motor.h"
#include "settings.h"
#include <stdlib.h>
#include "mcc_generated_files/mcc.h"

static uint16_t servo1trigger = 0;
static uint16_t servo2trigger = 0;
static bool ps1okf = false;
static bool ps2okf = false;

static PID_TEMRS pid1;
static PID_TEMRS pid2;
static int16_t perror1 = 0;
static int16_t perror2 = 0;
static MOTOR_MOTION mm1 = MOTOR_DOWNMOTION;
static MOTOR_MOTION mm2 = MOTOR_DOWNMOTION;
static PRESSET ps1 = {0,0,0,0,0,0,false};
static PRESSET ps2 = {0,0,0,0,0,0,false};
static SERVO_MODE servomode = SERVO_NONE;

/*
 * 
 */
bool servo_isoutputactive(){
    if(servomode == SERVO_BOTH){
        if((ps1okf == true) && (ps2okf == true)){
            ps1okf = false;
            ps2okf = false;
            return true;
        }
    } else if(servomode == SERVO_PR){
        if(ps1okf == true){
            ps1okf = false;
            return true;
        }
    } else if(servomode == SERVO_PL){
        if(ps2okf == true){
            ps2okf = false;
            return true;
        }
    }
    return false;
}


/*
 *
 */
void servo_trigger(){    
    if((servomode == SERVO_PR) || (servomode == SERVO_BOTH) || (servomode == SERVO_CALPR)){
        servo1trigger = 1;
        pid1.i = 0;
        pid1.d = 0;
        perror1 = 0;
        mm1 = MOTOR_DOWNMOTION;
 
        motor1_on();
        motor1_Move(200, MOTOR_DOWNMOTION);       
    }
    if((servomode == SERVO_PL) || (servomode == SERVO_BOTH) || (servomode == SERVO_CALPL)){
        servo2trigger = 1;
        pid2.i = 0;
        pid2.d = 0;
        perror2 = 0;
        mm2 = MOTOR_DOWNMOTION;
 
        motor2_on();
        motor2_Move(200, MOTOR_DOWNMOTION);
    }        
}

void servo1_run(int16_t p){
    static uint16_t itime = 0;
//  static uint16_t dtime = 0;
    static uint16_t otime = 0;
    
    if(servo1trigger == 0)
        return; 
    
    int32_t error = ps1.pressure - p;
    
    if((error < 250) && (error > -250)){
        ps1okf = true;
    }else {
        ps1okf = false;
    } 
    
    if(otime != 0){     // pause time for motor reverse direction.
        otime--;
        pid1.i = 0;
        return;
    }
   
    
    
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
    
   
    
    int32_t output = (error * ps1.kp) + (pid1.i * ps1.ki); // + (pid1.d * ps1.kd);
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
    
    int32_t error = ps2.pressure - p;
    
    if((error < 200) && (error > -200)){
        ps2okf = true;
    }else {
        ps2okf = false;
    }
    
    if(otime != 0){     // pause time for motor reverse direction.
        otime--;
        pid2.i = 0;
        return;
    }

    

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
   
    
    int32_t output = (error * ps2.kp) + (pid2.i * ps2.ki); // + (pid2.d * ps2.kd);
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
/*
 *  servo operate mode
 */
uint16_t servo_setmode(SERVO_MODE m) {
    servomode = m;
    return 1;
}

/*
 *  set probe settings.
 */
void servo_setprobe(SERVOPROBE p, PRESSET data) {

    if (p == PR) {
        ps1 = data;
        ps1.pressure = get_p1zeropressure() + ps1.pressure;
        return;
    }
    if (p == PL) {
        ps2 = data;
        ps2.pressure = get_p2zeropressure() + ps2.pressure;
        return;
    }
}

/*
 * 
 */
void servo_cal(SERVOPROBE p, CALITEM item, uint16_t value){
    PRESSET *presset; 
    int16_t zeropres;
    if(p == PR){
       presset = &ps1;  
       zeropres = get_p1zeropressure();
    } else {
       presset = &ps2;
       zeropres = get_p2zeropressure();
    }
    
    switch(item){
        case CAL_PRESSURE:
            presset->pressure = zeropres + value;
            break;
        case CAL_ILIMIT:
            presset->imax = value;
            break;
        case CAL_OLIMIT:
            presset->outlimit = value;
            break;
        case CAL_KP:
            presset->kp = value;
            break;
        case CAL_KI:
            presset->ki = value;
            break;
        case CAL_KD:
            presset->kd = value;
            break;
        default:
            break;
    }  
    pid1.d = 0;
    pid1.i = 0;
    perror1 = 0;
    pid2.d = 0;
    pid2.i = 0;
    perror2 =0;       
}