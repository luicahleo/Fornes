/**
  RTCC Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    rtcc.h

  @Summary
    This is the generated header file for the RTCC driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs driver for RTCC.
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

#ifndef RTCC_H
#define RTCC_H


/**
 Section: Included Files
*/


#define __builtin_write_RTCWREN() RTCCFGbits.RTCWREN = 1
#define __builtin_clear_RTCWREN() RTCCFGbits.RTCWREN = 0

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
 Section: types
*/
typedef struct tm bcdTime_t;

/**
 Section: Interface Routines
*/

/**
  @Summary
    Initializes and enables RTCC peripheral

  @Description
    This function sets a time in the RTCC and enables 
    RTCC for operation. It will also configure the Alarm settings.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Example
    <code>
    struct tm currentTime;

    RTCC_Initialize();

    while(!RTCC_TimeGet(&currentTime))
    {
        // Do something
    }
    </code>
*/
void RTCC_Initialize(void);

/**
  @Summary
    Returns the current time from the RTCC peripheral

  @Description
    This function returns the current time from the RTCC peripheral. This
    function uses the C library type struct tm parameter.

  @Preconditions
    None

  @Param
    currentTime - This the parameter which gets filled in by the function. The
    values are set by reading the hardware peripheral

  @Returns
    Whether the data is available or not, true if the data is available.
    false if the data is not available.

  @Example
    <code>
    struct tm currentTime;

    while(!RTCC_TimeGet(&currentTime))
    {
        // Do something
    }
    </code>
*/

bool RTCC_TimeGet(struct tm *currentTime);


/**
  @Summary
    Sets the initial time for the RTCC peripheral

  @Description
    This function sets the initial time for the RTCC peripheral. This
    function uses the C library type struct tm parameter.

  @Preconditions
    None

  @Param
    initialTime - This parameter sets the values.

  @Returns
    None

  @Example
    <code>
    struct tm initialTime;

    RTCC_TimeSet(&initialTime);
    </code>
*/

void RTCC_TimeSet(struct tm *initialTime);
/**
  @Summary
    Returns the current time from the RTCC peripheral

  @Description
    This function returns the current time from the RTCC peripheral. This
    function uses the C library type struct tm parameter.

  @Preconditions
    None

  @Param
    currentTime - This the parameter which gets filled in by the function. The
    values are set by reading the hardware peripheral

  @Returns
    Whether the data is available or not, true if the data is available.
    false if the data is not available.

  @Example
    <code>
    bcdTime_t currentTime;

    while(!RTCC_BCDTimeGet(&currentTime))
    {
        // Do something
    }
    </code>
*/

bool RTCC_BCDTimeGet(bcdTime_t *currentTime);

/**
  @Summary
    Sets the initial time for the RTCC peripheral in BCD format

  @Description
    This function sets the initial time for the RTCC peripheral. This
    the time value in BCD format

  @Preconditions
    None

  @Param
    initialTime - This parameter takes the input value in BCD format

  @Returns
    None

  @Example
    <code>
    bcdTime_t initialTime;

    RTCC_BCDTimeSet(&initialTime);
    </code>
*/
void RTCC_BCDTimeSet(bcdTime_t *initialTime);

/**
  @Summary
    This function indicates whether to reset the RTCC value or not on  system restart.

  @Description
    This function indicates whether to reset the RTCC value or not on  system restart.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Example
    <code>
    RTCC_TimeReset();
    </code>
*/
void RTCC_TimeReset(void);

/**
  @Summary
    This function converts a hex value to bcd format
  @Description
    This function converts a hex value to bcd format


  @Preconditions
    None

  @Param
    uint8_t hexvalue

  @Returns
    None

  @Example
    <code>
	bcdTime_t bcdvalue;
	struct tm hexvalue;
	
	bcdvalue = ConvertHexToBCD(hexvalue)
    </code>
*/
uint8_t ConvertHexToBCD(uint8_t hexvalue);

/**
  @Summary
    This function converts a bcd format value to a hex value
  @Description
    This function converts a bcd format value to a hex value


  @Preconditions
    None

  @Param
    uint8_t bcdvalue

  @Returns
    None

  @Example
    <code>
	bcdTime_t bcdvalue;
	struct tm hexvalue;
	
	hexvalue = ConvertHexToBCD(bcdvalue)
    </code>
*/
uint8_t ConvertBCDToHex(uint8_t bcdvalue);

/**
  @Summary
    This function converts struct tm time to unix time
  @Description
    This function receives a tm input and returns the corresponding unix time represented in seconds since 00:00:00 on Jan1. 1970


  @Preconditions
    None

  @Param
    struct tm * tmTime

  @Returns
    None

  @Example
    <code>
	time_t unixTime;
	struct tm tmTime;
	
	unixTime = ConvertDateTimeToUnixTime(&tmTime)
    </code>
*/
time_t ConvertDateTimeToUnixTime(struct tm *tmTime);

/**
  @Summary
    This function converts unix time to struct tm type
  @Description
    This function receives a unix time input (32 bits time in seconds) and returns the corresponding tm time


  @Preconditions
    None

  @Param
    time_t * unixTime

  @Returns
    None

  @Example
    <code>
	time_t unixTime;
	struct tm tmTime;
	
	*tmTime = ConvertUnixTimeToDateTime(&unixTime)
    </code>
*/
struct tm *ConvertUnixTimeToDateTime(time_t *unixTime);

/* Function:
    bool RTCC_Task(void)

  Summary:
    Status function which returns the RTCC interrupt flag status

  Description:
    This is the status function for the RTCC peripheral. 
*/
bool RTCC_Task(void);

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif // RTCC_H

/**
 End of File
*/
