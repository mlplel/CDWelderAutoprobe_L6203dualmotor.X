/* 
 * File:   servo.h
 * Author: mjacobs
 *
 * Created on February 11, 2019, 2:08 PM
 */

#ifndef SERVO_H
#define	SERVO_H

#include "xc.h"
#include <stdbool.h>


#ifdef	__cplusplus
extern "C" {
#endif 
    
    typedef struct {
        uint32_t    i;
        uint32_t    d;
    }PID_TEMRS;  
   

    typedef enum {
        SERVO_PR,
        SERVO_PL,
        SERVO_BOTH,
        SERVO_NONE,
        SERVO_CALPL,
        SERVO_CALPR
    } SERVO_MODE;
    
     typedef struct {
        int16_t pressure;
        int16_t kp;
        int16_t ki;
        int16_t kd;
        int16_t imax;
        int16_t outlimit;   
        bool validf;
    }PRESSET;
    
    typedef enum {
        PR = 1,
        PL
    } SERVOPROBE;

     typedef enum {
        CAL_PRESSURE = 1,
        CAL_ILIMIT = 2,
        CAL_OLIMIT = 3,
        CAL_KP = 4,
        CAL_KI = 5,
        CAL_KD = 6,
        CAL_NONE = 7
    } CALITEM;
   
    
    
    
    
 /**
  @Summary
  
  @Description
   
  @Preconditions
    
  @Returns
    
  @Param
   
  @Example 
    
*/    
bool servo_isoutputactive(void);    
    
    
    
 /**
  @Summary
  
  @Description
   
  @Preconditions
    
  @Returns
    
  @Param
   
  @Example 
    
*/ 
void servo_trigger(void);
    


/**
  @Summary
  
  @Description
   
  @Preconditions
    
  @Returns
    
  @Param
   
  @Example 
    
*/
    void servo1_run(int16_t);
    
    
    
/**
  @Summary
  
  @Description
   
  @Preconditions
    
  @Returns
    
  @Param
   
  @Example 
    
*/    
    void servo1_stop(void);
    
    
    
    
    
/**
  @Summary
  
  @Description
   
  @Preconditions
    
  @Returns
    
  @Param
   
  @Example 
    
*/    
    void servo2_run(int16_t);
    
    
    
    
/**
  @Summary
  
  @Description
   
  @Preconditions
    
  @Returns
    
  @Param
   
  @Example 
    
*/    
    void servo2_stop(void);
    
/**
  @Summary
  
  @Description
   
  @Preconditions
    
  @Returns
    
  @Param
   
  @Example 
    
*/  
uint16_t servo_setmode(SERVO_MODE m);

/**
  @Summary
  
  @Description
   
  @Preconditions
    
  @Returns
    
  @Param
   
  @Example 
    
*/
void servo_setprobe(SERVOPROBE p, PRESSET data);   
    
 /**
  @Summary
  
  @Description
   
  @Preconditions
    
  @Returns
    
  @Param
   
  @Example 
    
*/ 
void servo_cal(SERVOPROBE p, CALITEM item, uint16_t value);




 /**
  @Summary
  
  @Description
   
  @Preconditions
    
  @Returns
    
  @Param
   
  @Example 
    
*/ 

#ifdef	__cplusplus
}
#endif

#endif	/* SERVO_H */

