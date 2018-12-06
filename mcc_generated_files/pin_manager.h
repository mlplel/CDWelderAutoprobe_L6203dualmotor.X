/**
  PIN MANAGER Generated Driver File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for PIN MANAGER.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.85
        Device            :  dsPIC33EP128MC504
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.35
        MPLAB 	          :  MPLAB X v5.05
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#ifndef _PIN_MANAGER_H
#define _PIN_MANAGER_H
/**
    Section: Includes
*/
#include <xc.h>

/**
    Section: Device Pin Macros
*/
/**
  @Summary
    Sets the GPIO pin, RA4, high using LATA4.

  @Description
    Sets the GPIO pin, RA4, high using LATA4.

  @Preconditions
    The RA4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA4 high (1)
    IO_RA4_SetHigh();
    </code>

*/
#define IO_RA4_SetHigh()          _LATA4 = 1
/**
  @Summary
    Sets the GPIO pin, RA4, low using LATA4.

  @Description
    Sets the GPIO pin, RA4, low using LATA4.

  @Preconditions
    The RA4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA4 low (0)
    IO_RA4_SetLow();
    </code>

*/
#define IO_RA4_SetLow()           _LATA4 = 0
/**
  @Summary
    Toggles the GPIO pin, RA4, using LATA4.

  @Description
    Toggles the GPIO pin, RA4, using LATA4.

  @Preconditions
    The RA4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RA4
    IO_RA4_Toggle();
    </code>

*/
#define IO_RA4_Toggle()           _LATA4 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RA4.

  @Description
    Reads the value of the GPIO pin, RA4.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RA4
    postValue = IO_RA4_GetValue();
    </code>

*/
#define IO_RA4_GetValue()         _RA4
/**
  @Summary
    Configures the GPIO pin, RA4, as an input.

  @Description
    Configures the GPIO pin, RA4, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA4 as an input
    IO_RA4_SetDigitalInput();
    </code>

*/
#define IO_RA4_SetDigitalInput()  _TRISA4 = 1
/**
  @Summary
    Configures the GPIO pin, RA4, as an output.

  @Description
    Configures the GPIO pin, RA4, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA4 as an output
    IO_RA4_SetDigitalOutput();
    </code>

*/
#define IO_RA4_SetDigitalOutput() _TRISA4 = 0
/**
  @Summary
    Sets the GPIO pin, RB10, high using LATB10.

  @Description
    Sets the GPIO pin, RB10, high using LATB10.

  @Preconditions
    The RB10 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB10 high (1)
    IO_RB10_SetHigh();
    </code>

*/
#define IO_RB10_SetHigh()          _LATB10 = 1
/**
  @Summary
    Sets the GPIO pin, RB10, low using LATB10.

  @Description
    Sets the GPIO pin, RB10, low using LATB10.

  @Preconditions
    The RB10 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB10 low (0)
    IO_RB10_SetLow();
    </code>

*/
#define IO_RB10_SetLow()           _LATB10 = 0
/**
  @Summary
    Toggles the GPIO pin, RB10, using LATB10.

  @Description
    Toggles the GPIO pin, RB10, using LATB10.

  @Preconditions
    The RB10 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB10
    IO_RB10_Toggle();
    </code>

*/
#define IO_RB10_Toggle()           _LATB10 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB10.

  @Description
    Reads the value of the GPIO pin, RB10.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB10
    postValue = IO_RB10_GetValue();
    </code>

