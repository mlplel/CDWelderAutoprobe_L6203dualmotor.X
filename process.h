/* 
 * File:   dualmotor.h
 * Author: mjacobs
 *
 * Created on December 12, 2018, 8:56 AM
 */

#ifndef PROCESS_H
#define	PROCESS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define FCY     30170937UL
    
#include <libpic30.h>
#include "xc.h"
#include "stdint.h"

    typedef enum {
        SW_DOWN = 0,
        SW_UP = 1,
        SW_INVALID = 2,
    } ENCSW;

    typedef enum {
        SW_NOEVENT = 0,
        SW_CLICKED = 1,
        SW_LCLICKED = 2,
    } ENCSWEVENT;

    typedef enum {
        PRES1,
        PRES2
    } PRESSURE_CH;

    typedef enum {
        PROBEUP,
        PROBEDOWN
    } PROBE_ACTION;
    

    
void loop1ms(void);
void loop100us(void);  
void loopDisplay(void);

ENCSW encswRead(void);
ENCSWEVENT encswEvent(void);
void encswUpdate(void);


void display_On(void);
void display_Off(void);

void setCH1Value(int16_t p);

void testMotor(void);
void test_SetADCValue(int16_t value);
void test_Probe1(void);
void test_SetTestValue(int16_t v);


#ifdef	__cplusplus
}
#endif

#endif	/* DUALMOTOR_H */

