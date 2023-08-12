#include "msp430g2553.h"
#include "TimeDate.h"
#include "Buzzer.h"
#include "BuzzerTimer.h"
#include "ClockTimer.h"
#include "LCD_interface.h"
#include "TimeDate.h"

void init();

Time_Date TD;

int main(void)
{
	init();
	ClockTimer CT;
	Lcd_Interface LI(&TD);
	while (1)
	{
		LI.time_to_lcd();
		LI.change_time();
		for(unsigned long i = 200; i>0; i--);     // delay
	}
	
	return 0;
}

//Timer ISR to increment seconds
#pragma vector = TIMER0_A0_VECTOR	//
__interrupt void Timer_A0(void)		//for TI compiler
{
    TD.increment_second();
}

void init(){
	
	WDTCTL = WDTPW + WDTHOLD; //Stop watchdog timer

    //MCLK=SMCLK=1Mhz
    //DCOCTL, DCO Control Register
    DCOCTL = 0;            //clears DCOCTL to set the DCOCLK to the lowest setting.
    DCOCTL = CALDCO_1MHZ;  //Copy the calibration data

    //BCSCTL1, Basic Clock System Control Register 1
    BCSCTL1 = CALBC1_1MHZ; //Copy the calibration data

}
