/* 
 * File:   process1ms.c
 * Author: mjacobs
 *
 * Created on December 12, 2018, 8:56 AM
 */
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/system.h"

#include "process.h"
#include "qei.h"
#include "motor.h"
#include "adc.h"
#include "servo.h"
#include "settings.h"
#include "comm.h"
#include "messages.h"


static RUNMODE runmode = MODE_POWERON;
static RUNMODE prevmode = MODE_NONE;

//static int16_t ch0pressure;
static int16_t ch1pressure;

//static int16_t ch0zeropressure;


static ENCSW encsw = SW_INVALID;
static ENCSWEVENT encswevent = SW_NOEVENT;
static PROBE_ACTION probeaction = PROBEUP;

static int16_t testvalue = 0;

static int16_t adcvaluech0 = 0;
static int16_t adcvaluech1 = 0;

static uint16_t actionswitch = 0xFFFF;
static SWEVENT actionswitchevent = NOEVENT;
static uint16_t procstatus = 0x0000;



// called every 100 us
void loop100us(void){
    
    //IO_RC3_Toggle(); 
    MOTOR_MOTION mm1 = motor1_isMotion();
    MOTOR_MOTION mm2 = motor2_isMotion();
    if (mm1 == MOTOR_UPMOTION) {
        if (get_probe1limit() == PROBE_UPLIMIT) {
            motor1_off();
        }
    } else if (mm1 == MOTOR_DOWNMOTION) {
        if (get_probe1limit() == PROBE_DOWNLIMIT) {
            motor1_off();
        }
    }

    if (mm2 == MOTOR_UPMOTION) {
        if (get_probe2limit() == PROBE_UPLIMIT) {
            motor2_off();
        }
    } else if (mm2 == MOTOR_DOWNMOTION) {
        if (get_probe2limit() == PROBE_DOWNLIMIT) {
            motor2_off();
        }
    }   
}

// called every 1 ms.
void loop1ms(void){     
    // main run mode selected here
    switch(runmode){
        
        case MODE_POWERON:
            run_poweron();
            break;            
        case MODE_RUN:
            run_operate();
            break;            
        case MODE_COMMERROR:
            run_commerror();
            break;
        case MODE_CAL:
            run_cal();
            break;
            
        default:
            break;
    }
  
    proc_actionswitch();
    
    
    //setP1PressureIndex(3);
    //testvalue = getP1Pressure();
    //testvalue = encvalue;
 
    SWEVENT swe = get_actionswitch();
    if(swe == PRESSED){
        //qei_WritePos(0);
        //encvalue = 0;
        //testMotor();
        if (probeaction == PROBEUP) {
            probeaction = PROBEDOWN;
        } else {
            probeaction = PROBEUP;
        }
        test_Probe1();
    }        
}

void proc_actionswitch(){
    
    SWSTATUS swstat = sw_debounce(ACTION_GetValue(), &actionswitch);
    if(swstat == FULLDOWN){
        // action trigger.  
        if((procstatus & 0x0010) == 0) actionswitchevent = PRESSED;
        procstatus = procstatus | 0x0010;        
        
    }else if(swstat == FULLUP){        
        procstatus = procstatus & 0xFFEF;     
    }
}

SWEVENT get_actionswitch(){
    SWEVENT swe = actionswitchevent;
    actionswitchevent = NOEVENT;
    return swe;
}


ENCSW encswRead(void){
    return encsw;    
}
ENCSWEVENT encswEvent(void){
    ENCSWEVENT event = encswevent;
    encswevent = SW_NOEVENT;
    return event;
}



void setCH1Value(int16_t p){
    ch1pressure = p;
}


void test_Probe1(void){
  
    if(probeaction == PROBEDOWN){
        servo_trigger(SERVOBOTH);
        
    }
    else{
        servo1_stop();
        motor1_on();
        motor1_Move(800, MOTOR_UPMOTION);
        
        servo2_stop();
        motor2_on();
        motor2_Move(800, MOTOR_UPMOTION);
        
    }
}

void set_ADCValueCH0(int16_t value){
    adcvaluech0 = value;
}
void set_ADCValueCH1(int16_t value){
    adcvaluech1 = value;
}


void test_SetTestValue(int16_t v){
    testvalue = v;
}

// sw current state of switch, swstate 16bits of past switch state
SWSTATUS sw_debounce(uint16_t sw, uint16_t* swstate){
    SWSTATUS sws;
    *swstate = (*swstate) << 1;
    if(sw != 0){
        (*swstate)++;
    }
    if(*swstate == 0xFFFF){
        sws = FULLUP;
        return sws;
    }else if(*swstate == 0x0000){
        sws = FULLDOWN;
        return sws;
    }else if((*swstate & 0x0001) == 0x0001){
        sws = PARTUP;
        return sws;
    }else 
        sws = PARTDOWN;
        return sws;    
    
}
// called till power up process finished
void run_poweron() {
    static POWERONSTATE postate = START;
    static uint16_t errorcnt = 0;
    MAINMSG msg;
    if (is_newmsg()) {
        msg = get_msg();
    } else msg = RPY_none;

    switch (postate) {

        case START:
            send_msg(MSG_poweron);
            if ((msg.validf == true) && (msg.command == RPO_init)) {
                postate = INIT;
            }
            break;

        case INIT:
            // init process goes here.

            postate = FINISH;
            break;

        case FINISH:
            // powerup finish process goes here.
            runmode = MODE_RUN;
            break;

        default:
            break;
    }
    if(msg.command == RPO_error){
        errorcnt++;
        if(errorcnt == 3){
            errorcnt = 0;
            prevmode = runmode;
            runmode = MODE_COMMERROR;   
        }
    }    
}

// called while in the operate mode
void run_operate(){    
     
    MAINMSG msg;    
    if (is_newmsg()) {
        msg = get_msg();
    } else msg = RPY_none;
    
    
    switch(msg.command){        
        
        case RPO_none:            
            break;
         
        // command to set probe pressures    
        case RPO_probepressure:
            set_p1pressureindex(msg.data1);
            set_p2pressureindex(msg.data2);            
            break;
        
        // command to switch to Calibrate and test mode
        case RPO_calmode:
            runmode = MODE_CAL;
            break;
        
        default:
            break;
    }   
    
    msg.command = MSG_testmode1.command;
    msg.data1 = adcvaluech0;    
    msg.data2 = adcvaluech1;
    msg.data3 = procstatus;
    send_msg(msg);  
}

void run_commerror(){
 // process restart of communication with control panel here.   
  
    //test setup
    runmode = prevmode;
    prevmode = MODE_NONE;
    
    
}

//calibrate and test operations
void run_cal(){
    static CALSTATE calstate = CAL_START;
    
    MAINMSG msg;

    switch (calstate) {

        case CAL_START:
            if(send_msg(MSG_calmode) == 0){
                calstate = CAL_RUN;
            }
            break;
            
        case CAL_RUN:
            
            
                msg.command = MSG_testmode1.command;
                    msg.data1 = adcvaluech0;    
                 msg.data2 = adcvaluech1;
            msg.data3 = procstatus;
            send_msg(msg);  
            break;

        default:
            break;
    }

    
}


