
/* 
 * File:   settings.c
 * Author: mjacobs
 *
 * Created on April 16 2019, 2:08 PM
 */

#include "settings.h"
#include "adc.h"

static int p1index = 0;

static int16_t p1zeropressure;

static int pressure[15] = {1500, 3000, 4900, 6500, 8500, 9800, 11900, 13300,
14900, 16900, 18100, 20300, 21700, 23500, 25000};
static int kp[15] = {150, 155, 165, 180, 190, 200, 210, 220, 230, 240,
    250, 260, 270, 280, 300};
static int ki[15] = {70, 70, 90, 90, 90, 105, 110, 115, 120, 125,
    130, 135, 140, 145, 165};


void settings_init(void){
   
}

void setP1PressureIndex(uint16_t i){
    p1index = i;    
}

int16_t getP1Pressure(){
    return pressure[p1index] + p1zeropressure;
}
PIDVALUE getP1Pid(){
    PIDVALUE pid;
    pid.kp = kp[p1index];
    pid.ki = ki[p1index];
    return pid;
}

void setP1ZeroPressure(){
     while(ADC_IsCH1Valid() == false);
     p1zeropressure = ADC_GetCH1();
}
