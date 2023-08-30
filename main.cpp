#include "buzzer.h"
#include "buzzerTimer.h"
#include "clockTimer.h"
#include "lcdInterface.h"
#include "msp430g2553.h"
#include "timeDate.h"
#include "alarm.h"


void initMcu();

bool signalIncrementSec = false;
buzzer buz;

int main(void)
{
    static bool signalIncrementMin = false;
    static bool alarmOn = false;
    static unsigned signalButton = 0;

    initMcu();
    timeDate td(&signalIncrementMin);
    clockTimer ct;
    buttons but(&alarmOn);
    alarm al1(td.getCurrentTime(), td.getCurrentWeekDay());
    lcdInterface li(&td, &al1, &but);
    while (1)
    {
        if (signalIncrementSec)
        {
            td.incrementSecond();
            li.printAll();
            signalIncrementSec = false;
        }
        if (signalIncrementMin)
        {
            alarmOn = al1.alarmTimeNow();
            static unsigned minCounter = 0;
            if(alarmOn)
            {
                minCounter = 0;
                buz.activeBuz();
            }
            else if (minCounter >= 5)
            {
                buz.deactivateBuz();
                minCounter = 0;
                signalIncrementMin = false;
            }
            minCounter++;
        }
        signalButton = but.getSignalButton();
        switch (signalButton)
        {
            case 1:
                break;
            case 2:
                break;
            case 4:
                li.changeTime();
                break;
            case 8:
                li.changeAlarm();
                break;
            case 16:
                break;
        }
        switch (signalButton)
        {
            case 1:
            case 2:
            case 4:
            case 8:
            case 16:
                buz.deactivateBuz();
                // TODO: led light activation;
        }
        ct.delay(500);
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

    static unsigned start = 0;
    static const unsigned stop = 40;

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
