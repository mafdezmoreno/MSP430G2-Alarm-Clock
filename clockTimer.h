#ifndef CLOCKTIMER_H_
#define CLOCKTIMER_H_

#include "msp430g2553.h"

class clockTimer
{
public:
    clockTimer();
    void upTimerOneSec();
    void upTimerBuzz();
    void delay(unsigned msDelay);
private:
    void initTimer0();
    void stopTimer0();
};

#endif /* CLOCKTIMER_H_ */
