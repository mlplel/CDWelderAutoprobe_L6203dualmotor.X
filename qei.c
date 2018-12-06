


#include "qei.h"




void qei_Init(){
    
    RPINR14bits.QEB1R = 0x37;
    RPINR14bits.QEA1R = 0x36;
    
    QEI1IOCbits.QFDIV = 0x07;
    QEI1IOCbits.FLTREN = 1;
    
}




void qei_On(){    
    
     QEI1CONbits.QEIEN = 1;
}





int16_t qei_ReadPos(void){
    
    return  POS1CNTL;
    
};
