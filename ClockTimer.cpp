/*
 * ClockTimer.cpp
 *
 *  Created on: Jun 5, 2021
 *      Author: mafm
 */

#include <ClockTimer.h>

ClockTimer::ClockTimer()
{
    init_timer0();
    up_timer0();
    _bis_SR_register(GIE); //Enable interrupts
}

ClockTimer::~ClockTimer()
{
    stop_timer0();
}

void ClockTimer::init_timer0()
{
    // ACLK   = 32 768 Hz
    // ACLK/8 =  4 096 Hz

    //TACCTL0, Capture/Compare Control Register
    //TACCTL0 |= CCIE; //Enable Interrupts on Timer

    //TACCR0, Timer0_A Capture/Compare Register 0
    //TACCR0 = 4 096; //Number of cycles in the timer
            //4 096 / 4 096 = 1 kHz 
 
    // Timer0_A Control Register
    TACTL    |= TASSEL_1 + ID_3; //+ MC_1;
                                //MC_1; //Use UP mode timer
                          //ID_3; //SMCLK/8
                //TASSEL_1; //Use ACLK as source for timer
}

void ClockTimer::stop_timer0(){
    // Timer_A Control Register
    TACTL    |= MC_0; // Stop mode
    TACCTL0  &=~ CCIE; // Disable Interrupts on Timer
}

void ClockTimer::up_timer0(){
    TACCR0    = 4096;
    TACCTL0  |= CCIE;
    TACTL    |= MC_1;
}