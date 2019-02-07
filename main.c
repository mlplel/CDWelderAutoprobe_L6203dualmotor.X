/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system intialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.75.1
        Device            :  dsPIC33EP128MC504
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.35
        MPLAB 	          :  MPLAB X v5.05
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/mcc.h"
 
#include "dualmotor.h"
#include <libpic30.h>
#include "sh1106.h"
#include "qei.h"
#include "motor.h"

static int16_t pressure1offset = 175;  //175
int16_t readADC(void);
void delay100(int);
int filter(int);

/*
                         Main application
 */
int main(void)
{
    static uint8_t loopcnt = 0;
    // initialize the device
    SYSTEM_Initialize(); 
    i2c_Init();
    qei_Init();
    qei_On();   
    sh1106_Init();    
    PWM_ModuleEnable();  
    
    
    PWM_GENERATOR genNum = PWM_GENERATOR_1;
    PWM_DutyCycleSet(genNum, 0x0500);
    
    while (1)
    {             
        if(IFS0bits.T2IF)
        {
            loopcnt++;       
            IFS0bits.T2IF = false;
            loop100us();
            
            if(loopcnt == 10){
                loopcnt = 0;
                loop1ms();
            }            
        } 
        //processStrainValue(filter(readADC()));
        int16_t adctemp = readADC();
        testValues(filter(adctemp), adctemp);
                                 
     
        // Add your application code                     
    }
    return 1; 
}

int16_t readADC(){
    
    int16_t adcvalue = 0;
        
    ADC1_SamplingStart();
    __delay_us(1);
    ADC1_SamplingStop();
    while(!ADC1_IsConversionComplete()){
    }
    
    if(IFS0bits.AD1IF)
		// clear the ADC interrupt flag
		IFS0bits.AD1IF = false;   
    
    adcvalue = ADC1_Channel0ConversionResultGet() + pressure1offset; 
        
    //display_Value(adcvalue);
    return adcvalue;    
}

int filter(int input){
    static int data[8]= {0, 0, 0, 0, 0, 0, 0, 0};
    static int index = 0;
    static int value= 0; 
    
    value = value - (data[index] - input);
    data[index] = input;
    index = ((index == 7) ? 0: index+1);
    
    return (value / 8);
}

void delay100(int count){
    
    int i = 0;
    for(;i < count;i++){
        readADC();
        __delay_ms(100);
    }
}
 
 
/**
 End of File
*/

