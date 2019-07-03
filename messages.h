/* 
 * File:   messages.h
 * Author: mjacobs
 *
 * Created on June 5, 2019, 2:13 PM
 */

#ifndef MESSAGES_H
#define	MESSAGES_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stddef.h>
#include <xc.h>
#include <stdbool.h>

    typedef enum {
        RPO_init = 0x3B01,
        RPO_status,
        RPO_none,
        RPO_command,
        CMD_poweron = 0xA301,
        CMD_init,
        CMD_cmdok,
        CMD_status,
        CMD_sync,
        CMD_testmode1 = 0xB101,
    } CMD;

    typedef struct {
        uint16_t SETPRESSURE1 : 1;
        uint16_t SETPRESSURE2 : 1;
        uint16_t : 13;
        uint16_t SETTESTMODE : 1;
    } STATUS1BITS;

    typedef struct {
        int16_t command;
        int16_t data1;
        int16_t data2;
        int16_t data3;
        bool validf;
    } MAINMSG;

    typedef enum {
        TESTPROBE1 = 0x0140,
        TESTPROBE2,
    } CTLCMD;

    extern const MAINMSG MSG_status;
    extern const MAINMSG MSG_poweron;
    extern const MAINMSG MSG_init;
    extern const MAINMSG MSG_cmdok;
    extern const MAINMSG MSG_testmode1;
    extern const MAINMSG MSG_sync;

    extern const MAINMSG RPY_init;
    extern const MAINMSG RPY_status;
    extern const MAINMSG RPY_command;
    extern const MAINMSG RPY_none;    


#ifdef	__cplusplus
}
#endif

#endif	/* MESSAGES_H */

