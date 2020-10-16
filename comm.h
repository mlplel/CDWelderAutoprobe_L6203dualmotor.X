/* 
 * File:   comm.h
 * Author: mjacobs
 *
 * Created on June 4, 2019, 11:15 AM
 */

#ifndef COMM_H
#define	COMM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "stddef.h"
#include <stdbool.h>
#include "xc.h"
#include "messages.h"
    
 /**
  @Summary
  
  @Description
   
  @Preconditions
    
  @Returns
    
  @Param
   
  @Example     
*/  
 void spi_init(void);   

    int16_t send_msg(MAINMSG msg);    
    MAINMSG get_msg(void);
    bool is_newmsg(void);
    
 /**
  @Summary
  
  @Description
   
  @Preconditions
    
  @Returns
    
  @Param
   
  @Example     
*/
 bool is_txbusy(void);   
    
    
    
 /**
  @Summary
  
  @Description
   
  @Preconditions
    
  @Returns
    
  @Param
   
  @Example     
*/    

#ifdef	__cplusplus
}
#endif

#endif	/* COMM_H */

