/* 
 * File:   motor.h
 * Author: 
 *
 * Created on December 6, 2018, 10:44 AM
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

#ifndef MOTOR_H
#define	MOTOR_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum {
        MOTOR_NOMOTION,
        MOTOR_UPMOTION,
        MOTOR_DOWNMOTION,
    } MOTOR_MOTION;

    typedef enum {
        PROBE_UPLIMIT,
        PROBE_DOWNLIMIT,
        PROBE_NOLIMIT
    }PROBE_LIMIT;

    
    uint16_t motor_ReadLimits1(void);
    
    void motor_MoveUp(void);
    void motor_MoveDown(void);
    void motor_MoveUptoLimit(void);
    void motor_MoveDowntoLimit(void);
    void motor1_Hold(void);
    void motor2_Hold(void);
    void motor1_off(void);
    void motor2_off(void);
    MOTOR_MOTION motor1_isMotion(void);
    MOTOR_MOTION motor2_isMotion(void);
    
    void motor1_on(void); 
    void motor2_on(void);
    void motor1_Move(uint16_t val, MOTOR_MOTION motion);
    void motor2_Move(uint16_t val, MOTOR_MOTION motion);
    
    PROBE_LIMIT get_probe2limit(void);
    PROBE_LIMIT get_probe1limit(void);
    void probe1_SetStartPos(void);
    void probe2_SetStartPos(void);
    


#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_H */

