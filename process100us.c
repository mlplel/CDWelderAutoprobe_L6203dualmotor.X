/* 
 * File:   process100us.c
 * Author: mjacobs
 *
 * Created on December 12, 2018, 8:56 AM
 */


#include "mcc_generated_files/mcc.h"
#include "dualmotor.h"




void loop100us(void){
    IO_RC3_Toggle();    
}