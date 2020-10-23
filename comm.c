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



     

/*
 * 
 */
void spi_init(void){
    
    RPOR0bits.RP20R = 0x0008;       // RA4->SPI2:SDO2
    RPINR22bits.SDI2R = 0x0019;     // RA9->SPI2:SDI2
    RPOR2bits.RP39R = 0x0009;       // RB7->SPI2:CLOCK
    RPINR22bits.SCK2R = 0x0027;     // RB7->SPI2:CLOCK
    
    // MSTEN Master;  PPRE 4:1; SPRE 8:1; MODE16 enabled; SMP Middle; DISSCK disabled; CKP Idle:Low, Active:High; CKE Active to Idle; SSEN disabled; 
    // SPI2CON1 = 0x522;
    SPI2CON1bits.MODE16 = 1;        // 16 bit mode
    SPI2CON1bits.CKE = 1;           // data change on clock active to Idle 
    SPI2CON1bits.MSTEN = 1;         // master mode
    SPI2CON1bits.SPRE = 0;          // 000 = Secondary prescale 8:1
    SPI2CON1bits.PPRE = 0x1;        // Primary prescale 4:1  
    
    
    
    // SPIFSD disabled; SPIBEN enabled; FRMPOL disabled; FRMDLY disabled; FRMEN disabled; 
    SPI2CON2 = 0x01;
    // SISEL SPI_INT_SPIRBF; SPIROV disabled; SPIEN enabled; SPISIDL disabled; 
    SPI2STAT = 0x8014; 
    
         
    IPC8bits.SPI2IP = 4;        // _SPI2Interrupt priority
    IPC8bits.SPI2EIP = 5;       // _SPI2ErrInterrupt priority
    
    
    IFS2bits.SPI2IF = 0;        
    IEC2bits.SPI2IE = 1;        // _SPI2Interrupt enabled
    
    IFS2bits.SPI2EIF = 0;
    IEC2bits.SPI2EIE = 1;       // _SPI2ErrInterrupt enabled
       
    
}

int16_t send_msg(MAINMSG msg){
    int16_t status = SPI2STATbits.SPIBEC;
    
    if(status != 0)
        return -1;  //error SPI2 interface is busy.
    
    SDCS_SetLow();
    SPI2BUF = msg.command;
    SPI2BUF = msg.data1;
    SPI2BUF = msg.data2;
    SPI2BUF = msg.data3;    
    
    return 0;  
}

/*
 * 
 */
bool is_txbusy(){
    
    if(SPI2STATbits.SPIBEC == 0){
        return false;
    } else
        return true;
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
    SDCS_SetHigh();
    newrxf = true;
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _SPI2ErrInterrupt(void){
    
    
    SPI2STATbits.SPIEN = 0;
    IFS2bits.SPI2EIF = 0;
    
    SPI2STAT = 0x8014;
    
}