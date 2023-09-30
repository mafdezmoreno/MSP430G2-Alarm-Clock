#include "buzzer.h"
#include "buzzerTimer.h"
#include "clockTimer.h"
#include "lcdInterface.h"
#include "msp430g2553.h"
#include "timeDate.h"
#include "alarm.h"
#include "dht.h"
#include "io.h"

void initMcu();
unsigned signalIncrementSec = 0;
clockTimer ct;
buzzer buz(&ct);
void buzzerControl();

int main()
{
    static bool signalIncrementMin = false;
    static unsigned signalButton = 0;

    initMcu();
    timeDate td(&signalIncrementMin);
    buttons but;
    dht d;
    alarm al1(td.getCurrentTime(), td.getCurrentWeekDay());
    alarm al2(td.getCurrentTime(), td.getCurrentWeekDay());
    lcdLight light;

    // TODO: testing:
    enableLed();
    ledOff();
    light.on(); // Todo: To remove after tests
    __delay_cycles(1000000);
    // End Testing part

    lcdInterface li(&td, &al1, &al2, &but, &d);
    while (true)
    {
        static bool alarmStarted = false;
        if (signalIncrementSec)
        {
            while (signalIncrementSec)
            {
                td.incrementSecond();
                signalIncrementSec--;
            }
            d.readDht();
            li.printAll();
            light.countDown();
        }
        if (signalIncrementMin)
        {
            signalIncrementMin = false;
            static unsigned minCounter = 0;
            if (!alarmStarted && (al1.alarmTimeNow() || al2.alarmTimeNow()))
            {
                minCounter = 0;
                buz.activeBuz();
                alarmStarted = true;
            } else if (minCounter >= 5 && alarmStarted)
            {  // alarm can be on for 5 minutes.
                buz.deactivateBuz();
                minCounter = 0;
                alarmStarted = false;
            }
            minCounter++;
            li.batteryLevelToLcd();
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
                alarmStarted = false;
                light.resetCounter();
        }
        ct.delay(500);
    }
}

//Timer ISR to increment seconds
#pragma vector = TIMER0_A0_VECTOR
__interrupt void timerA0(void)
{
    static unsigned long counter = 0;

    if (buz.getBuzActive())
    {
        if (counter == 256)
        {
            signalIncrementSec++;
            counter = 0;
        }
        counter++;
        buzzerControl();
    }
    else
    {
        signalIncrementSec++;
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

    __bis_SR_register(GIE); // Enable interrupts
}

void buzzerControl()
{
    static unsigned start = 0;
    static const unsigned stop = 40;

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
        {
            start = 0;
        }
}