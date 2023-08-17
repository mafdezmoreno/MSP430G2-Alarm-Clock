#include "buzzer.h"
#include "buzzerTimer.h"
#include "clockTimer.h"
#include "lcdInterface.h"
#include <msp430g2553.h>
#include "timeDate.h"

void initMcu();

bool signalIncrementSec = false;
buzzer buz;

int main(void)
{
    initMcu();
    timeDate td;
    clockTimer ct;
    lcdInterface li(&td);
    buz.activeBuz(); // Todo: move in activation conditions.
    while (1)
    {
        if (signalIncrementSec)
        {
            td.incrementSecond();
            li.timeToLcd();
            li.changeTime();
            signalIncrementSec = false;
        }
        for (unsigned long i = 200; i > 0; i--);     // delay
    }
}

//Timer ISR to increment seconds
#pragma vector = TIMER0_A0_VECTOR    //
__interrupt void Timer_A0(void)        //for TI compiler
{
    static unsigned long counter = 0;
    if (counter == 256)
    {
        signalIncrementSec = true;
        counter = 0;
    }
    counter++;

    static unsigned int start = 0;
    static unsigned int stop = 40;

    if (buz.getBuzActive())
    {
        if (start < 2 * stop)
        {
            buz.makeSound();
            start++;
        }
        else if (start < 3 * stop)
        {
            start++;
        }
        else if (start < 5 * stop)
        {
            buz.makeSound();
            start++;
        }
        else if (start < 10 * stop)
        {
            start++;
        }
        else
            start = 0;
    }
}

void initMcu()
{

    WDTCTL = WDTPW + WDTHOLD; //Stop watchdog timer

    //MCLK=SMCLK=1Mhz
    //DCOCTL, DCO Control Register
    DCOCTL = 0;            //clears DCOCTL to set the DCOCLK to the lowest setting.
    DCOCTL = CALDCO_1MHZ;  //Copy the calibration data

    //BCSCTL1, Basic Clock System Control Register 1
    BCSCTL1 = CALBC1_1MHZ; //Copy the calibration data

}
