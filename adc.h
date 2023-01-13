/* 
 * File:   adc.h
 * Author: 
 *
 * Created on February 7, 2019, 12:53 PM
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

    void set_p1zeropressure(void);
    int16_t get_p1zeropressure(void);
    void set_p2zeropressure(void);
    int16_t get_p2zeropressure();


/**
  @Summary
  
  @Description
   
  @Preconditions
    
  @Returns
    
  @Param
   
  @Example     
*/
int16_t adc_peekch1(void);


/**
  @Summary
  
  @Description
   
  @Preconditions
    
  @Returns
    
  @Param
   
  @Example     
*/
int16_t adc_peekch0(void);


/**
  @Summary
  
  @Description
   
  @Preconditions
    
  @Returns
    
  @Param
   
  @Example     
*/



#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

