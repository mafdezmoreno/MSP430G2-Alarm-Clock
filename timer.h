#ifndef ALARM_CLOCK_MSP430_TIMER_H
#define ALARM_CLOCK_MSP430_TIMER_H

#define CLR(x,y)	(x &= ~(y))

#include "msp430g2553.h"

class timer1
{
public:
    void usWait(const unsigned * usDelay);
    void msWait(const unsigned * msDelay);
    void usInitTimer(const unsigned * us);
    void msInitTimer(const unsigned * ms);
    bool timeOut();
    void stopTimer();
};

#endif /* ALARM_CLOCK_MSP430_TIMER_H */
