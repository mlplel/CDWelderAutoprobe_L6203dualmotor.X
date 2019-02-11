/* 
 * File:   adc.h
 * Author: mjacobs
 *
 * Created on February 7, 2019, 12:53 PM
 */

#ifndef ADC_H
#define	ADC_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct {
        bool validf;
        int16_t value;
    } ADC_CH;


void ADC_Init(void);

void ADC_On(void);
void ADC_Off(void);

bool ADC_IsCH1Valid(void);
int16_t ADC_GetCH1(void);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