*/
#define IO_RB10_GetValue()         _RB10
/**
  @Summary
    Configures the GPIO pin, RB10, as an input.

  @Description
    Configures the GPIO pin, RB10, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB10 as an input
    IO_RB10_SetDigitalInput();
    </code>

*/
#define IO_RB10_SetDigitalInput()  _TRISB10 = 1
/**
  @Summary
    Configures the GPIO pin, RB10, as an output.

  @Description
    Configures the GPIO pin, RB10, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB10 as an output
    IO_RB10_SetDigitalOutput();
    </code>

*/
#define IO_RB10_SetDigitalOutput() _TRISB10 = 0
/**
  @Summary
    Sets the GPIO pin, RB11, high using LATB11.

  @Description
    Sets the GPIO pin, RB11, high using LATB11.

  @Preconditions
    The RB11 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB11 high (1)
    IO_RB11_SetHigh();
    </code>

*/
#define IO_RB11_SetHigh()          _LATB11 = 1
/**
  @Summary
    Sets the GPIO pin, RB11, low using LATB11.

  @Description
    Sets the GPIO pin, RB11, low using LATB11.

  @Preconditions
    The RB11 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB11 low (0)
    IO_RB11_SetLow();
    </code>

*/
#define IO_RB11_SetLow()           _LATB11 = 0
/**
  @Summary
    Toggles the GPIO pin, RB11, using LATB11.

  @Description
    Toggles the GPIO pin, RB11, using LATB11.

  @Preconditions
    The RB11 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB11
    IO_RB11_Toggle();
    </code>

*/
#define IO_RB11_Toggle()           _LATB11 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB11.

  @Description
    Reads the value of the GPIO pin, RB11.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB11
    postValue = IO_RB11_GetValue();
    </code>

*/
#define IO_RB11_GetValue()         _RB11
/**
  @Summary
    Configures the GPIO pin, RB11, as an input.

  @Description
    Configures the GPIO pin, RB11, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB11 as an input
    IO_RB11_SetDigitalInput();
    </code>

*/
#define IO_RB11_SetDigitalInput()  _TRISB11 = 1
/**
  @Summary
    Configures the GPIO pin, RB11, as an output.

  @Description
    Configures the GPIO pin, RB11, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB11 as an output
    IO_RB11_SetDigitalOutput();
    </code>

*/
#define IO_RB11_SetDigitalOutput() _TRISB11 = 0
/**
  @Summary
    Sets the GPIO pin, RB12, high using LATB12.

  @Description
    Sets the GPIO pin, RB12, high using LATB12.

  @Preconditions
    The RB12 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB12 high (1)
    IO_RB12_SetHigh();
    </code>

*/
#define IO_RB12_SetHigh()          _LATB12 = 1
/**
  @Summary
    Sets the GPIO pin, RB12, low using LATB12.

  @Description
    Sets the GPIO pin, RB12, low using LATB12.

  @Preconditions
    The RB12 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB12 low (0)
    IO_RB12_SetLow();
    </code>

*/
#define IO_RB12_SetLow()           _LATB12 = 0
/**
  @Summary
    Toggles the GPIO pin, RB12, using LATB12.

  @Description
    Toggles the GPIO pin, RB12, using LATB12.

  @Preconditions
    The RB12 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB12
    IO_RB12_Toggle();
    </code>

*/
#define IO_RB12_Toggle()           _LATB12 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB12.

  @Description
    Reads the value of the GPIO pin, RB12.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB12
    postValue = IO_RB12_GetValue();
    </code>

*/
#define IO_RB12_GetValue()         _RB12
/**
  @Summary
    Configures the GPIO pin, RB12, as an input.

  @Description
    Configures the GPIO pin, RB12, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB12 as an input
    IO_RB12_SetDigitalInput();
    </code>

*/
#define IO_RB12_SetDigitalInput()  _TRISB12 = 1
/**
  @Summary
    Configures the GPIO pin, RB12, as an output.

  @Description
    Configures the GPIO pin, RB12, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB12 as an output
    IO_RB12_SetDigitalOutput();
    </code>

*/
#define IO_RB12_SetDigitalOutput() _TRISB12 = 0
/**
  @Summary
    Sets the GPIO pin, RB13, high using LATB13.

  @Description
    Sets the GPIO pin, RB13, high using LATB13.

  @Preconditions
    The RB13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB13 high (1)
    IO_RB13_SetHigh();
    </code>

*/
#define IO_RB13_SetHigh()          _LATB13 = 1
/**
  @Summary
    Sets the GPIO pin, RB13, low using LATB13.

  @Description
    Sets the GPIO pin, RB13, low using LATB13.

  @Preconditions
    The RB13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB13 low (0)
    IO_RB13_SetLow();
    </code>

*/
#define IO_RB13_SetLow()           _LATB13 = 0
/**
  @Summary
    Toggles the GPIO pin, RB13, using LATB13.

  @Description
    Toggles the GPIO pin, RB13, using LATB13.

  @Preconditions
    The RB13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB13
    IO_RB13_Toggle();
    </code>

*/
#define IO_RB13_Toggle()           _LATB13 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB13.

  @Description
    Reads the value of the GPIO pin, RB13.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB13
    postValue = IO_RB13_GetValue();
    </code>

