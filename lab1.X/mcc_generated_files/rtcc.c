/**
  RTCC Generated Driver  File

  @Company
    Microchip Technology Inc.

  @File Name
    rtcc.c

  @Summary
    This is the generated driver implementation for the RTCC driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for RTCC.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC18F47J53
        Driver Version    :  2.02
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

/**
 Section: Included Files
*/

#include <xc.h>
#include "rtcc.h"

/**
* Section: Function Prototype
*/
static bool rtccTimeInitialized = false;
static bool RTCCTimeInitialized(void);

/**
* Section: Driver Interface Function Definitions
*/

void RTCC_Initialize(void)
{
    // Make sure to select the clock source for RTCC from config bits (default SOSC)


    // In order to be able to write the Write Enable(WREN) bit for RTCC you neet to enable EEPROM writing 
    // it is strongly recommended to disable interrupts during this code segment - see INTERRUPT_GlobalInterruptDisable() in interrupt manager.h if using interrupts
    EECON2 = 0x55;
    EECON2 = 0xAA;
    // Set the RTCWREN bit
    __builtin_write_RTCWREN();
    RTCCFGbits.RTCEN = 0;

    if(!RTCCTimeInitialized())
    {
        // set RTCC time 2018-09-16 22-18-27
        RTCCFG |= 0x3;       // Set RTCPTR0 and RTCPTR1 to start the sequence
        RTCVALL = 0x18;  // YEAR
        RTCVALH = 0x00;
        RTCVALL = 0x16;   // DAY
        RTCVALH = 0x9; // MONTH
        RTCVALL = 0x22;  // HOURS
        RTCVALH = 0x0;  // WEEKDAY
        RTCVALL = 0x27;   // SECONDS
        RTCVALH = 0x18;   // MINUTES
        rtccTimeInitialized = true;
    }

    PADCFG1 = 1; // Enable RTCC output
    // RTSECSEL0 Source Clock; 
    PADCFG1 = 0x04;

    // CAL 0; 
    RTCCAL = 0x00;

    // ARPT 0; 
    ALRMRPT = 0x00;

    // Enable RTCC, clear RTCWREN  
    RTCCFGbits.RTCEN = 1;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    __builtin_clear_RTCWREN();

}

/**
 This function implements RTCC_TimeReset.This function is used to
 used by application to reset the RTCC value and reinitialize RTCC value.
*/
void RTCC_TimeReset()
{
    rtccTimeInitialized = false;
}

static bool RTCCTimeInitialized(void)
{
    return(rtccTimeInitialized);
}

/**
 This function implements RTCC_TimeGet. It access the 
 registers of  RTCC and writes to them the values provided 
 in the function argument currentTime
*/

bool RTCC_TimeGet(struct tm *currentTime)
{
    uint8_t register_valueHigh;
    uint8_t register_valueLow;
    if(RTCCFGbits.RTCSYNC){
        return false;
    }

    EECON2 = 0x55;
    EECON2 = 0xAA;
   // Set the RTCWREN bit
   __builtin_write_RTCWREN();

    RTCCFG |= 0x3;       // Set RTCPTR0 and RTCPTR1 to start the sequence
    register_valueLow = RTCVALL;
    register_valueHigh = RTCVALH;    // reading/writing the high byte will decrement the pointer value by 1
    currentTime->tm_year = ConvertBCDToHex(register_valueLow);
  //  RCFGCALbits.RTCPTR = 2;
    register_valueLow = RTCVALL;
    register_valueHigh = RTCVALH;
    currentTime->tm_mon = ConvertBCDToHex(register_valueHigh);
    currentTime->tm_mday = ConvertBCDToHex(register_valueLow);
  //  RCFGCALbits.RTCPTR = 1;
    register_valueLow = RTCVALL;
    register_valueHigh = RTCVALH;;
    currentTime->tm_wday = ConvertBCDToHex(register_valueHigh);
    currentTime->tm_hour = ConvertBCDToHex(register_valueLow);
  //  RCFGCALbits.RTCPTR = 0;
    register_valueLow = RTCVALL;
    register_valueHigh = RTCVALH;
    currentTime->tm_min = ConvertBCDToHex(register_valueHigh);
    currentTime->tm_sec = ConvertBCDToHex(register_valueLow);

    // Clear RTCWREN Bit
    EECON2 = 0x55;
    EECON2 = 0xAA;
    __builtin_clear_RTCWREN();
    
    return true;
}

/**
 * This function sets the RTCC value and takes the input time in decimal format
*/

