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
        Device            :  PIC16F19176
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

/**
 Section: Included Files
*/
#include <xc.h>
#include <stdio.h>
#include "rtcc.h"
#include "mcc.h"

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
    // In order to be able to write the Write Enable(WREN) bit for RTCC you neet to enable EEPROM writing 
    // it is strongly recommended to disable interrupts during this code segment - see INTERRUPT_GlobalInterruptDisable() in interrupt manager.h if using interrupts
    // Set the RTCWREN bit
    __builtin_write_RTCWREN();
    RTCCONbits.RTCEN = 0;
    RTCCONbits.RTCCLKSEL = 0x01;
    
    if(!RTCCTimeInitialized())
    {
       // set RTCC time;
        YEAR     = 0x18;   // year
        MONTH    = 0x5;    // month 
        WEEKDAY  = 0x1;    // weekday 
        DAY      = 0x21;    // day
        HOURS    = 0x12;    // hours 
        MINUTES  = 0x00;    // minutes 
        SECONDS  = 0x0;    // seconds 
        rtccTimeInitialized = true;
    }
    
    // set Alarm time;
    ALRMCONbits.ALRMEN = 0;
    // ARPT 255; 
    ALRMRPT = 0xFF;
    
    ALRMMTH  = 0x5;  // month 
    ALRMWD   = 0x1; // weekday 
    ALRMDAY  = 0x21;  // day
    ALRMHR   = 0x12; // hours 
    ALRMMIN  = 0x01;  // minutes 
    ALRMSEC  = 0xA;  // seconds 

    // Re-enable the alarm
    ALRMCONbits.ALRMEN = 1;
    
    // AMASK Every 10 Second; CHIME enabled; ALRMEN enabled; 
    ALRMCON = 0xC8;

    
    // CAL 0; 
    RTCCAL = 0x00;
    
   // Enable RTCC, clear RTCWREN
   RTCCONbits.RTCEN = 1;
    while(!RTCCONbits.RTCEN);
   __builtin_clear_RTCWREN();

   // Clear the RTCC interrupt flag
   PIR8bits.RTCCIF = 0;

   //Enable RTCC interrupt
   PIE8bits.RTCCIE = 1;
}


/**
 This function implements RTCC_TimeGet. It access the 
 registers of  RTCC and writes to them the values provided 
 in a tm structure. 
*/
bool RTCC_TimeGet(struct tm *currentTime) 
{
    if(RTCCONbits.RTCSYNC) return false;

    // Set the RTCWREN bit
    __builtin_write_RTCWREN(); 

    //get year 
    currentTime->tm_year    = ConcatInt(20, GetDecimalValue(YEAR));
    //get month
    currentTime->tm_mon     = GetDecimalValue(MONTH);
    // get weekday
    currentTime->tm_wday    = GetDecimalValue(WEEKDAY);
    //get day
    currentTime->tm_mday    = GetDecimalValue(DAY);
    //get hour
    currentTime->tm_hour    = GetDecimalValue(HOURS);
    //get minutes
    currentTime->tm_min     = GetDecimalValue(MINUTES);
    //get seconds
    currentTime->tm_sec     = GetDecimalValue(SECONDS);    

    __builtin_clear_RTCWREN();

    return true;
}

void RTCC_TimeSet(struct tm *initialTime) 
{
    PIR8bits.RTCCIF = 0;
    PIE8bits.RTCCIE = 0;

    __builtin_write_RTCWREN();
    RTCCONbits.RTCEN = 0;

    //set year
    YEAR = GetHexValue(initialTime->tm_year);
    //set month
    MONTH = GetHexValue(initialTime->tm_mon);
    //set weekday
    WEEKDAY = GetHexValue(initialTime->tm_wday); 
    //set day
    DAY = GetHexValue(initialTime->tm_mday);     
    //set hours
    HOURS = GetHexValue(initialTime->tm_hour); 
    //set minutes
    MINUTES = GetHexValue(initialTime->tm_min); 
    //set seconds
    SECONDS = GetHexValue(initialTime->tm_sec);       

    RTCCONbits.RTCEN = 1;
    __builtin_clear_RTCWREN();

    PIR8bits.RTCCIF = 1;
    PIE8bits.RTCCIE = 1;
}