*/
#define IO_RB13_GetValue()         _RB13
/**
  @Summary
    Configures the GPIO pin, RB13, as an input.

  @Description
    Configures the GPIO pin, RB13, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB13 as an input
    IO_RB13_SetDigitalInput();
    </code>

*/
#define IO_RB13_SetDigitalInput()  _TRISB13 = 1
/**
  @Summary
    Configures the GPIO pin, RB13, as an output.

  @Description
    Configures the GPIO pin, RB13, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB13 as an output
    IO_RB13_SetDigitalOutput();
    </code>

*/
#define IO_RB13_SetDigitalOutput() _TRISB13 = 0
/**
  @Summary
    Sets the GPIO pin, RB14, high using LATB14.

  @Description
    Sets the GPIO pin, RB14, high using LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB14 high (1)
    IO_RB14_SetHigh();
    </code>

*/
#define IO_RB14_SetHigh()          _LATB14 = 1
/**
  @Summary
    Sets the GPIO pin, RB14, low using LATB14.

  @Description
    Sets the GPIO pin, RB14, low using LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB14 low (0)
    IO_RB14_SetLow();
    </code>

*/
#define IO_RB14_SetLow()           _LATB14 = 0
/**
  @Summary
    Toggles the GPIO pin, RB14, using LATB14.

  @Description
    Toggles the GPIO pin, RB14, using LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB14
    IO_RB14_Toggle();
    </code>

*/
#define IO_RB14_Toggle()           _LATB14 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB14.

  @Description
    Reads the value of the GPIO pin, RB14.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB14
    postValue = IO_RB14_GetValue();
    </code>

*/
#define IO_RB14_GetValue()         _RB14
/**
  @Summary
    Configures the GPIO pin, RB14, as an input.

  @Description
    Configures the GPIO pin, RB14, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB14 as an input
    IO_RB14_SetDigitalInput();
    </code>

*/
#define IO_RB14_SetDigitalInput()  _TRISB14 = 1
/**
  @Summary
    Configures the GPIO pin, RB14, as an output.

  @Description
    Configures the GPIO pin, RB14, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB14 as an output
    IO_RB14_SetDigitalOutput();
    </code>

*/
#define IO_RB14_SetDigitalOutput() _TRISB14 = 0
/**
  @Summary
    Sets the GPIO pin, RB15, high using LATB15.

  @Description
    Sets the GPIO pin, RB15, high using LATB15.

  @Preconditions
    The RB15 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB15 high (1)
    IO_RB15_SetHigh();
    </code>

*/
#define IO_RB15_SetHigh()          _LATB15 = 1
/**
  @Summary
    Sets the GPIO pin, RB15, low using LATB15.

  @Description
    Sets the GPIO pin, RB15, low using LATB15.

  @Preconditions
    The RB15 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB15 low (0)
    IO_RB15_SetLow();
    </code>

*/
#define IO_RB15_SetLow()           _LATB15 = 0
/**
  @Summary
    Toggles the GPIO pin, RB15, using LATB15.

  @Description
    Toggles the GPIO pin, RB15, using LATB15.

  @Preconditions
    The RB15 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB15
    IO_RB15_Toggle();
    </code>

*/
#define IO_RB15_Toggle()           _LATB15 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB15.

  @Description
    Reads the value of the GPIO pin, RB15.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB15
    postValue = IO_RB15_GetValue();
    </code>

