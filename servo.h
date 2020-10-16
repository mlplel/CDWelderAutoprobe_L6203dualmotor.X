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
        uint16_t    Kp;
        uint16_t    Ki;
        uint16_t    Kd;
        uint32_t    i;
        uint32_t    d;
    }PID_TEMRS;
    
    typedef enum {
        SERVO_PR,
        SERVO_PL,
        SERVO_BOTH,
        SERVO_NONE
    }SERVO_MODE;
    
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
    
 /**
  @Summary
  
  @Description
   
  @Preconditions
    
  @Returns
    
  @Param
   
  @Example 
    
*/    
     
    void servo_trigger(SERVO_MODE m);
    
    void servo1_run(int16_t);
    void servo1_stop(void);
    void servo2_run(int16_t);
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


#ifdef	__cplusplus
}
#endif

#endif	/* SERVO_H */

