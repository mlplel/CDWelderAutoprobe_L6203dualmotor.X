/* 
 * File:   dualmotor.h
 * Author: mjacobs
 *
 * Created on December 12, 2018, 8:56 AM
 */

#ifndef DUALMOTOR_H
#define	DUALMOTOR_H

#ifdef	__cplusplus
extern "C" {
#endif

#define FCY     30170937U
    
#include <libpic30.h>
#include "xc.h"
#include "stdint.h"

typedef enum 
{
    SW_DOWN = 0,       
    SW_UP =  1,       
    SW_INVALID = 2,       
} ENCSW;
typedef enum
{
    SW_NOEVENT = 0,
    SW_CLICKED = 1,
    SW_LCLICKED = 2,        
}ENCSWEVENT;
    
void loop1ms(void);
void loop100us(void);  
void loopDisplay(void);

ENCSW encswRead(void);
ENCSWEVENT encswEvent(void);
void encswUpdate(void);



void setStrainValue(int16_t val);



#ifdef	__cplusplus
}
#endif

#endif	/* DUALMOTOR_H */