*/
#define IO_RB15_GetValue()         _RB15
/**
  @Summary
    Configures the GPIO pin, RB15, as an input.

  @Description
    Configures the GPIO pin, RB15, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB15 as an input
    IO_RB15_SetDigitalInput();
    </code>

*/
#define IO_RB15_SetDigitalInput()  _TRISB15 = 1
/**
  @Summary
    Configures the GPIO pin, RB15, as an output.

  @Description
    Configures the GPIO pin, RB15, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB15 as an output
    IO_RB15_SetDigitalOutput();
    </code>

*/
#define IO_RB15_SetDigitalOutput() _TRISB15 = 0
/**
  @Summary
    Sets the GPIO pin, RB8, high using LATB8.

  @Description
    Sets the GPIO pin, RB8, high using LATB8.

  @Preconditions
    The RB8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB8 high (1)
    IO_RB8_SetHigh();
    </code>

*/
#define IO_RB8_SetHigh()          _LATB8 = 1
/**
  @Summary
    Sets the GPIO pin, RB8, low using LATB8.

  @Description
    Sets the GPIO pin, RB8, low using LATB8.

  @Preconditions
    The RB8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB8 low (0)
    IO_RB8_SetLow();
    </code>

*/
#define IO_RB8_SetLow()           _LATB8 = 0
/**
  @Summary
    Toggles the GPIO pin, RB8, using LATB8.

  @Description
    Toggles the GPIO pin, RB8, using LATB8.

  @Preconditions
    The RB8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB8
    IO_RB8_Toggle();
    </code>

*/
#define IO_RB8_Toggle()           _LATB8 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB8.

  @Description
    Reads the value of the GPIO pin, RB8.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB8
    postValue = IO_RB8_GetValue();
    </code>

*/
#define IO_RB8_GetValue()         _RB8
/**
  @Summary
    Configures the GPIO pin, RB8, as an input.

  @Description
    Configures the GPIO pin, RB8, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB8 as an input
    IO_RB8_SetDigitalInput();
    </code>

*/
#define IO_RB8_SetDigitalInput()  _TRISB8 = 1
/**
  @Summary
    Configures the GPIO pin, RB8, as an output.

  @Description
    Configures the GPIO pin, RB8, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB8 as an output
    IO_RB8_SetDigitalOutput();
    </code>

*/
#define IO_RB8_SetDigitalOutput() _TRISB8 = 0
/**
  @Summary
    Sets the GPIO pin, RC9, high using LATC9.

  @Description
    Sets the GPIO pin, RC9, high using LATC9.

  @Preconditions
    The RC9 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC9 high (1)
    IO_RC9_SetHigh();
    </code>

*/
#define IO_RC9_SetHigh()          _LATC9 = 1
/**
  @Summary
    Sets the GPIO pin, RC9, low using LATC9.

  @Description
    Sets the GPIO pin, RC9, low using LATC9.

  @Preconditions
    The RC9 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC9 low (0)
    IO_RC9_SetLow();
    </code>

*/
#define IO_RC9_SetLow()           _LATC9 = 0
/**
  @Summary
    Toggles the GPIO pin, RC9, using LATC9.

  @Description
    Toggles the GPIO pin, RC9, using LATC9.

  @Preconditions
    The RC9 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RC9
    IO_RC9_Toggle();
    </code>

*/
#define IO_RC9_Toggle()           _LATC9 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RC9.

  @Description
    Reads the value of the GPIO pin, RC9.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RC9
    postValue = IO_RC9_GetValue();
    </code>

*/
#define IO_RC9_GetValue()         _RC9
/**
  @Summary
    Configures the GPIO pin, RC9, as an input.

  @Description
    Configures the GPIO pin, RC9, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC9 as an input
    IO_RC9_SetDigitalInput();
    </code>

*/
#define IO_RC9_SetDigitalInput()  _TRISC9 = 1
/**
  @Summary
    Configures the GPIO pin, RC9, as an output.

  @Description
    Configures the GPIO pin, RC9, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC9 as an output
    IO_RC9_SetDigitalOutput();
    </code>

*/
#define IO_RC9_SetDigitalOutput() _TRISC9 = 0

/**
    Section: Function Prototypes
*/
/**
  @Summary
    Configures the pin settings of the dsPIC33EP128MC504
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void SYSTEM_Initialize(void)
    {
        // Other initializers are called from this function
        PIN_MANAGER_Initialize();
    }
    </code>

*/
void PIN_MANAGER_Initialize (void);

#endif
