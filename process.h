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

    typedef enum {
        FULLUP,
        FULLDOWN,
        PARTUP,
        PARTDOWN
    } SWSTATUS;

    typedef enum {
        NOEVENT,
        CLICKED,
        PRESSED,
    } SWEVENT;
    
    typedef enum {
        START,
        INIT,
        FINISH,
    } POWERONSTATE;    
    
    typedef enum {
        CAL_START,
        CAL_RUN,
                
    }CALSTATE;

    typedef enum {
        MSG_SEND,
        MSG_RECV
    } MSG_STATE;

    
void loop1ms(void);
void loop100us(void);  

ENCSW encswRead(void);
ENCSWEVENT encswEvent(void);
void encswUpdate(void);


void display_On(void);
void display_Off(void);

void setCH1Value(int16_t p);

void testMotor(void);
void test_Probe1(void);
void test_SetTestValue(int16_t v);

void set_ADCValueCH0(int16_t value);
void set_ADCValueCH1(int16_t value);

SWSTATUS sw_debounce(uint16_t sw, uint16_t* swstate);

void proc_actionswitch(void);
SWEVENT get_actionswitch(void);

//void run_poweron(void);
//void run_operate(void);
//void run_commerror(void);
//void run_cal(void);


#ifdef	__cplusplus
}
#endif

#endif	/* DUALMOTOR_H */

