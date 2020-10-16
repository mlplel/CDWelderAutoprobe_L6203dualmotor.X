/* 
 * File:   process1ms.c
 * Author: mjacobs
 *
 * Created on December 12, 2018, 8:56 AM
 */
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/system.h"

#include "process.h"
//#include "qei.h"
#include "motor.h"
#include "adc.h"
#include "servo.h"
#include "settings.h"
#include "comm.h"
#include "messages.h"

/*
 *  internal function 
 */
void processmsg(void);


static MODE runmode = MODE_POWERON;
static MAINMSG lastmsg = {CMD_poweron, 0x00, 0x00, 0x00, false};
static MAINMSG lastrpy = {RPY_none, 0x00, 0x00, 0x00, false};
MAINMSG statusmsg = {CMD_status, 0x00, 0x00, 0x00, false};

PRESSET pl, pr;


//static RUNMODE prevmode = MODE_NONE;

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
    
    // test for motor at limits. 
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
    
    /*
    // main run mode selected here
    switch(runmode){        
        case MODE_POWERON:
            run_poweron();
            break;            
        case MODE_RUNBOTH:           
        case MODE_RUNPL:
        case MODE_RUNPR:
            run_operate();
            break;
        case MODE_CALZERO:
            break;
        case MODE_CALPL:
            break;
        case MODE_CALPR:
            break;                   
        default:
            break;
    }
     */
    
    proc_actionswitch();
    processmsg();
    
    
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
            pl.pressure = lastrpy.data1;
            pl.imax = lastrpy.data2;
            pl.outlimit = lastrpy.data3;
            break;
        case RPY_setpl2:
            pl.kp = lastrpy.data1;
            pl.ki = lastrpy.data2;
            pl.kd = lastrpy.data3;
            break;
        case RPY_setpr1:
            pr.pressure = lastrpy.data1;
            pr.imax = lastrpy.data2;
            pr.outlimit = lastrpy.data3;
            break;
        case RPY_setpr2:
            pr.kp = lastrpy.data1;
            pr.ki = lastrpy.data2;
            pr.kd = lastrpy.data3;
            break;
        case RPY_runboth:
            statusmsg.data3 = MODE_RUNBOTH;
            runmode = MODE_RUNBOTH;
            servo_setprobe(PL, pl);
            servo_setprobe(PR, pr);
            servo_setmode(SERVO_BOTH);
            break;
        case RPY_runpl:
            statusmsg.data3 = MODE_RUNPL;
            runmode = MODE_RUNPL;
            servo_setprobe(PL, pl);
            servo_setmode(SERVO_PL);
            break;
        case RPY_runpr:
            statusmsg.data3 = MODE_RUNPR;
            runmode = MODE_RUNPR;
            servo_setprobe(PR, pr);
            servo_setmode(SERVO_PR);
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
            lastmsg.command = CMD_init;
            runmode = MODE_INIT;
            // may have to do a restart here.
            servo_setmode(SERVO_NONE);
            break;            
        default:
            break;
    }
    send_msg(lastmsg);
    
    // testing
    //statusmsg.data1 = adcvaluech0;
    //statusmsg.data2 = adcvaluech1;
    statusmsg.data1 = pl.pressure;
    statusmsg.data2 = pr.pressure;
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
        servo_trigger(SERVO_BOTH);        
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
    //static POWERONSTATE postate = START;
    //static uint16_t errorcnt = 0;
    
    //static uint16_t opmode;
    //static uint16_t data[12];
    MAINMSG msg;
    if (is_newmsg()) {
        msg = get_msg();
        if(msg.validf == true){
            lastmsg = msg;
        }
    }
    
    switch(lastmsg.command){
        case RPY_init:
            msg.command = CMD_init;
            msg.data1 = lastmsg.data1;
            // if we can reply to msg change to new mode
            if(send_msg(msg) == -1){    
                return;
            }
            runmode = lastmsg.data1;
            servo_setmode(SERVO_NONE); // disable servo till setup
            break; 
            
        case RPY_poweron:
        default:
            msg.command = CMD_poweron;
            send_msg(msg);
            break;
    }    
/*

    switch (postate) {

        case START:
            send_msg(MSG_poweron);
            if ((msg.validf == true) && (msg.command == RPO_init)) {
                opmode = msg.data1;
                postate = INIT;
            }
            break;

        case INIT:
            // init process goes here.
            send_msg(MSG_init);
            switch(msg.command){
                
                case RPO_initfinished:
                    postate = FINISH;
                    break;
                    
                default:
                    break;
                    
            }
            break;

        case FINISH:
            // powerup finish process goes here.
            if(send_msg(MSG_status) == -1){
                return;
            }
            runmode = MODE_RUN;
            break;

        default:
            break;
    }
 */
}

// called while in the operate mode
void run_operate(){
static PRESSET ppl, ppr;    
     
    MAINMSG msg;    
    if (is_newmsg()) {
        msg = get_msg();
        if(msg.validf == true){
            lastmsg = msg;
        }
    }       
    switch(lastmsg.command){       
        
        case RPY_setpl1:
            ppl.pressure = msg.data1;
            ppl.imax = msg.data2;
            ppl.outlimit = msg.data3;
            msg.command = CMD_init;
            msg.data1 = RPY_setpl1;
            send_msg(msg);
            break;
            
        case RPY_setpl2:
            ppl.kp = msg.data1;
            ppl.ki = msg.data2;
            ppl.ki = msg.data3;
            msg.command = CMD_init;
            msg.data1 = RPY_setpl2;
            send_msg(msg);
            break;
            
        case RPY_setpr1:
            ppr.pressure = msg.data1;
            ppr.imax = msg.data2;
            ppr.outlimit = msg.data3;
            msg.command = CMD_init;
            msg.data1 = RPY_setpr1;
            send_msg(msg);
            break;
            
        case RPY_setpr2:
            ppr.kp = msg.data1;
            ppr.ki = msg.data2;
            ppr.kd = msg.data3;
            msg.command = CMD_init;
            msg.data1 = RPY_setpr2;
            send_msg(msg);
            break;  
            
        case RPY_initfinished:
            if (runmode == MODE_RUNPL) {
                servo_setprobe(PL, ppl);
                servo_setmode(SERVO_PL);
            } else if (runmode == MODE_RUNPR) {
                servo_setprobe(PR, ppr);
                servo_setmode(SERVO_PR);
            } else if (runmode == MODE_RUNBOTH){
                servo_setprobe(PL, ppl);
                servo_setprobe(PR, ppr);
                servo_setmode(SERVO_BOTH);
            }
            msg.command = CMD_ok;
            msg.data1 = RPY_initfinished;
            send_msg(msg);            
            break;
         
        // command to set probe pressures    
        case RPY_probepressure:
            set_p1pressureindex(msg.data1);
            set_p2pressureindex(msg.data2);            
            break;
        
        // command to switch to Calibrate and test mode
        case RPY_calmode:
            runmode = MODE_CALPL;
            break;

        case RPY_none:
        default:
            msg.command = CMD_status;
            msg.data1 = adcvaluech0;
            msg.data2 = adcvaluech1;
            msg.data3 = procstatus;
            send_msg(msg);
            break;
    }   
    
      
}



//calibrate and test operations
void run_cal(){
    static CALSTATE calstate = CAL_START;
    
    MAINMSG msg;

    switch (calstate) {
        case CAL_RUN:
            msg.command = CMD_status;
            msg.data1 = adcvaluech0;
            msg.data2 = adcvaluech1;
            msg.data3 = procstatus;
            send_msg(msg);
            break;

        default:
            break;
    }
}


