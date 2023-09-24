#include "timer.h"

#pragma vector = TIMER1_A0_VECTOR
__interrupt void dhtTimer(void)
{
    TA1CTL &= ~MC_3;
    CLR (TA1CCTL0, CCIE);
}

void timer1::msWait(const unsigned *msDelay)
{
    msInitTimer(msDelay);
    while (true)
    {
        if (timeOut())
        {
            break;
        }
    }
}

void timer1::usWait(const unsigned *usDelay)
{
    usInitTimer(usDelay);
    while (true)
    {
        if (timeOut())
        {
            break;
        }
    }
}

void timer1::usInitTimer(const unsigned *us)
{
    TA1CCR0 = (unsigned) (*us);
    TA1CTL = TASSEL_2 + MC_1 + TACLR;
    TA1CCTL0 |= CCIE;
}

void timer1::msInitTimer(const unsigned *ms)
{
    TA1CCTL0 |= CCIE;
    TA1CCR0 = (*ms) * 5;
    TA1CTL = TASSEL_1 | ID_3 | MC_1 | TACLR;
}


bool timer1::timeOut()
{
    return (TA1CTL & MC_1) == 0x00;
}

void timer1::stopTimer()
{
    TA1CTL &= ~MC_3;
    CLR (TA1CCTL0, CCIE);
}
