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
#include "sh1106.h"
#include "motor.h"
#include "adc.h"

static ENCSW encsw = SW_INVALID;
static ENCSWEVENT encswevent = SW_NOEVENT;
static int16_t encvalue = 0;
static int16_t adcvalue = 0;
static int16_t testvalue = 0;


static uint8_t fdisplay = 1;
static uint8_t fmpressure = 0;

static int16_t pressuresetvalue = 0;
static int16_t ierror = 0;
static int16_t perror = 0;


// called ever 1 ms.
void loop1ms(void){ 
    static uint8_t displayloop = 0;    
    
    encswUpdate();    
    encvalue = (qei_ReadPos() >> 2);
    int pre = encvalue;
    if(pre < -200)
        pre = -100;
    else if(pre > 500)
        pre = 500;
    pressuresetvalue = pre; 
 
    ENCSWEVENT event = encswEvent();
    if(event == SW_CLICKED){
        //qei_WritePos(0);
        //encvalue = 0;
        testMotor();
    }
    
    
    // display update at 100 ms
    displayloop++;
    if(displayloop == 100){
        displayloop = 0;
        loopDisplay();
    }    
}

void loopDisplay(void){
    
    if((i2c_Ready() == I2C_STATUS_IDLE) && fdisplay){
        display_Value(adcvalue);
    
        display_Line3(encvalue);
        //display_Line3(triggervalue);
        //display_Line3(testvalue);
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

void setStrainValue(int16_t val){
    adcvalue = val;
}

void testMotor(void){
    
    static uint8_t mode = 1;
    
    if(mode){
        // move motor down with pressure
        fmpressure = 8;
        fdisplay = 0;
        ierror = 0;
        // motor_MoveDown();
        motor_On();
        motor_Move(50);
        mode = 0;
    }
    else{
         IO_RC3_Toggle();
        // move motor up to limit
        motor_On();
        motor_Move(-100);
        mode = 1;
    } 
}

void processStrainValue(int16_t val){
   adcvalue = val;  
   if(fmpressure == 0) return;
   
   int16_t error = pressuresetvalue - val;
   int16_t derror = error - perror;
   perror = error;
   if(derror > 40) derror = 40;
   if(derror < -40) derror = -40;
   
   ierror = ierror + error;
   if(ierror > 40) ierror = 40;
   if(ierror < -40) ierror = -40;
   
   int8_t kp;
   
   if((error < 2) && (error > -2)){
       fmpressure = fmpressure - 1;
       if(fmpressure == 0){
       motor_Hold();
       fdisplay = 1;
       }
   }
   else {
        error = (error * 2) + ierror + derror;

        if(error > 127)
            error = 127;
        if(error < -128)
            error = -128;
        kp = error;

        motor_Move(kp);
   }   
}

void testValues(int16_t val1, int16_t val2){
    
    testvalue = val2;    
    processStrainValue(val1);     
}