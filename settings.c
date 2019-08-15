
/* 
 * File:   settings.c
 * Author: mjacobs
 *
 * Created on April 16 2019, 2:08 PM
 */

#include "settings.h"
#include "adc.h"

static int p1index = 0;
static int p2index = 0;
static int16_t p1zeropressure;
static int16_t p2zeropressure;

static int pressure[15] = {2400, 3900, 5600, 7200, 8900, 10600, 12100, 13900,
15400, 17000, 18500, 20500, 22500, 24000, 25900};
static int kp[15] = {180, 180, 180, 180, 190, 200, 200, 210, 210, 210,
    220, 260, 270, 290, 300};
static int ki[15] = {90, 90, 100, 100, 100, 110, 110, 110, 120, 120,
    120, 130, 130, 130, 130};


void settings_init(void){
   
}

void set_p1pressureindex(uint16_t i){
    p1index = i - 1;    
}
void set_p2pressureindex(uint16_t i){
    p2index = i - 1;
}

int16_t getP1Pressure(){
    return pressure[p1index] + p1zeropressure;
}

int16_t getP2Pressure(){
    return pressure[p2index] + p2zeropressure;
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
int16_t get_p1zeropressure(){
    return p1zeropressure;
}

void setP2ZeroPressure(){
     while(ADC_IsCH0Valid() == false);
     p2zeropressure = ADC_GetCH0();
}
int16_t get_p2zeropressure(){
    return p2zeropressure;
}
