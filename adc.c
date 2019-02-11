


#include "mcc_generated_files/mcc.h"
#include "adc.h"


static ADC_CH ch0;
static ADC_CH ch1;

void ADC_Init(void){        
    // bits 8-9  FORM<1:0> uint out
    AD1CON1 = 0x008C;
    
    AD1CON2 = 0x0104;
    
    AD1CON3 = 0x0010;
    
    AD1CON4 = 0x0000;
    
    AD1CHS0 = 0x0101;
    
    AD1CHS123 = 0x0000;
    
    AD1CSSH = 0x0000;
    
    AD1CSSL = 0x0000;       
    
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
   
   ch0.value = (ADC1BUF0 + ADC1BUF2)/2;
   ch0.validf = true;
   ch1.value = (ADC1BUF1 + ADC1BUF3)/2;
   ch1.validf = true;    
    
}


bool ADC_IsCH1Valid(void){
    
    return ch1.validf;    
    
}

int16_t ADC_GetCH1(void){
    
    ch1.validf = false;
    return ch1.value;
    
}