/* 
 * File:   settings.h
 * Author:
 *
 * Created on April 18, 2019, 10:58 AM
 */
/*
    Copyright 2022 Michael Jacobs

    Permission is hereby granted, free of charge, to any person obtaining a 
    copy of this software and associated documentation files (the "Software"), 
    to deal in the Software without restriction, including without limitation 
    the rights to use, copy, modify, merge, publish, distribute, sublicense, 
    and/or sell copies of the Software, and to permit persons to whom the 
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included 
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
    DEALINGS IN THE SOFTWARE.
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

