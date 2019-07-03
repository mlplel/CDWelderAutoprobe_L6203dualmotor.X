/* 
 * File:   motor.h
 * Author: mjacobs
 *
 * Created on December 6, 2018, 10:44 AM
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
    void motor_Move(int8_t);
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

