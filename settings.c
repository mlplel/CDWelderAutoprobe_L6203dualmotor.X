
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

static PRESSET ps1[15] = {
    // pressure, kp, ki, kd, imax, outlimit
    {2400, 100, 20, 0, 1200, 800},
    {3900, 150, 20, 0, 1300, 900},
    {5600, 180, 100, 15, 2000, 1300},
    {7200, 180, 100, 15, 2000, 1300},
    {8900, 190, 100, 15, 2000, 1300},
    {10600, 200, 110, 15, 2000, 1300},
    {12100, 200, 110, 15, 2000, 1300},
    {13900, 210, 110, 15, 2000, 1300},
    {15400, 210, 120, 15, 2000, 1300},
    {17000, 210, 120, 15, 2000, 1300},
    {18500, 220, 120, 15, 2000, 1300},
    {20500, 260, 130, 15, 2000, 1300},
    {22500, 270, 130, 15, 2000, 1300},
    {24000, 290, 130, 15, 2000, 1300},
    {25900, 300, 130, 15, 2000, 1300}
};

static PRESSET ps2[15] = {
    {2400, 140, 20, 0, 1200, 800},
    {3900, 150, 20, 0, 1300, 900},
    {5600, 180, 100, 15, 2000, 1300},
    {7200, 180, 100, 15, 2000, 1300},
    {8900, 190, 100, 15, 2000, 1300},
    {10600, 200, 110, 15, 2000, 1300},
    {12100, 200, 110, 15, 2000, 1300},
    {13900, 210, 110, 15, 2000, 1300},
    {15400, 210, 120, 15, 2000, 1300},
    {17000, 210, 120, 15, 2000, 1300},
    {18500, 220, 120, 15, 2000, 1300},
    {20500, 260, 130, 15, 2000, 1300},
    {22500, 270, 130, 15, 2000, 1300},
    {24000, 290, 130, 15, 2000, 1300},
    {25900, 300, 130, 15, 2000, 1300}
};


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

PRESSET getP1(){
    return ps1[p1index];
}

PRESSET getP2(){
    return ps2[p2index];
}

PIDVALUE get_P1pid(){
    PIDVALUE pid;
    pid.kp = kp[p1index];
    pid.ki = ki[p1index];
    return pid;
}

PIDVALUE get_P2pid(){
    PIDVALUE pid;
    pid.kp = kp[p1index];
    pid.ki = ki[p1index];
    return pid;   
}

void setP1ZeroPressure(){
     while(ADC_IsCH1Valid() == false);
     p1zeropressure = ADC_GetCH1();
     int i;
     for(i = 0; i < 15; i++){
         ps1[i].pressure = ps1[i].pressure + p1zeropressure;
     }
}
int16_t get_p1zeropressure(){
    return p1zeropressure;
}

void setP2ZeroPressure(){
     while(ADC_IsCH0Valid() == false);
     p2zeropressure = ADC_GetCH0();
     int i;
      for(i = 0; i < 15; i++){
         ps2[i].pressure = ps2[i].pressure + p2zeropressure;
     }
}
int16_t get_p2zeropressure(){
    return p2zeropressure;
}
