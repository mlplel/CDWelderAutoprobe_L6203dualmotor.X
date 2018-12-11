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


 
 #define FCY     30170937UL

#include <libpic30.h>
#include "display.h"
#include "qei.h"
#include "motor.h"

int16_t readADC(void);
void delay100(int);


/*
                         Main application
 */
int main(void)
{
    
    // initialize the device
    SYSTEM_Initialize();
    
    qei_Init();
    qei_On();
   
    sh1106_Init();
   
    __delay_ms(150);
   
    sh1106_On();
   
    __delay_ms(150);
   
    uint8_t page = 0;
    for(;page < 8; page++){
       sh1106_ClearPage(page);
    }    
    
    
    PWM_ModuleEnable();    
    
    while (1)
    { 
        
        int16_t encvalue = 0;
        encvalue = qei_ReadPos(); 
        
        encvalue = encvalue >> 2;
                
        display_Value(0x0);
        
        motor_MoveDown();
        //__delay_ms(1);
        while(readADC() > -30);
        motor_Hold();       
        
        
        delay100(80);
        
        motor_MoveUptoLimit();
        
        delay100(30);
       
         
        
        /*
        
        if(updown == 0){
            motor_MoveUp();
            updown = 1;
        }
        
        if(updown == 1){
            motor_MoveDown();
            updown = 0;
        }
        */  
       
        // Add your application code    
        /*
        uint16_t sws = motor_ReadLimits1();
       
        if(sws == 1)
            display_Value(1);
        if(sws == 2)
            display_Value(-1);
        if(sws == 3)
            display_Value(33);
        if(sws == 0)
            display_Value(0);
        */                   
        
    }
    return 1; 
}

int16_t readADC(){
    
    int16_t adcvalue = 0;
        
        ADC1_SamplingStart();
        __delay_us(1);
        ADC1_SamplingStop();
        while(!ADC1_IsConversionComplete())
        {
            ADC1_Tasks();   
        }
        adcvalue = ADC1_Channel0ConversionResultGet();
        
        //adcvalue = adcvalue >> 1;
        
        display_Value(adcvalue);
        return adcvalue;    
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

