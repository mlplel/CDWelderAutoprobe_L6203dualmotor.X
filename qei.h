/* 
 * File:   qei.h
 * Author: mjacobs
 *
 * Created on December 4, 2018, 3:26 PM
 */

#ifndef QEI_H
#define	QEI_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <xc.h>

#ifdef	__cplusplus
extern "C" {
#endif
    
    void qei_Init(void);

    void qei_On(void);
    
    int16_t qei_ReadPos(void);  
    void qei_WritePos(int16_t);


#ifdef	__cplusplus
}
#endif

#endif	/* QEI_H */

