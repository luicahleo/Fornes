/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC18F47J53
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB 	          :  MPLAB X 4.15	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set led aliases
#define led_TRIS                 TRISAbits.TRISA0
#define led_LAT                  LATAbits.LATA0
#define led_PORT                 PORTAbits.RA0
#define led_ANS                  ANCON0bits.PCFG0
#define led_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define led_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define led_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define led_GetValue()           PORTAbits.RA0
#define led_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define led_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define led_SetAnalogMode()      do { ANCON0bits.PCFG0 = 1; } while(0)
#define led_SetDigitalMode()     do { ANCON0bits.PCFG0 = 0; } while(0)

// get/set RB1 procedures
#define RB1_SetHigh()               do { LATBbits.LATB1 = 1; } while(0)
#define RB1_SetLow()                do { LATBbits.LATB1 = 0; } while(0)
#define RB1_Toggle()                do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define RB1_GetValue()              PORTBbits.RB1
#define RB1_SetDigitalInput()       do { TRISBbits.TRISB1 = 1; } while(0)
#define RB1_SetDigitalOutput()      do { TRISBbits.TRISB1 = 0; } while(0)
#define RB1_SetPullup()             do { WPUBbits.WPUB1 = 1; } while(0)
#define RB1_ResetPullup()           do { WPUBbits.WPUB1 = 0; } while(0)
#define RB1_SetAnalogMode()         do { ANCON1bits.PCFG10 = 1; } while(0)
#define RB1_SetDigitalMode()        do { ANCON1bits.PCFG10 = 0; } while(0)

// get/set RD6 procedures
#define RD6_SetHigh()               do { LATDbits.LATD6 = 1; } while(0)
#define RD6_SetLow()                do { LATDbits.LATD6 = 0; } while(0)
#define RD6_Toggle()                do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define RD6_GetValue()              PORTDbits.RD6
#define RD6_SetDigitalInput()       do { TRISDbits.TRISD6 = 1; } while(0)
#define RD6_SetDigitalOutput()      do { TRISDbits.TRISD6 = 0; } while(0)
#define RD6_SetPullup()             do { WPUDbits.WPUD6 = 1; } while(0)
#define RD6_ResetPullup()           do { WPUDbits.WPUD6 = 0; } while(0)

// get/set RD7 procedures
#define RD7_SetHigh()               do { LATDbits.LATD7 = 1; } while(0)
#define RD7_SetLow()                do { LATDbits.LATD7 = 0; } while(0)
#define RD7_Toggle()                do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define RD7_GetValue()              PORTDbits.RD7
#define RD7_SetDigitalInput()       do { TRISDbits.TRISD7 = 1; } while(0)
#define RD7_SetDigitalOutput()      do { TRISDbits.TRISD7 = 0; } while(0)
#define RD7_SetPullup()             do { WPUDbits.WPUD7 = 1; } while(0)
#define RD7_ResetPullup()           do { WPUDbits.WPUD7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/