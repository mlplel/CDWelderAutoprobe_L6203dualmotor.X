/* 
 * File:   sh1106.h
 * Author: mjacobs
 *
 * Created on December 14, 2018, 5:27 PM
 */

#include "mcc_generated_files/mcc.h"
#include "sh1106.h"
#include "dualmotor.h"

typedef enum {
    I2C_IDLE,
    I2C_SENDADDR,
    I2C_SENDDATA,    
}I2C_STATES;

typedef struct
{
    uint8_t empty;
    uint8_t full;    
}DATA_QUEUE_STATUS;

#define MAX_I2C_DATABLOCKS      20

volatile static I2C_STATES i2cstate = I2C_IDLE;
static uint8_t sh1106_address = 0x78;   // 0x3c << 1 = 0x78
static I2C_DATABLOCK    i2cdatablocks[MAX_I2C_DATABLOCKS];
volatile static I2C_DATABLOCK    *startblock;
volatile static I2C_DATABLOCK    *endblock;
volatile static DATA_QUEUE_STATUS dataqueuestatus;
static uint8_t *pbuffer;

void i2c_Init(void){    
    
    startblock = i2cdatablocks;
    endblock = i2cdatablocks;
    dataqueuestatus.empty = 1;
    dataqueuestatus.full = 0;
    pbuffer = NULL;
      
    I2C1BRG = 0x47;     // baud rate set for 400KHz
    //I2C1BRG = 0x12A;       // baud rate set for 100Khz  
    I2C1CON = 0x8200;   // enable i2c 7bit addr
    I2C1STAT = 0x00; 

    // clear interrupt flag
    IFS1bits.MI2C1IF = 0;
    // enable i2c interrupt
    IEC1bits.MI2C1IE = 1;    
}

/*
 * Called on I2C1 Master interrupt flag set  
 */
void __attribute__ ( ( interrupt, no_auto_psv ) ) _MI2C1Interrupt ( void ){ 
    
    static uint8_t bytesleft;
    static uint8_t *databuf;     
   
    IFS1bits.MI2C1IF = 0;       // clear interrupt flag  
    //IO_RC3_Toggle();
    
    if(I2C1STATbits.IWCOL){        
        I2C1STATbits.IWCOL = 0;
        // write collision occured reset state to IDLE
        i2cstate = I2C_IDLE;        
    }
    
    switch(i2cstate){
        case I2C_IDLE:
            if(dataqueuestatus.empty == 0){
                // there is data to send
                bytesleft = startblock->length;
                databuf = startblock->pdata;
                pbuffer = startblock->pdata;
                startblock++;
                if(startblock == (i2cdatablocks + MAX_I2C_DATABLOCKS)){
                    startblock = i2cdatablocks;
                }
                dataqueuestatus.full = 0;
                if(startblock == endblock){
                    dataqueuestatus.empty = 1;
                }
                // send start bit
                I2C1CONbits.SEN = 1;
                i2cstate = I2C_SENDADDR;
            }            
            break;
        case I2C_SENDADDR:
            // send address with r/w bit cleared
            I2C1TRN = sh1106_address;
            i2cstate = I2C_SENDDATA;
            break;
        case I2C_SENDDATA:
            if(I2C1STATbits.ACKSTAT){
                // no ack from device
                // reset i2c here
                I2C1STATbits.ACKSTAT = 0;
                i2c_Stop();
            }
            else{
                if(bytesleft-- == 0){
                    i2c_Stop();
                }
                else{
                    I2C1TRN = *databuf++;
                }                
            }            
            break;
            
        default:
            // should not get here
            i2c_Stop();
            break;                 
    }    
}
void i2c_Stop(void){
    // set stop bit 
    I2C1CONbits.PEN = 1;
    i2cstate = I2C_IDLE;
    if(pbuffer != NULL){
        free(pbuffer);
        pbuffer = NULL;
    }
   // __delay_us(2);
}

I2C_STATUS_MSG i2c_Write(uint8_t *data, uint8_t length){
    
    if(dataqueuestatus.full)
        return I2C_STATUS_FULL;
    
    endblock->length = length;
    endblock->pdata = data;
    endblock++;
    if(endblock == (i2cdatablocks + MAX_I2C_DATABLOCKS)){
        endblock = i2cdatablocks;
    }
    dataqueuestatus.empty = 0;
    if(endblock == startblock){
        dataqueuestatus.full = 1;
    }
    if(i2cstate == I2C_IDLE){
        // force interrupt to start i2c transfer
        IFS1bits.MI2C1IF = 1;
    }
    return I2C_STATUS_OK;
}

I2C_STATUS_MSG i2c_Ready(void){
    if(dataqueuestatus.full)
        return I2C_STATUS_FULL;
    if(dataqueuestatus.empty && (i2cstate == I2C_IDLE))
        return I2C_STATUS_IDLE;
    else return I2C_STATUS_OK;
}

 void sh1106_Init(void){    
    
    while(i2c_Ready() != I2C_STATUS_IDLE);
    uint8_t *pdata;
    if((pdata = (uint8_t *)malloc(6)) == NULL){
        // fatal error need to reset
        while(1);
    }
    *pdata = 0x80;
    *(pdata + 1) = 0xA1;  //segment remap left
    *(pdata + 2) = 0x80;
    *(pdata + 3) = 0xC8;  //set scan direction
    *(pdata + 4) = 0x00;
    *(pdata + 5) = 0x50;  //set scan display line
    // init sh1106
    i2c_Write(pdata, 6);  

    sh1106_Clear();
    __delay_ms(100);
    
    if((pdata = (uint8_t *)malloc(2)) == NULL){
        // fatal error need to reset
        while(1);
    }
    *(pdata + 0) = 0x00;
    *(pdata + 1) = 0xAF; // turn display on
    i2c_Write(pdata, 2);    
    __delay_ms(150);   
 }
 
 void sh1106_Clear(void){
    uint8_t *pdata;
    uint8_t page = 0;
    
    while (page < 8) {
        if ((pdata = (uint8_t *) malloc(140)) == NULL) {
            // fatal error need to reset
            while (1);
        }
        *(pdata + 0) = 0x80;
        *(pdata + 1) = 0xB0 + page; // select page 0
        *(pdata + 2) = 0x80;
        *(pdata + 3) = 0x00;
        *(pdata + 4) = 0x80;
        *(pdata + 5) = 0x10; // column 0
        *(pdata + 6) = 0x40;
        int i = 7;
        //139 
        for (; i < 139;) {
            *(pdata + i) = 0x00;
            i++;
        }        
        while(i2c_Ready() != I2C_STATUS_IDLE);
        i2c_Write(pdata, i);
        page++;        
    }  
 }
  