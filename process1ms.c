/* 
 * File:   process1ms.c
 * Author: mjacobs
 *
 * Created on December 12, 2018, 8:56 AM
 */
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/system.h"

#include "dualmotor.h"
#include "qei.h"
#include "display.h"

static ENCSW encsw = SW_INVALID;
static ENCSWEVENT encswevent = SW_NOEVENT;
static int16_t encvalue = 0;
static int16_t adcvalue = 0;


// called ever 1 ms.
void loop1ms(void){ 
    static uint8_t displayloop = 0;
    
    
    encswUpdate();    
    encvalue = (qei_ReadPos() >> 2);     
 
    ENCSWEVENT event = encswEvent();
    if(event == SW_CLICKED){
        qei_WritePos(0);
        encvalue = 0;
    }
    
    displayloop++;
    if(displayloop == 100){
        displayloop = 0;
        loopDisplay();
    }
    
}

void loopDisplay(void){
    
    if(i2c_Ready() == I2C_STATUS_IDLE){
        display_Value(adcvalue);
    
        display_Line3(encvalue);
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

void setStrainValue(int16_t val){
    adcvalue = val;
}