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
#include "sh1106.h"
#include "motor.h"
#include "adc.h"
#include "servo.h"
#include "settings.h"

//static int16_t ch0pressure;
static int16_t ch1pressure;

//static int16_t ch0zeropressure;


static ENCSW encsw = SW_INVALID;
static ENCSWEVENT encswevent = SW_NOEVENT;
static int16_t encvalue = 0;
static int16_t adcvalue = 0;

static uint8_t fdisplay = 1;

static PROBE_ACTION probeaction = PROBEUP;

static int16_t testvalue = 0;


// called every 100 us
void loop100us(void){
    
    //IO_RC3_Toggle(); 
    MOTOR_MOTION mm = motor1_isMotion();
    if(mm == MOTOR_UPMOTION){
        if(probe1_GetLimit() == PROBE_UPLIMIT){
            motor1_Off();
        }
    }
    else if(mm == MOTOR_DOWNMOTION){        
    if(probe1_GetLimit() == PROBE_DOWNLIMIT)
       motor1_Off();
    }
}

// called every 1 ms.
void loop1ms(void){ 
    static uint8_t displayloop = 0;    
    
    encswUpdate();    
    encvalue = (qei_ReadPos() >> 2);
    //encvalue *= 10;
    if(encvalue < 0){
        encvalue = 0;
        qei_WritePos(encvalue);
    }
    else if(encvalue > 14){
        encvalue = 14;
        qei_WritePos(encvalue * 4);
    }
    setP1PressureIndex(encvalue);
    testvalue = getP1Pressure();
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
    
    // display update at 100 ms
    displayloop++;
    if(displayloop == 200){
        displayloop = 0;
        loopDisplay();
    }    
}



void display_On(void){
    fdisplay = 1;
}

void display_Off(void){
    fdisplay = 0;
}

void loopDisplay(void){
    
    if((i2c_Ready() == I2C_STATUS_IDLE) && fdisplay){
        display_Value(adcvalue);
    
        //display_Line3(encvalue);
        //display_Line3(triggervalue);
        display_Line3(testvalue);
        //display_Line3(ch1zeropressure);
        
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
    if(IO_RC8_GetValue()){        
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
        motor1_On();
        motor1_Move(1200, MOTOR_UPMOTION);
    }
}

void test_SetADCValue(int16_t value){
    adcvalue = value;
}

void test_SetTestValue(int16_t v){
    testvalue = v;
}