bool RTCC_AlarmTimeGet(struct tm *alarmTime) 
{
   if(RTCCONbits.RTCSYNC) return false;
    
    //Set the RTCWREN bit
    __builtin_write_RTCWREN(); 

    //get month
    alarmTime->tm_mon     = GetDecimalValue(ALRMMTH);  
    //get weekday
    alarmTime->tm_wday    = GetDecimalValue(ALRMWD);  
    //get day
    alarmTime->tm_mday    =  GetDecimalValue(ALRMDAY);;
    //get hour
    alarmTime->tm_hour    = GetDecimalValue(ALRMHR);  
    //get minutes
    alarmTime->tm_min     = GetDecimalValue(ALRMMIN); 
    //get seconds
    alarmTime->tm_sec     = GetDecimalValue(ALRMSEC);   

    __builtin_clear_RTCWREN();
  return true;
}

void RTCC_AlarmTimeSet(struct tm *alarmTime) 
{
    ALRMCONbits.ALRMEN = 0;

    //set month
    ALRMMTH = GetHexValue(alarmTime->tm_mon);
    //set weekday
    ALRMWD = GetHexValue(alarmTime->tm_wday); 
    //set day
    ALRMDAY = GetHexValue(alarmTime->tm_mday);     
    //set hours
    ALRMHR = GetHexValue(alarmTime->tm_hour); 
    //set minutes
    ALRMMIN = GetHexValue(alarmTime->tm_min); 
    //set seconds
    ALRMSEC = GetHexValue(alarmTime->tm_sec);       

    ALRMCONbits.ALRMEN = 1;
}

/**
 This function implements RTCC_TimeReset.This function is used to
 used by application to reset the RTCC value and reinitialize RTCC value.
*/
void RTCC_TimeReset()
{
    rtccTimeInitialized = false;
}

/**
  This function returns the value of the rtccTimeInitialized vaiable.
*/
static bool RTCCTimeInitialized(void)
{
    return(rtccTimeInitialized);
}

uint8_t ConvertHexToBCD(uint8_t hexvalue)
{
    uint8_t bcdvalue;
    bcdvalue = (uint8_t)((hexvalue / 10) << 4);
    bcdvalue = (uint8_t)(bcdvalue | (hexvalue % 10));
    return bcdvalue;
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

uint8_t GetDecimalValue(uint8_t hex_value) 
{
    uint8_t prefix_value = (uint8_t)(((hex_value & 0xf0) >> 4));
    uint8_t sufix_value  = (uint8_t)(hex_value & 0x0f);
    uint8_t int1 = ConvertHexToBCD(prefix_value);
    uint8_t int2 = ConvertHexToBCD(sufix_value);
    
    uint8_t result = (uint8_t)(ConcatInt(int1, int2 ));
    
    return result;
}

uint8_t GetHexValue(int value)
{
    uint8_t low     = ConvertBCDToHex(GetLastDigit(value));
    uint8_t high    = ConvertBCDToHex(GetLastDigit(value/10));
    
    return ((uint8_t)(((high & 0x0f) << 4) | low));
}

int ConcatInt(uint8_t uint1, uint8_t uint2)
{
    uint8_t temp         = 1;

    if(uint2 == 0) 
    {
        if(uint1 == 20) //if the result is about the year
        {
            temp = 100;
        } 
        else
        {
          temp = 10;
        }
    }

    while(temp <= uint2) {
        temp *= 10;
    }
    
    return uint1*temp + uint2;
}

uint8_t GetLastDigit(int int_value) 
{
    uint8_t result  =  (uint8_t)(int_value % 10);
    int_value      /= 10;
    
    return result;
}

void RTCC_ISR(void)
{
    /* TODO : Add interrupt handling code */
    printf("\r\n\r\n***** Alarm *****");
    D5_SetHigh();
    PWM4_LoadDutyValue(0xBF);
    __delay_ms(500);
    D5_SetLow();
    PWM4_LoadDutyValue(0x00);
    PIR8bits.RTCCIF = 0;
}

/**
 End of File
*/