void RTCC_TimeSet(struct tm *initialTime)
{
    // Set the RTCWREN bit
    EECON2 = 0x55;
    EECON2 = 0xAA;
    __builtin_write_RTCWREN();

    RTCCFGbits.RTCEN = 0;
    

    // set RTCC initial time
    RTCCFG |= 0x3;       // Set RTCPTR0 and RTCPTR1 to start the sequence
    RTCVALL =  ConvertHexToBCD((uint8_t)(initialTime->tm_year));                        // YEAR
    RTCVALH = 0x00;
    RTCVALL = ConvertHexToBCD((uint8_t)(initialTime->tm_mday));                         // DAY-1
    RTCVALH = ConvertHexToBCD((uint8_t)(initialTime->tm_mon));                          // Month-1
    RTCVALL = ConvertHexToBCD((uint8_t)(initialTime->tm_hour));                         // HOURS
    RTCVALH = ConvertHexToBCD((uint8_t)(initialTime->tm_wday));                         // WEEKDAY
    RTCVALL = ConvertHexToBCD((uint8_t)(initialTime->tm_sec));                          // SECONDS
    RTCVALH = ConvertHexToBCD((uint8_t)(initialTime->tm_min));                          // MINUTES
             
    // Enable RTCC, clear RTCWREN  
    
    RTCCFGbits.RTCEN = 1;
        
    EECON2 = 0x55;
    EECON2 = 0xAA;
    __builtin_clear_RTCWREN();
    

}

/**
 This function reads the RTCC time and returns the date and time in BCD format
  */
bool RTCC_BCDTimeGet(bcdTime_t *currentTime)
{
    uint8_t register_valueHigh;
    uint8_t register_valueLow;
    if(RTCCFGbits.RTCSYNC){
        return false;
    }
    
    // Set the RTCWREN bit
    EECON2 = 0x55;
    EECON2 = 0xAA;
    __builtin_write_RTCWREN();

    RTCCFG |= 0x3;       // Set RTCPTR0 and RTCPTR1 to start the sequence
    register_valueLow = RTCVALL;
    register_valueHigh = RTCVALH;
    currentTime->tm_year = register_valueLow;
    //  RCFGCALbits.RTCPTR = 2;
    register_valueLow = RTCVALL;
    register_valueHigh = RTCVALH;
    currentTime->tm_mon = register_valueHigh;
    currentTime->tm_mday = register_valueLow;
    //  RCFGCALbits.RTCPTR = 1;
    register_valueLow = RTCVALL;
    register_valueHigh = RTCVALH;;
    currentTime->tm_wday = register_valueHigh;
    currentTime->tm_hour = register_valueLow;
    //  RCFGCALbits.RTCPTR = 0;
    register_valueLow = RTCVALL;
    register_valueHigh = RTCVALH;
    currentTime->tm_min = register_valueHigh;
    currentTime->tm_sec = register_valueLow;

    // Clear RTCWREN Bit
    EECON2 = 0x55;
    EECON2 = 0xAA;
    __builtin_clear_RTCWREN();

   return true;
}
/**
 This function takes the input date and time in BCD format and sets the RTCC
 */
void RTCC_BCDTimeSet(bcdTime_t *initialTime)
{
    // Set the RTCWREN bit
    EECON2 = 0x55;
    EECON2 = 0xAA;
    __builtin_write_RTCWREN();

    RTCCFGbits.RTCEN = 0; 

    PIR3bits.RTCCIF = 0;
    PIE3bits.RTCCIE = 0;

    // set RTCC initial time
	RTCCFG |= 0x3;       // Set RTCPTR0 and RTCPTR1 to start the sequence
    RTCVALL =  (uint8_t)(initialTime->tm_year);                        // YEAR
    RTCVALH = 0x00;
    RTCVALL = (uint8_t)(initialTime->tm_mday);                         // DAY-1
    RTCVALH = (uint8_t)(initialTime->tm_mon);                          // Month-1
    RTCVALL = (uint8_t)(initialTime->tm_hour);                         // HOURS
    RTCVALH = (uint8_t)(initialTime->tm_wday);                         // WEEKDAY
    RTCVALL = (uint8_t)(initialTime->tm_sec);                          // SECONDS
    RTCVALH = (uint8_t)(initialTime->tm_min);                          // MINUTES
    
    // Enable RTCC, clear RTCWREN
    RTCCFGbits.RTCEN = 1;  
    EECON2 = 0x55;
    EECON2 = 0xAA;
    __builtin_clear_RTCWREN();

    PIE3bits.RTCCIE = 1;

}

uint8_t ConvertHexToBCD(uint8_t hexvalue)
{
    uint8_t bcdvalue;
    bcdvalue = (uint8_t)((hexvalue / 10) << 4);
    bcdvalue = (uint8_t)(bcdvalue | (hexvalue % 10));
    return (bcdvalue);
}

uint8_t ConvertBCDToHex(uint8_t bcdvalue)
{
    uint8_t hexvalue;
    hexvalue = (uint8_t)((((bcdvalue & 0xF0) >> 4)* 10) + (bcdvalue & 0x0F));
    return hexvalue;
}


time_t ConvertDateTimeToUnixTime(struct tm *tmTime)
{
    return mktime(tmTime);
}

struct tm *ConvertUnixTimeToDateTime(time_t *unixTime)
{
    return gmtime(unixTime);
}

bool RTCC_Task(void)
{
    bool status;
    status = PIR3bits.RTCCIF;
    if( PIR3bits.RTCCIF)
    {
       PIR3bits.RTCCIF = 0;
    }
    return status;
}


/**
 End of File
*/
