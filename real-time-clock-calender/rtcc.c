/**********************************************************************
* 2009 Microchip Technology Inc.
*
* FileName:        	rtcc.c
* Dependencies:    Header (.h) files if applicable, see below
* Processor:       	PIC18F
* Compiler:        	MCC18 v3.30 or higher
*
* SOFTWARE LICENSE AGREEMENT:
* Microchip Technology Incorporated ("Microchip") retains all 
* ownership and intellectual property rights in the code accompanying
* this message and in all derivatives hereto.  You may use this code,
* and any derivatives created by any person or entity by or on your 
* behalf, exclusively with Microchip's proprietary products.  Your 
* acceptance and/or use of this code constitutes agreement to the 
* terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS". NO 
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT 
* NOT LIMITED TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, 
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS 
* CODE, ITS INTERACTION WITH MICROCHIP'S PRODUCTS, COMBINATION WITH 
* ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE 
* LIABLE, WHETHER IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR
* BREACH OF STATUTORY DUTY), STRICT LIABILITY, INDEMNITY, 
* CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
* EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR 
* EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER 
* CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE
* DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWABLE BY LAW, 
* MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS
* CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP 
* SPECIFICALLY TO HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and 
* determining its suitability.  Microchip has no obligation to modify,
* test, certify, or support the code.
*
* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author        	Date      	Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Harsha.J.M	04/04/09	First release of source file
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES:
* Code uses the Peripheral library support available with MCC18 Compiler
* Code Tested on:
* PIC18F46J50 controller
* The Processor starts with the External Crystal (8 Mhz).
* NOTE: Device Operates with 3.3V supply 
**********************************************************************/
#include <p18cxxx.h>
#include "rtcc.h"


//-------------------------------Configuration setting ----------------------------------------------
/**
	* Oscillator is configured as HS
	* Fail safe monitor is enabled
	* watch dog timer is disabled
	* Extended instruction mode is disabled
	* oscillator switch over is enabled	
	* CPU clock is not devided
	* RTCC clock is derived from T1OSC
*/
#if defined(__18F46J50)		//If the selected device if PIC18F46J50, then apply below settings else user will have to set
#pragma config OSC=HS, FCMEN=ON, WDTEN=OFF, IESO=ON, XINST=OFF, RTCOSC=INTOSCREF
#endif

//-------------------------Function Prototypes-----------------------------------------------------------------------------
void Blink_LED(unsigned int number_of_blink);
void RTCC_configure(void);

//-----------------Global structures used in deep sleep library-------------------------------------------------------
rtccTimeDate RtccTimeDate ,RtccAlrmTimeDate, Rtcc_read_TimeDate ;

//*******************main function******************************************************
void main(void)
{
	TRISB=0x01;									//configure the IO [TRIS and LAT register] as desired		
	LATB = 0x00;
	ANCON0 = 0xFF;
	
	mRtcc_Clear_Intr_Status_Bit;				//clears the RTCC interrupt status bit
	RTCC_configure();							//Configure RTCC using library APIs

	while(PIR3bits.RTCCIF==0)					//wait untill alarm is set
	RtccReadTimeDate(&Rtcc_read_TimeDate);		//Rtcc_read_TimeDate will have latest time
	Blink_LED(150);								//Indicate the alarm
	
	while(1);									//End of program
}


void Blink_LED(unsigned int number_of_blink)
{
	unsigned int m=0,n=0;
	for(n=0;n<number_of_blink;n++)
		{
		LATB = 0xFE;		
		for(m=0;m<60000;m++);
		LATB = 0x00;
		for(m=0;m<60000;m++);
		}
}

void RTCC_configure(void)
{
unsigned int i=0,j=0;


   RtccInitClock();       								//turn on clock source 
   RtccWrOn();            								//write enable the rtcc registers  
   mRtccSetClockOe(1);									//enable RTCC output on RTCC output pin
//   mRtccSetInt(1);										//Enable RTCC interrupt
	PIE3bits.RTCCIE=1; 
   //Set Date and time using global structures defined in libraries
   RtccTimeDate.f.hour = 1;								//Set Hour					
   RtccTimeDate.f.min =  0;								//Set minute
   RtccTimeDate.f.sec =  0;								//Set second
   RtccTimeDate.f.mday = 04;							//Set day
   RtccTimeDate.f.mon =  04;							//Se month
   RtccTimeDate.f.year = 09; 							//set year
   RtccTimeDate.f.wday = 6;  							//Set which day of the week for the corrsponding date 
   
   //Set the alarm time and date using gloabl structures defined in libraries
   RtccAlrmTimeDate.f.hour = RtccTimeDate.f.hour;		//Set Hour			
   RtccAlrmTimeDate.f.min =  RtccTimeDate.f.min ;		//Set minute
   RtccAlrmTimeDate.f.sec =  RtccTimeDate.f.sec + 4;	//alarm after ten seconds
   RtccAlrmTimeDate.f.mday = RtccTimeDate.f.mday;		//Set day
   RtccAlrmTimeDate.f.wday = RtccTimeDate.f.wday;		//Set which day of the week for the corrsponding date 
   RtccAlrmTimeDate.f.mon =  RtccTimeDate.f.mon;		//Se month
   RtccAlrmTimeDate.f.year = RtccTimeDate.f.year;		//set year 
   
   RtccWriteTimeDate(&RtccTimeDate,1);					//write into registers
   RtccSetAlarmRpt(RTCC_RPT_TEN_SEC,1);						//Set the alarm repeat to every minute
   RtccSetAlarmRptCount(5,1);							//set alarm repeat count
   RtccWriteAlrmTimeDate(&RtccAlrmTimeDate);			//write the time for alarm into alarm registers
   mRtccOn();											//enable the rtcc
   mRtccAlrmEnable();									//enable the rtcc alarm to wake the device up from deep sleep
}  


