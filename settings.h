/* 
 * File:   settings.h
 * Author: mjacobs
 *
 * Created on April 18, 2019, 10:58 AM
 */

#ifndef SETTINGS_H
#define	SETTINGS_H

#include "xc.h"
#include "servo.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef struct {
        uint16_t kp;
        uint16_t ki;
    }PIDVALUE;
    
   

    void settings_init(void);    
    void set_p1pressureindex(uint16_t i);
    void set_p2pressureindex(uint16_t i);
    int16_t getP1Pressure(void);
    int16_t getP2Pressure(void);
    PIDVALUE get_P1pid(void);
    PIDVALUE get_P2pid(void);
    PRESSET getP1(void);
    PRESSET getP2(void);
    
    /*
    void setP1ZeroPressure(void);
    int16_t get_p1zeropressure(void);
    void setP2ZeroPressure(void);
    int16_t get_p2zeropressure();
*/
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* SETTINGS_H */

