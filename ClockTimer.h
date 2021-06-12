/*
 * ClockTimer.h
 *
 *  Created on: Jun 5, 2021
 *      Author: mafm
 */

#ifndef CLOCKTIMER_H_
#define CLOCKTIMER_H_

#include "msp430g2553.h"

class ClockTimer
{
public:
    ClockTimer();
    virtual ~ClockTimer();

    void init_timer0();
    void stop_timer0();
    void up_timer0();
};

#endif /* CLOCKTIMER_H_ */
