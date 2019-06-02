/* 
 * File:   settings.h
 * Author: mjacobs
 *
 * Created on April 18, 2019, 10:58 AM
 */

#ifndef SETTINGS_H
#define	SETTINGS_H

#include "xc.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef struct {
        uint16_t kp;
        uint16_t ki;
    }PIDVALUE;

    void settings_init(void);    
    void setP1PressureIndex(uint16_t pres);
    int16_t getP1Pressure(void);
    PIDVALUE getP1Pid(void);
    
    void setP1ZeroPressure(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SETTINGS_H */

