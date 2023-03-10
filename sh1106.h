/* 
 * File:   sh1106.h
 * Author: mjacobs
 *
 * Created on December 14, 2018, 5:27 PM
 */

#ifndef SH1106_H
#define	SH1106_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <xc.h>

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef enum 
    {
        I2C_STATUS_IDLE,
        I2C_STATUS_FULL,
        I2C_STATUS_OK,
        
    }I2C_STATUS_MSG;
    
    
    typedef struct
    {
        uint8_t     length;
        uint8_t     *pdata;        
    }I2C_DATABLOCK;

    void i2c_Init(void);
    void i2c_Stop(void);
    I2C_STATUS_MSG i2c_Write(uint8_t *data, uint8_t length);
    I2C_STATUS_MSG i2c_Ready(void);
    
    
    void sh1106_Init(void);
    void sh1106_Clear(void);
    
    void sh1106_Char(uint8_t col, uint8_t line, int chr);
    void display_Value(int16_t val);
    void display_Line3(int16_t val);
    


#ifdef	__cplusplus
}
#endif

#endif	/* SH1106_H */

