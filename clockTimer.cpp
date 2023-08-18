#include "clockTimer.h"

clockTimer::clockTimer()
{
    initTimer0();
    upTimer0();
    __bis_SR_register(GIE); // Enable interrupts
}

void clockTimer::initTimer0()
{

    // Timer0_A Control Register
    TACTL |= TASSEL_1 + ID_3; //+ MC_1;
    // MC_1; //Use UP mode timer
    // ID_3; //SMCLK/8 =
    // TASSEL_1; //Use ACLK as source for timer
    // ACLK == 32768Hz // Clock source
    // ACLK/8 = 4096Hz
}

void clockTimer::stopTimer0()
{
    // Timer_A Control Register
    TACTL |= MC_0;    // Stop mode
    TACCTL0 &= ~CCIE; // Disable Interrupts on Timer
}

void clockTimer::upTimer0()
{
    //TACCR0 = 4096; // callback every 1 sec
    TACCR0 = 16; // callback every 3.9 ms (for buzzer)
    TACCTL0 |= CCIE;
    TACTL |= MC_1;
}

void clockTimer::delay(unsigned msDelay)
{
    for (unsigned i = msDelay; i > 1; i--)
    {
            __delay_cycles( 1000 );
    }
}
