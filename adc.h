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
        int16_t value;
        bool validf;
    } ADC_CH;


void ADC_Init(void);

void ADC_On(void);
void ADC_Off(void);

bool ADC_IsCH0Valid(void);
bool ADC_IsCH1Valid(void);
int16_t ADC_GetCH0(void);
int16_t ADC_GetCH1(void);

int16_t LPFilterCH0(int16_t input);
int16_t LPFilterCH1(int16_t input);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

