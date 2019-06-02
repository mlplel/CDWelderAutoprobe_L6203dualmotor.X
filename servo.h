/* 
 * File:   servo.h
 * Author: mjacobs
 *
 * Created on February 11, 2019, 2:08 PM
 */

#ifndef SERVO_H
#define	SERVO_H

#include "xc.h"

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
        SERVO1,
        SERVO2,
        SERVOBOTH
    }SERVO_MODE;
    
    
    void servo_Init(void);
    
    void servo_Trigger(SERVO_MODE m);
    
    void servo_1Run(int16_t );
    void servo1_Stop(void);


#ifdef	__cplusplus
}
#endif

#endif	/* SERVO_H */

