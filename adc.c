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

#include "mcc_generated_files/mcc.h"
#include <xc.h>
#include "adc.h"
#include <stdint.h>
#include <stdbool.h>

static ADC_CH ch0;
static ADC_CH ch1;

static int16_t p1zeropressure;
static int16_t p2zeropressure;

void ADC_Init(void){        
    // bits 8-9  FORM<1:0> 
    // TMR5 starts adc conversion
    // AD1CON1 = 0x038C;
    AD1CON1bits.FORM = 0x3;     // Signed fractional 
    AD1CON1bits.SSRC = 0x4;     // Timer5 compare ends sampling and starts conversion
    AD1CON1bits.SIMSAM = 1;     // Simultaneous Sample 
    AD1CON1bits.ASAM = 1;       // Sampling begins immediately after the last conversion      
    
    //AD1CON2 = 0x0104;
    AD1CON2bits.CHPS = 0x1;     // Converts CH0 and CH1
    AD1CON2bits.SMPI = 0x1;     // interrupt after every 2nd sample/conversion operation
    
    // AD1CON3 = 0x0010;
    AD1CON3bits.ADCS = 0x10;    // Tad = TP ? 17
    
    AD1CON4 = 0x0000;    
    //AD1CHS0 = 0x0101;
    AD1CHS0bits.CH0SB = 0x1;    // Channel 0 positive input is AN1
    AD1CHS0bits.CH0SA = 0x1;    // Channel 0 positive input is AN1
    
    AD1CHS123 = 0x0000;         // Channel 1 AN0
    
    AD1CSSH = 0x0000;           // no scan    
    AD1CSSL = 0x0000;           // no scan      
}

void ADC_On(void){
     // clear interrupt flag
    IFS0bits.AD1IF  = 0;
    // enable adc interrupt
    IEC0bits.AD1IE = 1;    
    AD1CON1bits.ADON = 1;
}
void ADC_Off(void){
    AD1CON1bits.ADON = 0;    
    // disable adc interrupt
    IEC0bits.AD1IE = 0;
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _AD1Interrupt(void){

    IFS0bits.AD1IF = 0;
    
    // use if adc data right aligned
    //ch0.value = ((int16_t)ADC1BUF0 + (int16_t)ADC1BUF2) / 2;
    // use if adc data left aligned
    ch0.value = (((int16_t)ADC1BUF0 / 2) + ((int16_t)ADC1BUF2 / 2));
    ch0.value = LPFilterCH0(ch0.value);
    ch0.value = ch0.value & 0xff80;     // 9 bits of information
    ch0.validf = true;
    
    // use if adc data right aligned
    //ch1.value = ((int16_t)ADC1BUF1 + (int16_t)ADC1BUF3) / 2;
    // use if adc data left aligned
    ch1.value = (((int16_t)ADC1BUF1 / 2) + ((int16_t)ADC1BUF3 / 2));
    ch1.value = LPFilterCH1(ch1.value);
    ch1.value = ch1.value & 0xff80;     // 9 bits of information
    ch1.validf = true;    
}


bool ADC_IsCH0Valid(void){
    return ch0.validf;
}

bool ADC_IsCH1Valid(void){    
    return ch1.validf;      
}

int16_t ADC_GetCH0(void){
    ch0.validf = false;
    return ch0.value;
}
int16_t ADC_GetCH1(void){    
    ch1.validf = false;
    return ch1.value;    
}

const unsigned int FILTERSIZE = 4;
/*
 * 
 */
int16_t LPFilterCH0(int16_t input){
    static int16_t data[8]= {0, 0, 0, 0, 0, 0, 0, 0};
    static int index = 0;
    static int32_t value = 0; 
    
    value = value - ((int32_t)data[index] - (int32_t)input);
    data[index] = input;
    index = ((index == (FILTERSIZE - 1)) ? 0: index+1);
    
    return (value / FILTERSIZE);
    
}

/*
 * 
 */
int16_t LPFilterCH1(int16_t input){
    static int16_t data[8]= {0, 0, 0, 0, 0, 0, 0, 0};
    static int index = 0;
    static int32_t value = 0; 
    
    value = value - ((int32_t)data[index] - (int32_t)input);
    data[index] = input;
    index = ((index == (FILTERSIZE - 1)) ? 0: index+1);
    
    return (value / FILTERSIZE);
    
}

/*
 * 
 */
int16_t adc_peekch0(){
    return ch0.value;
}
/*
 * 
 */
int16_t adc_peekch1(){
    return ch1.value;
}


void set_p1zeropressure(){
     //while(ADC_IsCH1Valid() == false);
     //p1zeropressure = ADC_GetCH1();
    p1zeropressure = ch1.value;
}
int16_t get_p1zeropressure(){
    return p1zeropressure;
}

void set_p2zeropressure(){
     //while(ADC_IsCH0Valid() == false);
    //p2zeropressure = ADC_GetCH0();
    p2zeropressure = ch0.value;
}
int16_t get_p2zeropressure(){
    return p2zeropressure;
}