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


static uint16_t rxdata[4];

//static int16_t ch0pressure;
static int16_t ch1pressure;

//static int16_t ch0zeropressure;


static ENCSW encsw = SW_INVALID;
static ENCSWEVENT encswevent = SW_NOEVENT;
static int16_t encvalue = 0;
static int16_t adcvalue = 0;

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
    static uint16_t count10ms = 0;
    const uint16_t txdata[4] = {0x1111, 0x4444, 0x7777, 0xAAAA };
    
    
    ENCA_Toggle();
    
    count10ms++;
    
    if(count10ms == 10){
        count10ms = 0;
        // process control panel here.
        int i = 0;
        SD2_CS_SetLow();
        for(;i < 4;i++){
            SPI2BUF = txdata[i];
            // rxdata[i] = SPI2BUF;
        }
        
        
    }
      
    
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



void __attribute__ ( ( interrupt, no_auto_psv ) ) _SPI2Interrupt(void){
    
    IFS2bits.SPI2IF = 0;
    
    SD2_CS_SetHigh();
    int i = 0;
    for(;i<4;i++){
        rxdata[i] = SPI2BUF;
    }
    
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _SPI2ErrInterrupt(void){
    
    
    SPI2STATbits.SPIEN = 0;
    IFS2bits.SPI2EIF = 0;
    
    SPI2STAT = 0x8014;
    
}