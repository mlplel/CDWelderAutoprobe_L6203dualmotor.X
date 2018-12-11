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

    
    uint16_t motor_ReadLimits1(void);
    
    void motor_MoveUp(void);
    void motor_MoveDown(void);
    void motor_MoveUptoLimit(void);
    void motor_MoveDowntoLimit(void);
    void motor_Hold(void);



#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_H */

