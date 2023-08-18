#ifndef CLOCKTIMER_H_
#define CLOCKTIMER_H_

#include "msp430g2553.h"

class clockTimer
{
public:
    clockTimer();
    void initTimer0();
    void stopTimer0();
    void upTimer0();
    void delay(unsigned msDelay);
};

#endif /* CLOCKTIMER_H_ */
