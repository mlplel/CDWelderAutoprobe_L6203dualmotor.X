/* 
 * File:   comm.c
 * Author: mjacobs
 *
 * Created on June 4, 2019, 11:15 AM
 */

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/system.h"

#include "comm.h" 

static int16_t rxdata[4];
static bool newrxf = 0;

static int16_t msglog[80];
static int16_t msglogp = 0;


int16_t send_msg(MAINMSG msg){
    int16_t status = SPI2STATbits.SPIBEC;
    
    if(status != 0)
        return -1;  //error SPI2 interface is busy.
    
    SPI2BUF = msg.command;
    SPI2BUF = msg.data1;
    SPI2BUF = msg.data2;
    SPI2BUF = msg.data3;    
    
    return 0;  
}

MAINMSG get_msg(){
     
    MAINMSG msg;
    newrxf = false;
    
    msg.command = rxdata[0];
    msg.data1 = rxdata[1];
    msg.data2 = rxdata[2];
    msg.data3 = rxdata[3];

    if (newrxf == true) {
        msg.validf = false;
        return msg;
    }
    msg.validf = true;
    return msg;   
}


bool is_newmsg(){
    return newrxf;
}


void __attribute__ ( ( interrupt, no_auto_psv ) ) _SPI2Interrupt(void){
    
    IFS2bits.SPI2IF = 0;
    
    //SD2_CS_SetHigh();
    int i = 0;
    for(;i<4;i++){
        rxdata[i] = SPI2BUF;
        msglog[msglogp] = rxdata[i];
        if (msglogp == 79) msglogp = 0;
        else msglogp++;
    }
    newrxf = true;
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _SPI2ErrInterrupt(void){
    
    
    SPI2STATbits.SPIEN = 0;
    IFS2bits.SPI2EIF = 0;
    
    SPI2STAT = 0x8014;
    
}