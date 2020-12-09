/* 
 * File:   process1ms.c
 * Author: mjacobs
 *
 * Created on December 12, 2018, 8:56 AM
 */
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/system.h"

#include "process.h"
#include "motor.h"
#include "adc.h"
#include "servo.h"
#include "settings.h"
#include "comm.h"
#include "messages.h"

/*
 *  file scope function 
 */
void processmsg(void);
void process_switchevent(SWEVENT swe);
void set_actionswitch(SWEVENT se);


static MODE runmode = MODE_POWERON;
static MAINMSG lastmsg = {CMD_status, 0x00, 0x00, 0x00, false};
static MAINMSG lastrpy = {RPY_none, 0x00, 0x00, 0x00, false};
MAINMSG statusmsg = {CMD_status, 0x00, 0x00, 0x00, false};
static PROBE_ACTION probeaction = PROBEUP;

static int16_t testvalue = 0;

static int16_t adcvaluech0 = 0;
static int16_t adcvaluech1 = 0;

static uint16_t actionswitch = 0xFFFF;
static SWEVENT actionswitchevent = NOEVENT;
static uint16_t procstatus = 0x0000;


/*
 * called every 100 us.
 */
void loop100us(void){    
    // test for probes at limits. 
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

/*
 * called every 1ms.
 */
void loop1ms(void){  
    static uint16_t outputactivetime = 0;
    static bool outputactivef = false;
    proc_actionswitch();
    processmsg();    
    process_switchevent(get_actionswitch());
    
    /*
    if(outputactivetime != 0){
        outputactivetime--;
        if(outputactivetime == 0){
            TRIG_SetHigh();
            set_actionswitch(PRESSED);
        }
    }  
     */ 
    
    if(outputactivef == true){
        outputactivetime++;
        if(outputactivetime == 3){
            outputactivetime--;
            TRIG_SetHigh();
            Nop();
            if(TRIG_GetValue() == 1){
                outputactivetime++;
            }            
        }
        if(outputactivetime >= 8){
            outputactivef = false;
            set_actionswitch(PRESSED);
        }        
    }    
    if(servo_isoutputactive()){
        TRIG_SetLow();
        outputactivetime = 0;
        outputactivef = true;
        servo1_stop();
        servo2_stop();
    }
}
/*
 * 
 */
void process_switchevent(SWEVENT swe){    
    if(swe != PRESSED){
        return;
    }
    if (probeaction == PROBEUP) {
        probeaction = PROBEDOWN;
        servo_trigger();
    } else {
        probeaction = PROBEUP;
        servo1_stop();
        motor1_on();
        motor1_Move(900, MOTOR_UPMOTION);

        servo2_stop();
        motor2_on();
        motor2_Move(900, MOTOR_UPMOTION);
    }
}


/*
 * 
 */
void processmsg(){
    if(is_txbusy() == true){
        // last message not processed don't do another.
        return;
    }   
    if(!is_newmsg()){
        // have to send a message before can get a reply.
        send_msg(lastmsg);
        return;
    }
    MAINMSG msg = get_msg();
    if(msg.validf == false){
        send_msg(lastmsg);
        return;
    }
    lastrpy = msg;
    
    switch(lastrpy.command){
        
        case RPY_setpl1:
            servo_cal(PL, CAL_PRESSURE, lastrpy.data1);
            servo_cal(PL, CAL_ILIMIT, lastrpy.data2);
            servo_cal(PL, CAL_OLIMIT, lastrpy.data3);          
            break;
        case RPY_setpl2:
            servo_cal(PL, CAL_KP, lastrpy.data1);
            servo_cal(PL, CAL_KI, lastrpy.data2);
            servo_cal(PL, CAL_KD, lastrpy.data3);
            break;
        case RPY_setpr1:
            servo_cal(PR, CAL_PRESSURE, lastrpy.data1);
            servo_cal(PR, CAL_ILIMIT, lastrpy.data2);
            servo_cal(PR, CAL_OLIMIT, lastrpy.data3);
            break;
        case RPY_setpr2:
            servo_cal(PR, CAL_KP, lastrpy.data1);
            servo_cal(PR, CAL_KI, lastrpy.data2);
            servo_cal(PR, CAL_KD, lastrpy.data3);
            break;
        case RPY_runboth:
            statusmsg.data3 = MODE_RUNBOTH;
            runmode = MODE_RUNBOTH;
            servo_setmode(SERVO_BOTH);
            break;
        case RPY_runpl:
            statusmsg.data3 = MODE_RUNPL;
            runmode = MODE_RUNPL;
            servo_setmode(SERVO_PL);
            break;
        case RPY_runpr:
            statusmsg.data3 = MODE_RUNPR;
            runmode = MODE_RUNPR;
            servo_setmode(SERVO_PR);
            break;
        case RPY_idle:
            statusmsg.data3 = MODE_IDLE;
            runmode = MODE_IDLE;
            servo_setmode(SERVO_NONE);
            break;
        case RPY_calpl:
            statusmsg.data3 = MODE_CALPL;
            runmode = MODE_CALPL;
            servo_setmode(SERVO_CALPL);              
            servo_cal(PL, lastrpy.data1, lastrpy.data2);            
            break;
        case RPY_calpr:
            statusmsg.data3 = MODE_CALPR;
            runmode = MODE_CALPR;
            servo_setmode(SERVO_CALPR);
            servo_cal(PR, lastrpy.data1, lastrpy.data2);          
            break;
        case RPY_calzero:
            statusmsg.data3 = MODE_CALZERO;
            runmode = MODE_CALZERO;
            set_p1zeropressure();
            set_p2zeropressure();
            break;
        case RPY_status:
            // status update.
            lastmsg = statusmsg;
            break;        
        case RPY_init:
            lastmsg = statusmsg;
            runmode = MODE_INIT;
            // set startup code here.
            servo_setmode(SERVO_NONE);
            break;
        case RPY_poweron:
            //lastmsg.command = CMD_init;
            lastmsg = statusmsg;
            runmode = MODE_INIT;
            // may have to do a restart here.
            servo_setmode(SERVO_NONE);
            break;            
        default:
            statusmsg.data3 = 0x55;
            break;
    }
    PRESSUREOKF pres = servo_checkprobpressure();
    uint16_t pressurestat = 0;
    if(pres.p1f == true)
        pressurestat = pressurestat | 0x0001;
    if(pres.p2f == true)
        pressurestat = pressurestat | 0x0002;
    lastmsg.data3 = pressurestat;                
    send_msg(lastmsg);
    
    // testing
    statusmsg.data1 = adcvaluech0;
    statusmsg.data2 = adcvaluech1;

}


/*
 * 
 */
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

/*
 * 
 */
void set_actionswitch(SWEVENT se){
    actionswitchevent = se;
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
/*
 * current state of switch, swstate 16bits of past switch state
 */
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

