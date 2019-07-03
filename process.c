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

//static int16_t ch0pressure;
static int16_t ch1pressure;

//static int16_t ch0zeropressure;


static ENCSW encsw = SW_INVALID;
static ENCSWEVENT encswevent = SW_NOEVENT;
static int16_t adcvalue = 0;
static PROBE_ACTION probeaction = PROBEUP;

static int16_t testvalue = 0;

static int16_t adcvaluech0 = 0;
static int16_t adcvaluech1 = 0;

static uint16_t actionswitch = 0xFFFF;
static uint16_t procstatus = 0x0000;



// called every 100 us
void loop100us(void){
    
    //IO_RC3_Toggle(); 
    MOTOR_MOTION mm = motor1_isMotion();
    if (mm == MOTOR_UPMOTION) {
        if (get_probe1limit() == PROBE_UPLIMIT) {
            motor1_off();
        }
        if (get_probe2limit() == PROBE_UPLIMIT) {
            motor2_off();
        }
    } else if (mm == MOTOR_DOWNMOTION) {
        if (get_probe1limit() == PROBE_DOWNLIMIT) {
            motor1_off();
        }
        if (get_probe2limit() == PROBE_DOWNLIMIT) {
            motor2_off();
        }
    }    
}

// called every 1 ms.
void loop1ms(void){ 
    static uint16_t count10ms = 0;   
    
    
    count10ms++;    
    if(count10ms == 10){
        count10ms = 0;
        // process control panel here.
        commloop();             
    }  
    
    
    uint16_t temp = ACTION_GetValue();
    SWSTATUS swstat = sw_debounce(temp, &actionswitch);
    if(swstat == FULLDOWN){
        // action trigger.
        
        procstatus = procstatus | 0x0010;
     
        
        
    }else if(swstat == FULLUP){
        
        procstatus = procstatus & 0xFFEF;
     
    }
    
    
    
    //setP1PressureIndex(3);
    //testvalue = getP1Pressure();
    //testvalue = encvalue;
 
    ENCSWEVENT event = encswEvent();
    if(event == SW_CLICKED){
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

void commloop(void){
   
    MAINMSG msg;
    msg.command = MSG_testmode1.command;
    msg.data1 = adcvaluech0;
    //msg.data1 = get_p1zeropressure();
    msg.data2 = adcvaluech1;
    //msg.data2 = get_p2zeropressure();
    msg.data3 = procstatus;
    send_msg(msg);
    
    if(is_newmsg()){
        msg = get_msg();
        if(msg.validf){
            if(msg.command == RPY_status.command){
                CTLCMD cc = msg.data1;
                switch(cc){
                    
                    case TESTPROBE1:
                        encswevent = SW_CLICKED;
                        if((msg.data3 > 0) & (msg.data3 < 16)){
                            //only update if valid
                            set_p1pressureindex(msg.data3);
                        }
                        break;
                 
                    
                    default:
                        break;
                }                
            }     
        }        
    }    
}



ENCSW encswRead(void){
    return encsw;    
}
ENCSWEVENT encswEvent(void){
    ENCSWEVENT event = encswevent;
    encswevent = SW_NOEVENT;
    return event;
}

void encswUpdate(void){
    static uint8_t encswreg = 0xFF;
    static uint16_t statecnt = 0;    
    
    // debounce switch
    encswreg = encswreg << 1;
    if(LIM1_GetValue()){        
        encswreg = encswreg | 1;        
    }
    else{
        encswreg = encswreg & 0xFE;
    }
    
    if(encswreg == 0xFF){
        switch(encsw){
            case SW_UP: 
                if(statecnt == 0xFFFF) return;
                statecnt++;
                return;
            case SW_DOWN:
                if(statecnt < 1000)
                    encswevent = SW_CLICKED;
                else
                    encswevent = SW_LCLICKED;
                encsw = SW_UP;
                statecnt = 0;
                return;                
            case SW_INVALID:
                encsw = SW_UP;
                statecnt = 0;
                return; 
            default:
                return;            
        }        
    }
    else if(encswreg == 0){
        switch(encsw){
            case SW_UP:
                encsw = SW_DOWN;
                statecnt = 0;
                return;
            case SW_DOWN:
                if(statecnt == 0xFFFF) return;
                statecnt++;
                return;
            default:
                return;             
        }                 
    }        
}

void setCH1Value(int16_t p){
    ch1pressure = p;
}


void test_Probe1(void){
  
    if(probeaction == PROBEDOWN){
        servo_Trigger(SERVO1);
        //motor1_On();
        //motor1_Move(encvalue * 10, MOTOR_DOWNMOTION);
    }
    else{
        servo1_Stop();
        motor1_on();
        motor1_Move(1200, MOTOR_UPMOTION);
    }
}

void set_ADCValueCH0(int16_t value){
    adcvaluech0 = value;
}
void set_ADCValueCH1(int16_t value){
    adcvaluech1 = value;
}

void test_SetADCValue(int16_t value){
    adcvalue = value;
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


